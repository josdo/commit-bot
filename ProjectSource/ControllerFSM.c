/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Controller.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
static ControllerState_t CurrentState;
static uint8_t MyPriority;

static uint32_t MinPiezoOutput;
static uint32_t MaxPiezoOutput;
static uint32_t NumPiezoBuckets;

/*------------------------------ Module Code ------------------------------*/
bool InitController(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitPState;
  MinPiezoOutput  = 0;
  MaxPiezoOutput  = 250;
  NumPiezoBuckets = 10;

  // Post successful initialization
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

bool PostController(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunController(ES_Event_t ThisEvent)
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

ControllerState_t QueryController(void)
{
  return CurrentState;
}

bool DrumIsHit(void)
{
  // TODO fill in using A/D library
  return true;
}

/***************************************************************************
 private functions
 ***************************************************************************/

