#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateFSM.h"

static TemplateFSMState_t CurrentState;

static uint8_t MyPriority;

bool InitTemplateFSM(uint8_t Priority)
{
  MyPriority = Priority;
  CurrentState = InitPState;

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostTemplateFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunTemplateFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitPState:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
        // TODO: do something, e.g. set CurrentState
      }
    } break;
  }

  return ReturnEvent;
}

TemplateFSMState_t QueryTemplateFSM(void)
{
  return CurrentState;
}