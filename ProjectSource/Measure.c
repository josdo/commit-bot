#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "Measure.h"

// For ISRs
#include <xc.h>
#include <sys/attribs.h>

// Length of high pulse in a PWM period. Read / write is interrupt protected.
volatile static RolloverTime_t lastEdge = {0};
static uint32_t maxPR2Value = 0xffff;
static uint32_t encoderPeriod = 0;

// Configure 5VT pin B10 for IC2 and timer 2 for IC2.
void InitMeasureEncoder(void)
{
  // Map to IC2 module
  IC2R = 0b0011;

  IC2CONbits.w = 0;     // Turn off and set to defaults
  IC2CONbits.ICM = 0b011; // every rising edge
  // IC2CONbits.ICM = 0b100; // every 4th rising edge
  IC2CONbits.ICTMR = 0; // Use Timer2
  IC2CONbits.FEDGE = 1; // Capture rising edge first

  // Setup timer 2 module
  T2CONbits.w = 0; // Turn off
  T2CONbits.TCS = 0; // Use PBCLK
  T2CONbits.TCKPS = 0b000; // 50ns tick
  PR2 = (uint16_t) maxPR2Value; // Set period to max ticks

  // Enable interrupts for IC2 and timer 2
  __builtin_enable_interrupts(); // global enable
  INTCONbits.w = 0;
  INTCONbits.MVEC = 1; // use multi-vectored interrupts

  IEC0SET = _IEC0_IC2IE_MASK;
  IPC2bits.IC2IP = 0b111; // interrupt priority
  IFS0CLR = _IFS0_IC2IF_MASK; // reset interrupt flag

  IEC0SET = _IEC0_T2IE_MASK; // Enable timer 2 interrupts
  IPC2bits.T2IP = 0b110;
  IFS0CLR = _IFS0_T2IF_MASK; // reset interrupt flag

  // Enable IC2 and timer 2
  T2CONbits.ON = 1;
  IC2CONbits.ON = 1;
}

// encoderPeriod value could be many rollovers large since measuring encoder,
// not PWM hi pulse
uint32_t getEncoderPeriod(void)
{
  printf("Encoder period: %u\n\r", encoderPeriod);
  return encoderPeriod;
}

// Update MSB of lastEdge
void __ISR(_TIMER_2_VECTOR, IPL6SOFT) RolloverISR(void)
{
  __builtin_disable_interrupts();
  if (IFS0bits.T2IF)
  {
    lastEdge.MSB += 1;
    IFS0CLR = _IFS0_T2IF_MASK;
  }
  __builtin_enable_interrupts();
}

// Update lastEdge and encoderPeriod. Assumes first interrupt is rise.
void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL7SOFT) MeasureEncoderISR(void)
{
  static RolloverTime_t lastRise = {0};

  __builtin_disable_interrupts();
  // Read until FIFO buf is empty
  while (1 == IC2CONbits.ICBNE)
  {
    // lastEdge
    lastEdge.LSB = (uint16_t) IC2BUF; 
    if ((IFS0bits.T2IF) && (lastEdge.LSB < 0x8000))
    {
      lastEdge.MSB += 1;
      IFS0CLR = _IFS0_T2IF_MASK;
    }

    // encoderPeriod
    encoderPeriod = lastEdge.w - lastRise.w;
    lastRise = lastEdge;
  }

  IFS0CLR = _IFS0_IC2IF_MASK; // clear interrupt source
  __builtin_enable_interrupts();
}