/****************************************************************************

  Header file for template service
  based on the Gen 2 Events and Services Framework

 ****************************************************************************/

#ifndef MotorStepService_H
#define MotorStepService_H

#include "ES_Types.h"

typedef enum
{
    TWO_PHASE_ON,
    ONE_PHASE_ON,
    HALF_STEP,
    QTR_STEP
} stepMode_t;

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
bool InitMotorStepService(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostMotorStepService(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunMotorStepService(ES_Event_t ThisEvent);

#endif /* MotorStepService_H */

