#ifndef DCMotorService_H
#define DCMotorService_H

#include "ES_Types.h"

typedef enum{
    STOP = 0,
    CW_90,
    CW_45,
    CCW_90,
    CCW_45,
    FORWARD_HALF,
    FORWARD_FULL,
    BACKWARD_HALF,
    BACKWARD_FULL,
    BEACON,  
    TAPE,
    NA
} Commands_t;

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
bool InitDCMotorService(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostDCMotorService(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunDCMotorService(ES_Event_t ThisEvent);

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle);

#endif /* TemplateService_H */

