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


void InitDCMotor(void);

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle);

float getVelError(void);
#endif 

