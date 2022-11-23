#ifndef ClockFSM_H
#define ClockFSM_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  InitPState_ClockFSM = 0, WelcomeState_ClockFSM, IRCovered_ClockFSM, 
  PlayingGameState_ClockFSM, ZenState_ClockFSM
}ClockFSMState_t;

// Public Function Prototypes

/*
Params: 
     uint8_t : the priorty of this service
Return:
     bool, false if error in initialization, true otherwise
Description:
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
*/
bool InitClockFSM(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostClockFSM(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunClockFSM(ES_Event_t ThisEvent);

/*
Params:
  None
Return:
  ClockFSMState_t The current state of the Clock state machine
Description:
  Returns the current state of the Clock state machine
*/
ClockFSMState_t QueryClockFSM(void);



#endif /* TemplateFSM_H */

