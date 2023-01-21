#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "MotorStepService.h"
#include "PhaseControl.h"
#include "SpeedDialService.h"


static uint8_t MyPriority;

// Stepping
static float currTheta = 0;
static float dTheta = 0;
static uint32_t sps = 0;
static stepMode_t stepMode;
static bool checkDrift = false; /* Forward and reverse stepping to spot drift. */
static uint32_t driftCheckSteps;

// Button
#define buttonPort PORTBbits.RB14
static uint16_t lastButtonDownTime;

static void InitButton(void);

/*  Set desired stator north and commands it. */
void SetCurrTheta(float theta)
{
  // Constrains range to [0, 2pi)
  currTheta = theta - floor(theta / (2*M_PI)) * 2*M_PI;
  // printf("currTheta = %.2f pi\n\r", currTheta/M_PI);
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
  if (numStepsPerSec < 1)
    sps = 1;
  else
    sps = numStepsPerSec;
}

void StartNextStepTimer()
{
  ES_Timer_InitTimer(NEXT_STEP_TIMER, (uint16_t) (1000.0 / sps));
  ES_Timer_StartTimer(NEXT_STEP_TIMER);
}

static void InitButton(void)
{
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_14);
  lastButtonDownTime = ES_Timer_GetTime();
}

/*  Event checker that returns true when a button is pressed. */
bool ButtonIsPressed(void)
{
  static uint16_t cooldown = 300;

  uint16_t currTime = ES_Timer_GetTime();
  bool doneCooling = (currTime - lastButtonDownTime) > cooldown;
  bool isPressed = (1 == buttonPort);
  if (doneCooling && isPressed)
  {
    lastButtonDownTime = currTime;
    ES_Event_t ReverseEvent = {ES_REVERSE_ROTATION, 0};
    PostMotorStepService(ReverseEvent);
    return true;
  }
  return false;
}

bool InitMotorStepService(uint8_t Priority)
{
  MyPriority = Priority;

  InitPhaseControl();
  InitButton();

  // Configure
  stepMode = TWO_PHASE_ON;
  SetStepRate(75);
  checkDrift = false;
  driftCheckSteps = 50;

  // Initialize step sequence based on step mode
  if (TWO_PHASE_ON == stepMode)
  {
    SetCurrTheta(M_PI_4);
    SetStepSize(M_PI_2);
    SetMaxStepRate(250);
    SetUseMaxDutyCycle(true);
  }
  else if (ONE_PHASE_ON == stepMode)
  {
    SetCurrTheta(0);
    SetStepSize(M_PI_2);
    SetMaxStepRate(200);
    SetUseMaxDutyCycle(true);
  }
  else if (HALF_STEP == stepMode)
  {
    SetCurrTheta(0);
    SetStepSize(M_PI_4);
    SetMaxStepRate(500);
    SetUseMaxDutyCycle(true);
  }
  else if (QTR_STEP == stepMode)
  {
    SetCurrTheta(0);
    SetStepSize(M_PI_4/2);
    SetMaxStepRate(75);
    SetUseMaxDutyCycle(false);
  }

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
  // Keep track of forward and reverse steps
  static uint16_t netStepsForward = 0;

  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_REVERSE_ROTATION:
    {
      SetStepSize(-1 * dTheta);
      printf("Reverse rotation, dTh = %f \n\r", dTheta);
    }
    break;

    case ES_TIMEOUT:
    {
      if (NEXT_STEP_TIMER == ThisEvent.EventParam)
      {
        SetStepRate(GetStepRateFromDial());
        SetCurrTheta(currTheta + dTheta);
        StartNextStepTimer();

        // Update net steps forward
        netStepsForward += (dTheta > 0) ? 1 : -1;
        if (checkDrift)
        {
          if (netStepsForward == driftCheckSteps || netStepsForward == 0)
          {
            ES_Event_t reverseEvent = {ES_REVERSE_ROTATION, 0};
            PostMotorStepService(reverseEvent);
          }
        }
        
      }
    }
    break;
  }

  return ReturnEvent;
}