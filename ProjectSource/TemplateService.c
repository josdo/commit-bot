#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateService.h"

static uint8_t MyPriority;

bool InitTemplateService(uint8_t Priority)
{
  MyPriority = Priority;

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostTemplateService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunTemplateService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code

  return ReturnEvent;
}