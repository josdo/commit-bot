#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "PIC32PortHAL.h"
#include "MotorStepService.h"
#include "PWM.h"
#include "SpeedDialService.h"

// For ISRs
#include <xc.h>
#include <sys/attribs.h>

static uint8_t MyPriority;
static uint16_t StepPeriod;
static uint16_t ControllerUpdatePeriod = 40000;

static void StartNextStepTimer();

void InitVelocityController()
{
  // Setup timer module
  // Turn off T4
  T4CONbits.w = 0;
  // Use PBCLK
  T4CONbits.TCS = 0;
  // Set prescale value to 1:1, which allows for 
  // (2^16-1 ticks) * 50ns/tick * 10^6ms/ns = 3.27ms of time measurement
  T4CONbits.TCKPS = 0;
  // Set PR4 to 2ms, which is 40,000 ticks
  PR4 = ControllerUpdatePeriod - 1;

  // Enable interrupts for timer 2
  __builtin_enable_interrupts(); // global enable
  INTCONbits.w = 0;
  INTCONbits.MVEC = 1; // use multi-vectored interrupts

  IEC0SET = _IEC0_T4IE_MASK; // Enable timer 4 interrupts
  IPC4bits.T4IP = 0b110; // Lower priority than encoder interrupt's priority 7
  IFS0CLR = _IFS0_T4IF_MASK; // reset interrupt flag

  // Turn on T4 module
  T4CONbits.ON = 1;
}

bool InitMotorStepService(uint8_t Priority)
{
  MyPriority = Priority;
  // Initialize timer interrupt updates for the velocity controller.
  InitVelocityController();
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
  static const uint16_t stepDC = 1;
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

// Updates velocity control, i.e. duty cycle applied
void __ISR(_TIMER_4_VECTOR, IPL6SOFT) VelocityControllerISR(void)
{
  // First printed time will be rubbish due to arbitrary initialization
  static uint16_t lastTime = 0;
  // __builtin_disable_interrupts();
  if (IFS0bits.T4IF)
  {
    uint16_t currTime = ES_Timer_GetTime();
    printf("Timer 4 window: %u\n\r", currTime - lastTime);
    lastTime = currTime;
    IFS0CLR = _IFS0_T4IF_MASK;
  }
  // __builtin_enable_interrupts();
}