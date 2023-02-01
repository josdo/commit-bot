#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "PIC32PortHAL.h"
#include "MotorStepService.h"
#include "PWM.h"
#include "SpeedDialService.h"


static uint8_t MyPriority;
static uint16_t StepPeriod;

// // Button
// #define buttonPort PORTBbits.RB14
// static uint16_t lastButtonDownTime;

static void StartNextStepTimer();

bool InitMotorStepService(uint8_t Priority)
{
  MyPriority = Priority;
  // Configure pin A0 for PWM to one terminal of the DC motor coil
  InitPWM();
  // Configure pin A1 for holding the other terminal low
  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_1);
  LATAbits.LATA1 = 0;
  // Configure pin B3 to enable the H-bridge
  PortSetup_ConfigureDigitalOutputs(_Port_B, _Pin_3);
  LATBbits.LATB3 = 1;

  // StepPeriod = 1000;
  // StartNextStepTimer();

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
  static uint16_t currDC = 0;
  static const uint16_t stepDC = 10;
  static const uint16_t maxDC = 100;
  static const uint16_t minDC = 0;

  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_NEW_KEY:
    {
      if ('k' == ThisEvent.EventParam && currDC < 100)
      {
        currDC += stepDC;
        printf("Up to %u%% DC\n\r", currDC);
      }
      else if ('j' == ThisEvent.EventParam && currDC > 0)
      {
        currDC -= stepDC;
        printf("Dn to %u%% DC\n\r", currDC);
      }
      SetDutyCycle(currDC);
    } break;

    // case ES_TIMEOUT:
    // {
    //   if (NEXT_STEP_TIMER == ThisEvent.EventParam)
    //   {
    //     // SetDutyCycle(DialDutyCycle());
    //     StartNextStepTimer();
    //   }
    // }
    // break;
  }

  return ReturnEvent;
}

static void StartNextStepTimer()
{
  ES_Timer_InitTimer(NEXT_STEP_TIMER, StepPeriod);
  ES_Timer_StartTimer(NEXT_STEP_TIMER);
}

// static void InitButton(void)
// {
//   PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_14);
//   lastButtonDownTime = ES_Timer_GetTime();
// }

// /*  Event checker that returns true when a button is pressed. */
// bool ButtonIsPressed(void)
// {
//   static uint16_t cooldown = 300;

//   uint16_t currTime = ES_Timer_GetTime();
//   bool doneCooling = (currTime - lastButtonDownTime) > cooldown;
//   bool isPressed = (1 == buttonPort);
//   if (doneCooling && isPressed)
//   {
//     lastButtonDownTime = currTime;
//     ES_Event_t ReverseEvent = {ES_REVERSE_ROTATION, 0};
//     PostMotorStepService(ReverseEvent);
//     return true;
//   }
//   return false;
// }
