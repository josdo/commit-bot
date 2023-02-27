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

float periodToMotorSpeed(uint32_t period);
float getMotorSpeed(Motors_t whichMotor);
float getWheelSpeed(Motors_t whichMotor);

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle);

void setVelocity(int32_t);
float getVelError(void);
#endif /* TemplateService_H */

