#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"

static leaderFSMState_t CuurentState;

static uint8_t MyPriority;

bool InitLeaderFSM(uint8_t Priority)
{
  MyPriority = Priority;
  CurrentState = InitPState_LeaderFSM;

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostLeaderFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunLeaderFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitPState_LeaderFSM:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
          DB_printf("\rES_INIT received in Leader FSM%d\r\n");
      }
    } 
    break;
    case AlignAtStart_LeaderFSM:
    {
        
    }
  }

  return ReturnEvent;
}