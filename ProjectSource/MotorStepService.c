#include <stdio.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "PIC32PortHAL.h"
#include "Measure.h"
#include "MotorStepService.h"
#include "PWM.h"
#include "SpeedDialService.h"

// For ISRs
#include <xc.h>
#include <sys/attribs.h>

static uint8_t MyPriority;

// Desired RPM for velocity controller to reach
static int32_t rpm_desired = 0;

// Last time the velocity controller printed its stats
static uint16_t lastPrintTime;

// How often to read from the speed dial
static uint16_t StepPeriod = 1000;
static void StartNextStepTimer();

void InitVelocityController()
{
  // How frequently the controller updates
  static uint16_t ControllerUpdatePeriod = 40000;

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

  // Ensure ISR printing is ready to go
  lastPrintTime = ES_Timer_GetTime();
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

  StepPeriod = 1000;
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
  // Either use the keys, or use the speed dial, to set the desired RPM
  bool use_dial = true;

  static const uint16_t step_rpm = 10;

  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_NEW_KEY:
    {
      if (use_dial)
        break;

      if ('k' == ThisEvent.EventParam && rpm_desired < 45)
      {
        rpm_desired += step_rpm;
        printf("Up to %u%% rpm\n\r", rpm_desired);
      }
      else if ('j' == ThisEvent.EventParam && rpm_desired > 0)
      {
        rpm_desired -= step_rpm;
        printf("Dn to %u%% rpm\n\r", rpm_desired);
      }
    } break;

    case ES_TIMEOUT:
    {
      if (!use_dial)
        break;

      if (NEXT_STEP_TIMER == ThisEvent.EventParam)
      {
        rpm_desired = (int32_t) DialRPM();
        StartNextStepTimer();
      }
    }
    break;
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
  // How often to print
  static uint16_t printPeriod = 60;

  static float kP = 1;
  static float kI = 1;
  static float curr_cum_e = 0;
  static float last_cum_e = 0;

  int32_t rpm_actual = (int32_t) GetEncoderRPM();
  int32_t e = rpm_desired - rpm_actual;
  last_cum_e = curr_cum_e;
  curr_cum_e += e;

  if (IFS0bits.T4IF)
  {
    float candidate_dc = kP * (e + (kI * curr_cum_e));
    uint32_t final_dc;
    // Clamp cumulative error if it drives the commanded duty cycle out of
    // valid range
    if (candidate_dc > 100 || candidate_dc < 0)
    {
      curr_cum_e = last_cum_e;
      final_dc = (candidate_dc > 100) ? 100 : 0;
    }
    else
    {
      final_dc = round(candidate_dc);
    }
    SetDutyCycle(final_dc);

    uint16_t currTime = ES_Timer_GetTime();
    if (currTime - lastPrintTime >= printPeriod)
    {
      printf("Desired %u vs actual %u\r\n", rpm_desired, rpm_actual);
      printf("DC: %u\r\n", final_dc);
      printf("\r\n");
      lastPrintTime = currTime;
    }
    IFS0CLR = _IFS0_T4IF_MASK;
  }
}