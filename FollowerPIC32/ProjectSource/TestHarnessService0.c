#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DistanceSensor.h"
#include "TapeSensor.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "TestHarnessService0.h"

/*----------------------------- Module Defines ----------------------------*/
// these times assume a 10.000mS/tick timing
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

bool InitTestHarnessService0(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;

  // initialising everything
  InitDistanceSensor();
  InitTapeSensor();
  
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
        DB_printf("\rES_INIT received in Test Service %d\r\n", MyPriority);
        ES_Timer_InitTimer(SERVICE0_TIMER, HALF_SEC);
    }
    break;
    
    case ES_TIMEOUT:
    {
        if(ThisEvent.EventParam == SERVICE0_TIMER){
//            DB_printf("Distance Period is: %d\r\n", getDistance());
            DB_printf("Middle Is it on tape: %d\r\n", isOnTape(MiddleTapeSensor));
            DB_printf("Right Is it on tape: %d\r\n", isOnTape(RightTapeSensor));
            ES_Timer_InitTimer(SERVICE0_TIMER, HALF_SEC);
        }
    }
    break;
  }

  return ReturnEvent;
}

