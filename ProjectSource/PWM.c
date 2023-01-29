#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "PWM.h"
#include "SharedData.h"

// Duty cycle from [0, 100] percent
static uint32_t initDutyCycle = 0;
static uint32_t PWMPeriod = 50000;

// Use OC1, T3, and OC pin A0 for PWM with a 200 Hz frequency.
void InitPWM(void)
{
  // Configure PWM pin A0
  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0);

  // Setup timer module
  // Turn off T3
  T3CONbits.w = 0;
  // Use PBCLK
  T3CONbits.TCS = 0;
  // 200 Hz frequency means 5ms per period, which is 100k 50ns ticks of PBCLK.
  // To count one period without overflow with 16bits (~65k), we need to prescale
  // by 2.
  T3CONbits.TCKPS = 0b001;
  // Set period of 5ms, which is 50k ticks.
  PR3 = PWMPeriod - 1;

  // Setup output compare module
  // Turn off OC1
  OC1CONbits.w = 0;
  // Use T3
  OC1CONbits.OCTSEL = 1;
  // Use PWM mode with faults disabled
  OC1CONbits.OCM = 0b110;
  // Set number of ticks of high pulse for each period
  OC1R = PWMPeriod * initDutyCycle / 100;
  OC1RS = PWMPeriod * initDutyCycle / 100;

  // Setup pin for OC1 output
  RPA0Rbits.RPA0R = 0b0101;
  PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0);

  // Enable modules. Must turn on OC1 only after OC1R is written,
  // since OC1R is read-only when OC1 is on.
  OC1CONbits.ON = 1;
  T3CONbits.ON = 1;
}

// Set duty cycle of OC1.
void SetDutyCycle(uint32_t dutyCycle)
{
  if (dutyCycle > 100)
  {
    printf("ERROR: SetDutyCycle argument exceeds max duty cycle");
  }
  // Scale duty cycle range [0-100] to [0-49999]
  OC1RS = (PWMPeriod - 1) * dutyCycle / 100;
}