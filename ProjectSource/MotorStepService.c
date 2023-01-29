#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "MotorStepService.h"
#include "PWM.h"
#include "SpeedDialService.h"


static uint8_t MyPriority;

// // Button
// #define buttonPort PORTBbits.RB14
// static uint16_t lastButtonDownTime;

// static void InitButton(void);

// void StartNextStepTimer()
// {
//   ES_Timer_InitTimer(NEXT_STEP_TIMER, (uint16_t) (1000.0 / sps));
//   ES_Timer_StartTimer(NEXT_STEP_TIMER);
// }

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

bool InitMotorStepService(uint8_t Priority)
{
  MyPriority = Priority;
  InitPWM();

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

  // switch (ThisEvent.EventType)
  // {
  //   case ES_REVERSE_ROTATION:
  //   {
  //     SetStepSize(-1 * dTheta);
  //     printf("Reverse rotation, dTh = %f \n\r", dTheta);
  //   }
  //   break;

  //   case ES_TIMEOUT:
  //   {
  //     if (NEXT_STEP_TIMER == ThisEvent.EventParam)
  //     {
  //       SetStepRate(GetStepRateFromDial());
  //       SetCurrTheta(currTheta + dTheta);
  //       StartNextStepTimer();

  //       // Update net steps forward
  //       netStepsForward += (dTheta > 0) ? 1 : -1;
  //       if (checkDrift)
  //       {
  //         if (netStepsForward == driftCheckSteps || netStepsForward == 0)
  //         {
  //           ES_Event_t reverseEvent = {ES_REVERSE_ROTATION, 0};
  //           PostMotorStepService(reverseEvent);
  //         }
  //       }
        
  //     }
  //   }
  //   break;
  // }

  return ReturnEvent;
}