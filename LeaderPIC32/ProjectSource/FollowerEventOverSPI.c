#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_SPI_HAL.h"
#include "ES_DeferRecall.h"
#include "PIC32PortHAL.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include <sys/attribs.h>
#include "FollowerEventOverSPI.h"
#include "EventOverSPI.h"
#include "DCMotorService.h"

// #define PBCLK_RATE 20000000L
// // TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// #define TIMER_DIV 8
// uint16_t reqFreq = 100;
// uint16_t period;


static uint8_t MyPriority;

bool InitFollowerEventOverSPI(uint8_t Priority)
{
  MyPriority = Priority;

  // clrScrn();
  initEventOverSPI(true);

  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostFollowerEventOverSPI(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunFollowerEventOverSPI(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent = {ES_NO_EVENT};
  
  switch(ThisEvent.EventType){
      case ES_INIT:
      {
        DB_printf("FollowerEventOverSPI initialized.\r\n")
      }
      break;

      case ES_TIMEOUT:
      {
      }
      break;

      case ES_NEW_KEY:
      {
          // Start the communication with command gen
          if ('s' == ThisEvent.EventParam){
              ThisEvent.EventType = ES_START_COM;
              PostFollowerEventOverSPI(ThisEvent);
              
          }
          
          // Stop the communication with command generator
          if ('o' == ThisEvent.EventParam){
              ThisEvent.EventType = ES_STOP_COM;
              PostFollowerEventOverSPI(ThisEvent);
          }
      }
      break;

      default :
      {
        if (!IsFollowerEvent(ThisEvent.EventType))
        {
          DB_printf("ERROR: invalid event passed\r\n");
          break;
        }
        EncodeSendToFollower(ThisEvent.EventType, (uint8_t) ThisEvent.EventParam);
      }
      break;
  }
  return ReturnEvent;
}

/* ----------------------------------------------------------------------------------------
   ----------------------------------------------------------------------------------------
   Helper functions
   ----------------------------------------------------------------------------------------
   ---------------------------------------------------------------------------------------- */

/* Initialize SPI 1 to leader or follower mode with 16 bit data and enhanced mode on. */
void initEventOverSPI(bool is_leader)
{
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
  if (is_leader)
    SPISetup_SetLeader(Module, Phase);
  else
    SPISetup_SetFollower(Module)
  SPISetup_SetBitTime(Module, SPI_ClkPeriodIn_ns);
  SPISetup_MapSSOutput(Module, SSPin);
  SPISetup_MapSDInput(Module, SDIPin);
  SPISetup_MapSDOutput(Module, SDOPin);
  SPISetup_SetClockIdleState(Module, WhichState);
  SPISetup_SetActiveEdge(Module, WhichEdge);
  SPISetup_SetXferWidth(Module, DataWidth);
  SPISetEnhancedBuffer(Module, true);
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

/* Notify service that an event from follower has arrived. */
void __ISR(_SPI_1_VECTOR, IPL6SOFT) ISR_FollowerEventOverSPI(void){
{
  ES_Event_t e = {ES_FOLLOWER_SPI_EVENT};
  PostFollowerEventOverSPI(e);
}
