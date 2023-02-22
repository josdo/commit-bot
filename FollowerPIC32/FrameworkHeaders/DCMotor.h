#ifndef DCMotor_H
#define DCMotor_H

#include "ES_Types.h"


typedef enum{
    LEFT_MOTOR = 0,
    RIGHT_MOTOR        
} Motors_t;

typedef enum{
    FORWARD = 0,
    BACKWARD
} Directions_t;

/*
Params: 
     uint8_t : the priorty of this service
Return:
     bool, false if error in initialization, true otherwise
Description:
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
*/
void InitDCMotor(void);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle);

void setVelocity(int32_t);
float getVelError(void);
#endif /* TemplateService_H */

