#include "../ProjectHeaders/TestHarnessService0.h"
#include "BeaconSensor.h"
#include "../../Shared/ES_Shared_Configure.h"

#include <xc.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "../../Shared/EventOverSPI.h"

// #include "../../Shared/PIC32_SPI_HAL.h"
// #include <xc.h>
// #include <sys/attribs.h>

#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)

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

  InitEventOverSPI(true);

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
    }
    break;

    case ES_TEST_TO_LEADER:
    {
      DB_printf("ES_TEST_TO_LEADER received with param -> %u <-\r\n",
          ThisEvent.EventParam);
    }
    break;

    case ES_TIMEOUT:   // re-start timer & announce
    {
        if (FREQ_TIMER == ThisEvent.EventParam){
            DB_printf("Frequency on sensor = %d\r\n", 
                        getBeaconSensorTick(ShortRangeBeaconSensor));
            
            ES_Timer_InitTimer(FREQ_TIMER, ONE_SEC);
        }
//      ES_Timer_InitTimer(SERVICE0_TIMER, FIVE_SEC);
      // DB_printf("ES_TIMEOUT received from Timer %d in Service %d\r\n",
      //     ThisEvent.EventParam, MyPriority);
    }
    break;
    
    case ES_FOUND_BEACON_B:{
        puts("Beacon B was found!\r\n");
        ES_Timer_StopTimer(FREQ_TIMER);
    }
    break;
    
    case ES_FOUND_BEACON_C:{
        puts("Beacon C was found!\r\n");
        ES_Timer_StopTimer(FREQ_TIMER);
    }
    break;
    
    case ES_NEW_KEY:   // announce
    {
     DB_printf("\n\r\n\rES_NEW_KEY received with -> %c <- in Service 0\r\n",
          (char)ThisEvent.EventParam);
      
      if ('i' == ThisEvent.EventParam){
          puts("Init short range IR beacon ISR\r\n");
          InitBeaconSensor();
          IEC0SET = _IEC0_IC5IE_MASK;
          
          ES_Timer_InitTimer(FREQ_TIMER, ONE_SEC);
      }
      
      if ('f' == ThisEvent.EventParam)
      {
        DB_printf("Posting test event to follower\n\r");
        ES_Event_t e = {ES_TEST_TO_FOLLOWER, 204};
        PostEventOverSPI(e);
      }
    }
    break;

    default:
    {
      /* Likely received an erroneous event over SPI. */
      DB_printf("TestHarness ERROR: Unrecognized event received (word %2x%2x) (evt %d) \r\n", 
          ThisEvent.EventType, ThisEvent.EventParam, ThisEvent.EventType);
    }
}

  return ReturnEvent;
}