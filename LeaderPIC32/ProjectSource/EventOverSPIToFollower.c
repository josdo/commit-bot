#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_SPI_HAL.h"
#include "ES_DeferRecall.h"
#include "PIC32PortHAL.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include <sys/attribs.h>
#include "EventOverSPIToFollower.h"
#include "EventOverSPI.h"
#include "DCMotorService.h"

// #define PBCLK_RATE 20000000L
// // TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// #define TIMER_DIV 8
// uint16_t reqFreq = 100;
// uint16_t period;


static uint8_t MyPriority;

bool InitEventOverSPIToFollower(uint8_t Priority)
{
  MyPriority = Priority;

  // clrScrn();
  InitEventOverSPI(true);

  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostEventOverSPIToFollower(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunEventOverSPIToFollower(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent = {ES_NO_EVENT};
  
  switch(ThisEvent.EventType){
      case ES_INIT:
      {
        DB_printf("EventOverSPIToFollower initialized.\r\n")
      }
      break;

      case ES_NEW_KEY:
      {
          // Send test event to follower
          if ('s' == ThisEvent.EventParam){
              DB_printf("Sending test event to follower PIC\r\n");
              ES_Event_t e = {ES_TEST_TO_FOLLOWER};
              PostEventOverSPIToFollower(e);
          }
      }
      break;

      default :
      {
        EncodeSendToFollower(ThisEvent);
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
