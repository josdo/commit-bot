#ifndef DCMotor_H
#define DCMotor_H

#include "ES_Types.h"


typedef enum{
    LEFT_MOTOR = 0,
    RIGHT_MOTOR        
} Motors_t;

typedef enum{
    // Must be first two for setMotorSpeed() to have right values
    FORWARD = 0,
    BACKWARD = 1,
    CW,
    CCW
} Directions_t;

void InitDCMotor(bool enablePI);

float periodToMotorSpeed(uint32_t period);
float getMotorSpeed(Motors_t whichMotor);
uint32_t getRolloverTicks(void);

void enablePIControl(void);
void disablePIControl(void);

// Sets duty cycle -- overridden when PI motor control updates are on.
void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle);
// Sets desired speed
void setDesiredSpeed(Motors_t motor, Directions_t direction, uint32_t speed);

void rotate90(Directions_t direction);
void drive(Directions_t direction, uint32_t dist_cm);


bool reachedDesiredLPulses(void);
bool reachedDesiredRPulses(void);
bool reachedBothDesiredPulses(void);

#endif /* TemplateService_H */

