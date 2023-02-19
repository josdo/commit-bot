#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_SPI_HAL.h"
#include "ES_DeferRecall.h"
#include "PIC32PortHAL.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include <sys/attribs.h>
#include "EventOverSPIToLeader.h"
#include "EventOverSPI.h"
#include "DCMotorService.h"

static uint8_t MyPriority;

bool InitEventOverSPIToLeader(uint8_t Priority)
{
  MyPriority = Priority;

  InitEventOverSPI(true);

  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostEventOverSPIToLeader(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunEventOverSPIToLeader(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent = {ES_NO_EVENT};
  
  switch(ThisEvent.EventType){
      case ES_INIT:
      {
        DB_printf("EventOverSPIToLeader initialized.\r\n")
      }
      break;

      case ES_NEW_KEY:
      {
          // Send test event to leader
          if ('s' == ThisEvent.EventParam){
              DB_printf("Sending test event to leader PIC\r\n");
              // TODO
              // ES_Event_t e = {ES_TEST_TO_FOLLOWER};
              // PostEventOverSPIToLeader(e);
          }
      }
      break;

      case 

      default :
      {
        // TODO
        // if (!IsFollowerEvent(ThisEvent.EventType))
        // {
        //   DB_printf("ERROR: invalid event passed\r\n");
        //   break;
        // }
        // EncodeSendToFollower(ThisEvent.EventType, (uint8_t) ThisEvent.EventParam);
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

/* Notify service that an event from follower has arrived. */
void __ISR(_SPI_1_VECTOR, IPL6SOFT) ISR_EventOverSPIToLeader(void){
{
  // ES_Event_t e = {ES_FOLLOWER_SPI_EVENT};
  // PostEventOverSPIToLeader(e);
  while (!SPI1STATbits.SPIRBE)
  {
    uint16_t word = SPI1BUF;
    DecodePostFromFollower(word)
  }
}
