/*  DC motor drive  */
void Init()
{
  // Configure two motor drive pins to digital output
  // Handover two pins to PWM library

  // Start POLL_SPEED_DIAL_TIMER
}

void Run()
{
  // if ES_TIMEOUT from POLL_SPEED_DIAL_TIMER
    // Poll speed dial (gives uint from 0-100)
    // Set PWM to that duty cycle
}

/*  PWM  */
#include "PIC32PortHAL.h"

// Use OC1, T3, and OC pin A0 for PWM with a 200 Hz frequency.
void Init()
{
  // Setup timer module
  // Turn off T3
  T3CONbits = 0;
  // Use PBCLK
  T3CONbits.TCS = 0;
  // 200 Hz frequency means 5ms per period, which is 100k 50ns ticks of PBCLK.
  // To count one period without overflow with 16bits (~65k), we need to prescale
  // by 2.
  T3CONbits.TCKPS = 0b001;
  // Set period of 5ms, which is 50k ticks.
  PR3 = 49999;

  // Setup output compare module
  // Turn off OC1
  OC1CONbits = 0;
  // Use T3
  OC1CONbits.OCTSEL = 1;
  // Use PWM mode with faults disabled
  OC1CONbits.OCM = 0b110;
  // Set number of ticks of high pulse for each period
  OC1R = defaultDutyCycle;
  OC1RS = defaultDutyCycle;

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
  OC1RS = dutyCycle * 49.999;
}


/*  Measure speed  */
void Init()
{
  // TODO: Setup IC module following lecture slides
  // Setup pin for IC1 output
  // RPA0Rbits.RPA0R = 0b0101;
  // PortSetup_ConfigureDigitalOutputs(_Port_A, _Pin_0);
}

// ISR for encoder input capture
void MeasureEncoderPeriod()
{
  // Keep track of last encoder rise time by reading from IC buf
  // Read until FIFO buf is empty
  // Post event to display service
}

// Displays the last measured period on a 8 segment LED bar.
// A long period lights up all the bars. No very short period lights up one bar.
void DisplayMeasuredPeriodRun()
{
  // if received new measurement event
    // TODO: flesh out
    // Program the ACT
}

// Raises a IO line for time profiling a software operation with an attached oscilloscope
void RaiseIOLine()
{
  // Set a specified pin's latch
}

void LowerIOLine()
{
  // Clear a specified pin's latch
}