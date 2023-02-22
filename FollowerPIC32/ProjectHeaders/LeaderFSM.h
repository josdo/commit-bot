#ifndef LeaderFSM_H
#define LeaderFSM_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  InitPState_LeaderFSM = 0,
  AlignWithBeacon_LeaderFSM,
  Idle_LeaderFSM
}LeaderFSMState_t;

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
bool InitLeaderFSM(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostLeaderFSM(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunLeaderFSM(ES_Event_t ThisEvent);

/*
Params:
  None
Return:
  TemplateState_t The current state of the Template state machine
Description:
  Returns the current state of the Template state machine
*/
LeaderState_t QueryLeaderFSM(void);

#endif /* TemplateFSM_H */

