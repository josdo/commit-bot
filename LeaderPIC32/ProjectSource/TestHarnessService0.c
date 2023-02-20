/****************************************************************************
 Module
   TestHarnessService0.c

 Revision
   1.0.1

 Description
   This is the first service for the Test Harness under the
   Gen2 Events and Services Framework.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/26/17 18:26 jec     moves definition of ALL_BITS to ES_Port.h
 10/19/17 21:28 jec     meaningless change to test updating
 10/19/17 18:42 jec     removed referennces to driverlib and programmed the
                        ports directly
 08/21/17 21:44 jec     modified LED blink routine to only modify bit 3 so that
                        I can test the new new framework debugging lines on PF1-2
 08/16/17 14:13 jec      corrected ONE_SEC constant to match Tiva tick rate
 11/02/13 17:21 jec      added exercise of the event deferral/recall module
 08/05/13 20:33 jec      converted to test harness service
 01/16/12 09:58 jec      began conversion from TemplateFSM.c
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
// This module
#include "../ProjectHeaders/TestHarnessService0.h"

// debugging printf()

// Hardware
#include <xc.h>
//#include <proc/p32mx170f256b.h>

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
// #include "../../Shared/EventOverSPI.h"
#include "PIC32_SPI_HAL.h"
#include "PIC32PortHAL.h"
#include <sys/attribs.h>


/*----------------------------- Module Defines ----------------------------*/
// these times assume a 10.000mS/tick timing
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)

#define ENTER_POST     ((MyPriority<<3)|0)
#define ENTER_RUN      ((MyPriority<<3)|1)
#define ENTER_TIMEOUT  ((MyPriority<<3)|2)

// #define TEST_INT_POST
/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitTestHarnessService0

 Parameters
     uint8_t : the priorty of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, and does any
     other required initialization for this service
 Notes

 Author
     J. Edward Carryer, 01/16/12, 10:00
****************************************************************************/
bool InitTestHarnessService0(uint8_t Priority)
{
  ES_Event_t ThisEvent;
  MyPriority = Priority;
  clrScrn();
  puts("\rStarting Test Harness for \r");
  DB_printf( "the 2nd Generation Events & Services Framework V2.4\r\n");
  DB_printf( "compiled at %s on %s\n", __TIME__, __DATE__);
  DB_printf( "\n\r\n");
  DB_printf( "Press any key to post key-stroke events\n\r");

  // InitEventOverSPI(true);
  SPI_Module_t Module = SPI_SPI1;
  SPI_SamplePhase_t Phase = SPI_SMP_END;
  uint32_t SPI_ClkPeriodIn_ns = 10000;
  SPI_PinMap_t SSPin = SPI_RPA0;
  SPI_PinMap_t SDIPin = SPI_RPB8;
  SPI_PinMap_t SDOPin = SPI_RPA1;
  SPI_Clock_t WhichState = SPI_CLK_HI;
  SPI_ActiveEdge_t WhichEdge = SPI_SECOND_EDGE;
  SPI_XferWidth_t DataWidth = SPI_16BIT;

  
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

  // Setting the interrupts
//  __builtin_disable_interrupts();
//  IFS1CLR = _IFS1_SPI1RXIF_MASK;
//  IEC1SET = _IEC1_SPI1RXIE_MASK;
//  // multivector is enabled
//  INTCONbits.MVEC = 1;                // enable multivector mode
//  IPC7bits.SPI1IP = 7;                // interrupt priority is 7
//  __builtin_enable_interrupts();

  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0 | _Pin_1);
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_8);

  // post the initial transition event
  ThisEvent.EventType = ES_INIT;
  if (ES_PostToService(MyPriority, ThisEvent) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/****************************************************************************
 Function
     PostTestHarnessService0

 Parameters
     ES_Event ThisEvent ,the event to post to the queue

 Returns
     bool false if the Enqueue operation failed, true otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
     J. Edward Carryer, 10/23/11, 19:25
****************************************************************************/
bool PostTestHarnessService0(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunTestHarnessService0

 Parameters
   ES_Event : the event to process

 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes

 Author
   J. Edward Carryer, 01/15/12, 15:23
****************************************************************************/
ES_Event_t RunTestHarnessService0(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  static char DeferredChar = '1';

#ifdef _INCLUDE_BYTE_DEBUG_
  _HW_ByteDebug_SetValueWithStrobe( ENTER_RUN );
#endif  
  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
      puts("Service 00:");
      DB_printf("\rES_INIT received in Service %d\r\n", MyPriority);
    }
    break;

    case ES_NEW_KEY:   // announce
    {
     DB_printf("ES_NEW_KEY received with -> %c <- in Service 0\r\n",
         (char)ThisEvent.EventParam);
      if ('d' == ThisEvent.EventParam)
      {
        DB_printf("Posting test event to follower\n\r");
//        for(uint32_t i=0; i<=0xffffff; i++){}
        ES_Event_t e = {ES_TEST_TO_FOLLOWER};
        // SPIOperate_SPI1_Send8Wait(0xf2);
        SPIOperate_SPI1_Send16Wait(0xFFFF);
        // PostToOther(e);
      }
    }
    break;
  }

  return ReturnEvent;
}

// void __ISR(_SPI_1_VECTOR, IPL7SOFT) ReceiverISR(void){
//     IFS1CLR = _IFS1_SPI1RXIF_MASK;              // clear the flag
    
// //     currentCommand = SPI1BUF;                   // read the buffer
// // //    puts("hello");
// //     if (currentCommand != lastCommand){
// //         lastCommand = currentCommand;           // store previous command
// // //        DB_printf("com: %x\r\n", currentCommand);
// //         ES_Event_t NewEvent;
// //         NewEvent.EventType = ES_NEW_COMMAND;
// //         NewEvent.EventParam = currentCommand;
// //         PostDCMotorService(NewEvent);            // post the command
// //     }
    
// }