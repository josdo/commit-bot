#include "ES_Configure.h"
#include "ES_Framework.h"
#include "../ProjectHeaders/PIC32_SPI_HAL.h"
#include "ES_DeferRecall.h"
#include "PIC32PortHAL.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"

SPI_Module_t Module = SPI_SPI1;
SPI_SamplePhase_t Phase = SPI_SMP_END;
uint32_t SPI_ClkPeriodIn_ns = 10000;
SPI_PinMap_t SSPin = SPI_RPA0;
SPI_PinMap_t SDIPin = SPI_RPB8;
SPI_PinMap_t SDOPin = SPI_RPA1;
SPI_Clock_t WhichState = SPI_CLK_HI;
SPI_ActiveEdge_t WhichEdge = SPI_SECOND_EDGE;
SPI_XferWidth_t DataWidth = SPI_8BIT;

static uint8_t MyPriority;

bool InitLeaderService(uint8_t Priority)
{
  MyPriority = Priority;
          
  SPISetup_BasicConfig(Module);
  SPISetup_SetLeader(Module, Phase);
  SPISetup_SetBitTime(Module, SPI_ClkPeriodIn_ns);
  SPISetup_MapSSOutput(Module, SSPin);
  SPISetup_MapSDInput(Module, SDIPin);
  SPISetup_MapSDOutput(Module, SDOPin);
  SPISetup_SetClockIdleState(Module, WhichState);
  SPISetup_SetActiveEdge(Module, WhichEdge);
  SPISetup_SetXferWidth(Module, DataWidth);
  SPISetEnhancedBuffer(Module, false);
  SPISetup_EnableSPI(Module);
  
  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0 | _Pin_1);
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_8);

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}


bool PostLeaderService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunLeaderService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  
  
  // TODO write service code
  switch(ThisEvent.EventType){
      case ES_INIT:
      {
        puts("Service 01:");
        DB_printf("\rES_INIT received in Service %d\r\n", MyPriority);
      }
      break;
      case ES_TIMEOUT:
      {
          if(ThisEvent.EventParam == COMMAND_TIMER)
          {
              SPIOperate_SPI1_Send8Wait(0xAA);
              ES_Timer_InitTimer(COMMAND_TIMER, 300);
          }
      }
      break;
      case ES_START_COM:
      {
          SPISetup_EnableSPI(Module);
          puts("Start Communication with Command Gen \r\n");
//          SPIOperate_SPI1_Send8Wait(0xAA);
          ES_Timer_InitTimer(COMMAND_TIMER, 300);
      }
      break;
      case ES_STOP_COM:
      {
          puts("Stop Communication with Command Gen \r\n");
          SPIOperate_SPI1_Send8Wait(0xFF);
          ES_Timer_StopTimer(COMMAND_TIMER);
//          SPISetup_DisableSPI(Module);
      }
      break;
      case ES_NEW_KEY:
      {
          // Start the communication with command gen
          if ('s' == ThisEvent.EventParam){
              ThisEvent.EventType = ES_START_COM;
              PostLeaderService(ThisEvent);
              
          }
          
          // Stop the communication with command generator
          if ('o' == ThisEvent.EventParam){
              ThisEvent.EventType = ES_STOP_COM;
              PostLeaderService(ThisEvent);
          }
      }

  }
  return ReturnEvent;
}