#include "ES_Configure.h"
#include "ES_Framework.h"
#include "MotorStepService.h"
#include "PhaseControl.h"
#include "SpeedDialService.h"
#include <math.h>

static uint8_t MyPriority;

static float currTheta = 0;
static float dTheta = 0;
static uint32_t sps = 0;
// static stepMode_t stepMode;

/*  Set desired stator north and commands it. */
void SetCurrTheta(float theta)
{
  if (theta < 0 || theta >= 2*M_PI)
  {
    printf("Invalid currTheta");
  }
  currTheta = theta;
  SetStatorNorth(currTheta);
}

/*  Set step size with error checks.
  Args
    rads: radial step in stator's north pole, in radians. 
      Can be positive or negative. */
void SetStepSize(float rads)
{
  if (rads < -M_PI_2 || rads > -M_PI_2)
  {
  printf("Invalid step size");
  }
  dTheta = rads;
}

/*  Set step rate. 
  Args
    numStepsPerSec: steps per second */
void SetStepRate(uint32_t numStepsPerSec)
{
  sps = numStepsPerSec;
}

bool InitMotorStepService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;

  InitPhaseControl();

  // Initialize step sequence for two phase on
  // TODO: generalize to all step modes
  SetCurrTheta(pi/4);
  SetStepSize(pi/2);
  // TODO: setMaxStepRate from empirical testing

  SetStepRate(10);
  ES_Timer_InitTimer(NEXT_STEP_TIMER, (uint16_t) (1000.0 / sps));
  ES_Timer_StartTimer(NEXT_STEP_TIMER);

  // Post successful initialization
  ES_Event_t ThisEvent;
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

bool PostMotorStepService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunMotorStepService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  if ((ES_TIMEOUT == ThisEvent.EventType) 
     && (NEXT_STEP_TIMER == ThisEvent.EventParam))
  {
  // TODO: getStepRateFromDial()
  SetStepRate(10);
  SetCurrTheta(currTheta + dTheta);
  ES_Timer_StartTimer(NEXT_STEP_TIMER);
  }

  // TODO
  // if ES_NEW_SPEED
  // SetStepRate(event.param);

  return ReturnEvent;
}