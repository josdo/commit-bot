#include "AdjustButtons.h"
#include <stdbool.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "dbprintf.h"
// #include "TopHSM.h"

#include "../../Shared/EventOverSPI.h"

#define LeftAdjustPort PORTBbits.RB3
#define RightAdjustPort PORTBbits.RB9
#define DirectionAdjustPort PORTAbits.RA3

static const uint32_t adjust_cm = 2;
static const uint32_t adjust_speed = 100;

static volatile bool lastLeftState;
static volatile bool lastRightState;

void InitAdjustButtons(void){
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_9 | _Pin_3);
    PortSetup_ConfigureDigitalInputs(_Port_A, _Pin_3);

    lastLeftState = LeftAdjustPort;
    lastRightState = RightAdjustPort;

    DB_printf ("Initialized AdjustButtons\r\n");
}

/* Return FORWARD if port direction adjust port high, BACKWARD otherwise. 
   TODO: ensure toggle switch mounted accordingly. */
Directions_t getAdjustDirection(void)
{
  return (DirectionAdjustPort == 1) ? BACKWARD : FORWARD;
}

bool pressedLeftAdjust(void)
{
    bool currState = LeftAdjustPort;
    bool stateChanged = currState != lastLeftState;
    bool isPressed = currState == 1;
    if(stateChanged && isPressed){
        adjust(LEFT_MOTOR, getAdjustDirection(), adjust_cm, adjust_speed);  \
        // ES_Event_t ReturnEvent = {ES_ADJUST_LEFT, getAdjustDirection()};
        DB_printf("AdjustButtons: pressedLeftAdjust\r\n");
        // PostTopHSM(ReturnEvent);
        return true;
    }
    lastLeftState = currState;
    return false;
}
        
bool pressedRightAdjust(void)
{
    bool currState = RightAdjustPort;
    bool stateChanged = currState != lastRightState;
    bool isPressed = currState == 1;
    if(stateChanged && isPressed){
        adjust(RIGHT_MOTOR, getAdjustDirection(), adjust_cm, adjust_speed);  \
        // ES_Event_t ReturnEvent = {ES_ADJUST_RIGHT, getAdjustDirection()};
        DB_printf("AdjustButtons: pressedRightAdjust\r\n");
        // PostTopHSM(ReturnEvent);
        return true;
    }
    lastRightState = currState;
    return false;
}