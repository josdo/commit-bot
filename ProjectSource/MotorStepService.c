#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "MotorStepService.h"
#include "PhaseControl.h"
#include "SpeedDialService.h"

static uint8_t MyPriority;

static float currTheta = 0;
static float dTheta = 0;
static uint32_t sps = 0;
// static stepMode_t stepMode;

/*  Set desired stator north and commands it. */
void SetCurrTheta(float theta)
{
  // Constrains range to [0, 2pi)
  currTheta = theta - floor(theta / (2*M_PI)) * 2*M_PI;
  printf("currTheta = %f\n\r", currTheta);
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
    printf("Invalid step size\n\r");
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

void StartNextStepTimer()
{
  ES_Timer_InitTimer(NEXT_STEP_TIMER, (uint16_t) (1000.0 / sps));
  ES_Timer_StartTimer(NEXT_STEP_TIMER);
}

bool InitMotorStepService(uint8_t Priority)
{
  MyPriority = Priority;

  InitPhaseControl();

  // Initialize step sequence for one phase on
  // TODO: generalize to all step modes
  SetCurrTheta(0);
  SetStepSize(M_PI_2);
  // TODO: setMaxStepRate from empirical testing

  SetStepRate(100);
  StartNextStepTimer();

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostMotorStepService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunMotorStepService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

//   if (ES_TIMEOUT == ThisEvent.EventType) 
//   {
//     printf("Timer parameter is %i\n", ThisEvent.EventParam);
//   }

  if ((ES_TIMEOUT == ThisEvent.EventType) 
     && (NEXT_STEP_TIMER == ThisEvent.EventParam))
  {
    // TODO: getStepRateFromDial()
    SetCurrTheta(currTheta + dTheta);
    StartNextStepTimer();
  }

  // TODO
  // if ES_NEW_SPEED
  // SetStepRate(event.param);

  return ReturnEvent;
}