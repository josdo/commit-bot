#include "../ProjectHeaders/TestHarnessService0.h"

#include <xc.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
//#include "../../Shared/EventOverSPI.h"

#include "BranchSwitch.h"
#include "LEDService.h"
#include "ButtonService.h"

// #include "../../Shared/PIC32_SPI_HAL.h"
// #include <xc.h>
// #include <sys/attribs.h>

static uint8_t MyPriority;

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

//  InitEventOverSPI(false);
  
  InitButtonService();

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

bool PostTestHarnessService0(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunTestHarnessService0(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
      puts("Service 00:");
      DB_printf("\rES_INIT received in Service %d\r\n", MyPriority);
//       ES_Timer_InitTimer(SWITCH_TIMER, 1000);
      
      InitSwitches();
    }
    break;

    case ES_TEST_TO_FOLLOWER:
    {
      DB_printf("\n\r\n\rES_TEST_TO_FOLLOWER received with param -> %u <-\r\n",
          ThisEvent.EventParam);
    }
    break;

    case ES_TIMEOUT:   // re-start timer & announce
    {
        if (SWITCH_TIMER == ThisEvent.EventParam){
            puts("\n");
            BranchType_t B = GetBranch();
            BranchDist_t D = GetDist();
            DB_printf("Branch = %d\r\n", B);
            DB_printf("Dist = %d\r\n", D);
            ES_Timer_InitTimer(SWITCH_TIMER, 1000);
        }
//      ES_Timer_InitTimer(SERVICE0_TIMER, FIVE_SEC);
      // DB_printf("ES_TIMEOUT received from Timer %d in Service %d\r\n",
      //     ThisEvent.EventParam, MyPriority);
    }
    break;

    case ES_NEW_KEY:   // announce
    {
     DB_printf("\n\r\n\rES_NEW_KEY received with -> %c <- in Service 0\r\n",
         (char)ThisEvent.EventParam);
      
      if ('b' == ThisEvent.EventParam){
              ES_Event_t testEvent = {ES_FOUND_BEACON_B, 0};
              ES_PostAll(testEvent);
          }
          
          else if ('c' == ThisEvent.EventParam){
              ES_Event_t testEvent = {ES_FOUND_BEACON_C, 0};
              ES_PostAll(testEvent);
          }
          
          else if ('f' == ThisEvent.EventParam){
              ES_Event_t testEvent = {ES_GAME_END, 0};
              ES_PostAll(testEvent);
          }
          else if ('s' == ThisEvent.EventParam){
              ES_Event_t testEvent = {ES_GAME_START, 0};
              ES_PostAll(testEvent);
          }
    }
    break;
  }

  return ReturnEvent;
}