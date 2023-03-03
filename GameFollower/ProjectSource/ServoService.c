#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ServoService.h"

static uint8_t MyPriority;



bool InitServoService(uint8_t Priority)
{
  MyPriority = Priority;

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostServoService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunServoService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code
  
  switch(ThisEvent.EventType){
      case ES_GAME_START: {
          
      }
      break;
      
      case ES_GAME_END: {
          
      }
      break;
  }

  return ReturnEvent;
}