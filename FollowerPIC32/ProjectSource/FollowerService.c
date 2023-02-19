#include "ES_Configure.h"
#include "ES_Shared_Configure.h"
#include "ES_Framework.h"
#include "PIC32_SPI_HAL.h"
#include "ES_DeferRecall.h"
#include "PIC32PortHAL.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include <sys/attribs.h>
#include "FollowerService.h"
#include "DCMotorService.h"

// ----------------------------- Module Functions ------------------------
void setFollowerMode(void);
// -----------------------------------------------------------------------

// -------------------- Define SPI parameters -------------------- 
SPI_Module_t Module = SPI_SPI1;
SPI_SamplePhase_t Phase = SPI_SMP_END;
uint32_t SPI_ClkPeriodIn_ns = 10000;
SPI_PinMap_t SDIPin = SPI_RPA1;
SPI_PinMap_t SDOPin = SPI_RPA1; // CHANGE THIS
SPI_Clock_t WhichState = SPI_CLK_HI;
SPI_ActiveEdge_t WhichEdge = SPI_SECOND_EDGE;
SPI_XferWidth_t DataWidth = SPI_16BIT;
// ---------------------------------------------------------------

// ----------------------- SPI variables --------------------------
volatile uint8_t newCommand;
volatile uint8_t lastCommand = 0xFF;
static Follower_Response_t followerResponse = ExecutingCommand;
volatile uint8_t currentCommand;
// ----------------------------------------------------------------


#define PBCLK_RATE 20000000L
// TIMERx divisor for PWM, standard value is 8, to give maximum resolution
#define TIMER_DIV 8
uint16_t reqFreq = 100;
uint16_t period;


static uint8_t MyPriority;

bool InitFollowerService(uint8_t Priority)
{
  MyPriority = Priority;
  clrScrn();
  setFollowerMode();
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
//              puts("Sending command: \r\n");
              SPIOperate_SPI1_Send8Wait(0xAA);
              ES_Timer_InitTimer(COMMAND_TIMER, 300);
          }
      }
      break;
      case ES_START_COM:
      {
          puts("Start Communication with Command Gen \r\n");
          ES_Timer_InitTimer(COMMAND_TIMER, 300);
      }
      break;
      case ES_STOP_COM:
      {
          puts("Stop Communication with Command Gen \r\n");
          SPIOperate_SPI1_Send8Wait(0xFF);
          ES_Timer_StopTimer(COMMAND_TIMER);
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
      break;
      case ES_ButtonDown:
      {
          ThisEvent.EventType = ES_START_COM;
          PostLeaderService(ThisEvent);
      }
      

  }
  return ReturnEvent;
}


void setFollowerMode(){
    // Setting SPI Basic config and pins
    SPISetup_BasicConfig(Module);
    SPISetup_SetFollower(Module);
    SPISetup_SetBitTime(Module, SPI_ClkPeriodIn_ns);
    
    // map SS input
    ANSELAbits.ANSA0 = 0;           // digital
    TRISAbits.TRISA0 = 1;           // input
    SS1R = 0b0000;                  // map SS1 to RA0
    
    // SDI_1 = RA1
    SPISetup_MapSDInput(Module, SDIPin);
    
    // SDO_1 = 
    SPISetup_MapSDOutput(Module, SDOPin);
    
    
    SPISetup_SetClockIdleState(Module, WhichState);
    SPISetup_SetActiveEdge(Module, WhichEdge);
    SPISetup_SetXferWidth(Module, DataWidth);
    SPISetEnhancedBuffer(Module, false);
    SPISetup_EnableSPI(Module);
    
    // Setting the interrupts
    __builtin_disable_interrupts();
    IFS1CLR = _IFS1_SPI1RXIF_MASK;
    IEC1SET = _IEC1_SPI1RXIE_MASK;
    // multivector is enabled
    INTCONbits.MVEC = 1;                // enable multivector mode
    IPC7bits.SPI1IP = 7;                // interrupt priority is 7
//    IPC7 = 7;
    __builtin_enable_interrupts();
    
    PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0 | _Pin_1);
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_8);
}

void __ISR(_SPI_1_VECTOR, IPL7SOFT) ReceiverISR(void){
    IFS1CLR = _IFS1_SPI1RXIF_MASK;              // clear the flag
    
    currentCommand = SPI1BUF;                   // read the buffer
//    puts("hello");
    if (currentCommand != lastCommand){
        lastCommand = currentCommand;           // store previous command
//        DB_printf("com: %x\r\n", currentCommand);
        ES_Event_t NewEvent;
        NewEvent.EventType = ES_NEW_COMMAND;
        NewEvent.EventParam = currentCommand;
        PostDCMotorService(NewEvent);            // post the command
    }
    
}