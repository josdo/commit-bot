#include "EventOverSPI.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "dbprintf.h"
#include "PIC32_SPI_HAL.h"
#include "PIC32PortHAL.h"
#include <xc.h>
#include <sys/attribs.h>

static bool isLeader;

/* Word that leader sends to pump any event stored in the follower. */
static uint16_t QUERY_WORD = 0xAAAA;

/* The default word in the follower's SPIBUF when no event is to be sent. 
   This value is also the default low value when the follower is not sending. */
static uint16_t NO_LEFTOVER_WORD = 0;

/* Queue for follower events. Dequeuing exclusively in the ISR. */
static uint16_t followerQueue[100];
static uint32_t followerQueueSize = 0;
static uint32_t followerQueueFront = 0; // Owned and reset by the ISR.

static bool FitsIn8Bits(uint16_t data);

/* Initialize SPI 1 to leader or follower mode. */
void InitEventOverSPI(bool isDriveMaster)
{
  isLeader = isDriveMaster;

  if (isLeader)
    DB_printf("\r\nEventOverSPI init'd to LEADER mode.\r\n");
  else
    DB_printf("\r\nEventOverSPI init'd to FOLLOWER mode.\r\n");

  // SPI setup
  SPI_Module_t Module = SPI_SPI1;
  SPI_SamplePhase_t Phase = SPI_SMP_MID;
  uint32_t SPI_ClkPeriodIn_ns = 50000; // 50 KHz clock
  SPI_PinMap_t SSPin = SPI_RPA0;
  SPI_PinMap_t SDIPin = SPI_RPB8;
  SPI_PinMap_t SDOPin = SPI_RPA1;
  SPI_Clock_t WhichState = SPI_CLK_HI;
  SPI_ActiveEdge_t WhichEdge = SPI_SECOND_EDGE;
  SPI_XferWidth_t DataWidth = SPI_16BIT; // 16bit word

  SPISetup_BasicConfig(Module);
  if (isLeader)
    SPISetup_SetLeader(Module, Phase);
  else
    SPISetup_SetFollower(Module);
  SPISetup_SetBitTime(Module, SPI_ClkPeriodIn_ns);
  if (isLeader)
    SPISetup_MapSSOutput(Module, SSPin);
  else
  {
    SPISetup_MapSSInput(Module, SSPin);
  }
  SPISetup_MapSDInput(Module, SDIPin);
  SPISetup_MapSDOutput(Module, SDOPin);
  SPISetup_SetClockIdleState(Module, WhichState);
  SPISetup_SetActiveEdge(Module, WhichEdge);
  SPISetup_SetXferWidth(Module, DataWidth);
  SPISetEnhancedBuffer(Module, false);
  SPISetup_EnableSPI(Module);

  /* Initialize SPIBUF to empty status. */
  if (!isLeader)
    SPI1BUF = NO_LEFTOVER_WORD;

  __builtin_disable_interrupts();
  IFS1CLR = _IFS1_SPI1RXIF_MASK;
  IEC1SET = _IEC1_SPI1RXIE_MASK;
  // enable multivector mode
  INTCONbits.MVEC = 1;
  // Interrupt priority. Match with IPL of ISR.
  IPC7bits.SPI1IP = 6;
  __builtin_enable_interrupts();
  
  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0 | _Pin_1);
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_8);

}

/* Posts the event to the other PIC. If a leader, sends the event immediately, followed
   by a QUERY_WORD in case the follower loads up a queued event upon receiving the leader's first event.
   If a follower, queues up the event to be sent to the leader by the ISR_EventOverSPI.

   Encodes event into 16 bits. Return true if successful, false otherwise. */
bool PostEventOverSPI(ES_Event_t e)
{
  if (!FitsIn8Bits(e.EventParam) || !FitsIn8Bits(e.EventType))
  {
    DB_printf("ERROR: EventOverSPI.c, even param cannot fit in 8 bits.\r\n");
    return false;
  }
  
  SPI_Event_t se = {(uint8_t) e.EventType, (uint8_t) e.EventParam};
  if (isLeader)
  {
    SPIOperate_SPI1_Send16Wait(se.w);
    SPIOperate_SPI1_Send16Wait(QUERY_WORD);
  }
  else
  {
    followerQueue[followerQueueSize] = se.w;
    followerQueueSize++;
    DB_printf("PostEventOverSPI, follower: queued %x\r\n", se.w);
    DB_printf("PostEventOverSPI, follower: queue size now %d\r\n", followerQueueSize);
  }
  return true;
}

static bool FitsIn8Bits(uint16_t data)
{
  return (0 <= data <= 0xff);
}

/* Posts the received event over SPI to all services on this PIC.
   On interrupt, the follower writes its next queued up event to the SPIBUF, or
   NO_LEFTOVER_WORD when it runs out.
   On interrupt, the leader checks if it is NO_LEFTOVER_WORD. If not, the leader 
   sends QUERY_WORD in case any more events are queued up in the follower. */
void __ISR(_SPI_1_VECTOR, IPL6SOFT) ISR_EventOverSPI(void)
{
  uint16_t word = SPI1BUF;
  IFS1CLR = _IFS1_SPI1RXIF_MASK;

  SPI_Event_t se;
  se.w = word;
  ES_Event_t e = {(ES_EventType_t) se.EventType, (uint16_t) se.EventParam};

  if (isLeader)
  {
    if (word == NO_LEFTOVER_WORD)
    {
      // DB_printf("ISR_EventOverSPI, leader: got NO_LEFTOVER_WORD.\r\n");
      return;
    }
    else if (e.EventType >= NUM_ES_EVENTS)
    {
      // DB_printf("ISR_EventOverSPI, leader: got invalid word %x.\r\n", word);
      return;
    }
    // DB_printf("ISR_EventOverSPI, leader: got word %x\r\n", word);

    ES_PostAll(e);
    SPIOperate_SPI1_Send16(QUERY_WORD);
    DB_printf("Event: %d\r\n", e.EventType);
  }
  else
  {
    if (word != QUERY_WORD)
    {
      ES_PostAll(e);
    }

    /* At this point, any event that was stored into the SPIBUF has already 
       been pumped out with the receipt of the current word from the leader,
       so the SPIBUF can store the next word to send the leader. */

    if (followerQueueSize == followerQueueFront)
    {
      SPI1BUF = NO_LEFTOVER_WORD;
      followerQueueSize = 0;
      followerQueueFront = 0;
      // DB_printf("ISR_EventOverSPI, follower: SPI1BUF set to NO_LEFTOVER_WORD %x\r\n", NO_LEFTOVER_WORD);
    }
    else
    {
      SPI1BUF = followerQueue[followerQueueFront];
      // DB_printf("ISR_EventOverSPI, follower: SPI1BUF set to %x\r\n", followerQueue[0]);

      followerQueueFront++;
    }
  }
}