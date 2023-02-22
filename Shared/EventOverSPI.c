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
   This value is also the default low value when the follower PIC is off
   so it should be robust to the follower being off. 
   TODO: test this robustness. */
static uint16_t NO_LEFTOVER_WORD = 0;

/* True if a follower event is stored in the SPIBUF. */
static bool followerBUFIsEmpty = true;

/* Queue for additional follower events after the one stored in the SPIBUF.
   The total number of events to send is followerBUFIsEmpty + followerQueueSize. */
static uint16_t followerQueue[100];
static uint32_t followerQueueSize = 0;

static bool FitsIn8Bits(uint16_t data);

/* Initialize SPI 1 to leader or follower mode with 16 bit words, 100 kHz clock, 
   and enhanced mode on. */
void InitEventOverSPI(bool isDriveMaster)
{
  isLeader = isDriveMaster;

  if (isLeader)
    DB_printf("Initializing EventOverSPI to leader mode.\r\n");
  else
    DB_printf("Initializing EventOverSPI to follower mode.\r\n");

  // SPI setup
  SPI_Module_t Module = SPI_SPI1;
  SPI_SamplePhase_t Phase = SPI_SMP_MID;
  uint32_t SPI_ClkPeriodIn_ns = 10000;
  SPI_PinMap_t SSPin = SPI_RPA0;
  SPI_PinMap_t SDIPin = SPI_RPB8;
  SPI_PinMap_t SDOPin = SPI_RPA1;
  SPI_Clock_t WhichState = SPI_CLK_HI;
  SPI_ActiveEdge_t WhichEdge = SPI_SECOND_EDGE;
  SPI_XferWidth_t DataWidth = SPI_16BIT;

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
    DB_printf("WARMING: EventOverSPI.c, follower mode not tested yet.\r\n");
    SPISetup_MapSSInput(Module, SSPin);
  }
  SPISetup_MapSDInput(Module, SDIPin);
  SPISetup_MapSDOutput(Module, SDOPin);
  SPISetup_SetClockIdleState(Module, WhichState);
  SPISetup_SetActiveEdge(Module, WhichEdge);
  SPISetup_SetXferWidth(Module, DataWidth);
  SPISetEnhancedBuffer(Module, false);
  // /* Initialize SPIBUF to empty status. */
  // // TODO: make work
  // SPI1BUF = NO_LEFTOVER_WORD;
  SPISetup_EnableSPI(Module);

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

/* Posts the event to the other PIC. If a leader, sends the event immediately.
   If a follower, queues the event directly into the SPIBUF or into a separate queue
   that the ISR_EventOverSPI will send to the leader.

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
    // SPIOperate_SPI1_Send16Wait(QUERY_WORD);
  }
  else
  {
    if (followerBUFIsEmpty)
    {
      // SPISetup_DisableSPI(SPI_SPI1);
      SPI1BUF = se.w;
      // SPISetup_EnableSPI(SPI_SPI1);
      DB_printf("PostEventOverSPI, follower: set BUF to %x\r\n", se.w);
      followerBUFIsEmpty = false;
    }
    else
    {
      followerQueue[followerQueueSize] = se.w;
      followerQueueSize++;
      DB_printf("PostEventOverSPI, follower: queued %x\r\n", se.w);
      DB_printf("PostEventOverSPI, follower: queue size now %d\r\n", followerQueueSize);
    }
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
      DB_printf("ISR_EventOverSPI, leader: got NO_LEFTOVER_WORD.\r\n");
      return;
    }
    else if (e.EventType >= NUM_ES_EVENTS)
    {
      DB_printf("ISR_EventOverSPI, leader: got invalid word %x.\r\n", word);
      return;
    }
    DB_printf("ISR_EventOverSPI, leader: got word %x\r\n", word);

    ES_PostAll(e);
    SPIOperate_SPI1_Send16Wait(QUERY_WORD);
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

    if (followerQueueSize == 0)
    {
      // SPISetup_DisableSPI(SPI_SPI1);
      SPI1BUF = NO_LEFTOVER_WORD;
      // SPISetup_EnableSPI(SPI_SPI1);
      DB_printf("ISR_EventOverSPI, follower: SPI1BUF set to NO_LEFTOVER_WORD %x\r\n", NO_LEFTOVER_WORD);
      followerBUFIsEmpty = true;
    }
    else
    {
      // SPISetup_DisableSPI(SPI_SPI1);
      SPI1BUF = followerQueue[0];
      // SPISetup_EnableSPI(SPI_SPI1);
      DB_printf("ISR_EventOverSPI, follower: SPI1BUF set to %x\r\n", followerQueue[0]);
      followerBUFIsEmpty = false;
      // TODO expensive operation on the follower PIC, use circular buffer?
      followerQueueSize--;
      for (uint32_t i = 0; i < followerQueueSize; i++)
      {
        DB_printf("  Shifted queue up\r\n");
        followerQueue[i] = followerQueue[i + 1];
      }
      DB_printf("ISR_EventOverSPI, follower: queue size now %d\r\n", followerQueueSize);
    }
  }
}