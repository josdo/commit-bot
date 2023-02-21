// #include "ES_Types.h"
// #include "../Shared/ES_Shared_Configure.h"
// #include "ES_Events.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "dbprintf.h"
#include "PIC32_SPI_HAL.h"
#include <xc.h>
#include <sys/attribs.h>

static bool isLeader;

typedef union
{
  struct
  {
    uint8_t EventType;
    uint8_t EventParam;
  };
  uint16_t w;
} SPI_Event_t;

static uint16_t QUERY_FOLLOWER_WORD = 0xAAAA;
static uint16_t NO_EVENT_WORD = 0xAAAA;

/* Queue for follower events to leader. */
static uint16_t wordQueue[100];
static uint32_t wordQueueSize = 0;

static bool FitsIn8Bits(uint16_t data);

/* Initialize SPI 1 to leader or follower mode with 16 bit data 
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
  SPISetup_EnableSPI(Module);

  __builtin_disable_interrupts();
  IFS1CLR = _IFS1_SPI1RXIF_MASK;
  IEC1SET = _IEC1_SPI1RXIE_MASK;
  INTCONbits.MVEC = 1;                // enable multivector mode
  IPC7bits.SPI1IP = 7;                // interrupt priority is 7
  __builtin_enable_interrupts();
  
  // PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0 | _Pin_1);
  // PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_8);
}

/* Encode event into 16 bits and send over SPI. Return true if successful, false otherwise. */
bool PostToOther(ES_Event_t e)
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
  }
  else
  {
    wordQueue[wordQueueSize] = se.w;
    wordQueueSize++;
  }
  return true;
}

static bool FitsIn8Bits(uint16_t data)
{
  return (0 <= data <= 0xff);
}

/* Notify service that an event from the other PIC has arrived. */
void __ISR(_SPI_1_VECTOR, IPL6SOFT) ISR_EventOverSPI(void)
{
  uint16_t word = SPI1BUF;
  IFS1CLR = _IFS1_SPI1RXIF_MASK;

  SPI_Event_t se;
  se.w = word;
  ES_Event_t e = {(ES_EventType_t) se.EventType, (uint16_t) se.EventParam};

  if (isLeader)
  {
    // Post event from follower and query follower for any more events
    if (word != NO_EVENT_WORD)
    {
      ES_PostAll(e);
      SPIOperate_SPI1_Send16Wait(QUERY_FOLLOWER_WORD);
    }
  }
  else
  {
    // Post event from leader
    if (word != QUERY_FOLLOWER_WORD)
    {
      ES_PostAll(e);
    }

    // Post a queued event to leader
    if (wordQueueSize == 0)
    {
      SPIOperate_SPI1_Send16Wait(NO_EVENT_WORD);
    }
    else
    {
      SPIOperate_SPI1_Send16Wait(wordQueue[0]);
      // TODO expensive, use circular buffer?
      for (uint32_t i = 0; i < wordQueueSize - 1; i++)
      {
        wordQueue[i] = wordQueue[i + 1];
      }
      wordQueueSize--;
    }
  }
}