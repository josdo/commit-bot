#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "Measure.h"

// For ISRs
#include <xc.h>
#include <sys/attribs.h>

// Length of high pulse in a PWM period. Read / write is interrupt protected.
volatile static RolloverTime_t lastEdge = {0};
static uint32_t encoderHiPulse = 0;

// Configure 5VT pin B10 for IC2. Depends on Timer3 initialization by PWM.c
void InitMeasureEncoder(void)
{
  // Map to IC2 module and configure to digital input
  RPB10Rbits.RPB10R = 0b0011;
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_10); // TODO: digital or analog input?

  IC2CONbits.w = 0;     // Turn off and set to defaults
  IC2CONbits.ICM = 0b110; // First edge then every edge after
  IC2CONbits.ICTMR = 0; // Use Timer2
  IC2CONbits.FEDGE = 1; // Capture rising edge first

  // Setup timer 2 module
  T2CONbits.w = 0; // Turn off
  T2CONbits.TCS = 0; // Use PBCLK
  T2CONbits.TCKPS = 0b001; // 100ns tick, matches timer 3 managed by PWM.c
  PR3 = 0xffff; // Set period to max ticks

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
  IC2CONbits.ON = 1;
  T2CONbits.ON = 1;
}

// encoderHiPulse value could be many rollovers large since measuring encoder,
// not PWM hi pulse
uint32_t getEncoderHiPulse(void)
{
  return encoderHiPulse;
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

// Update lastEdge and encoderHiPulse
void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL7SOFT) MeasureEncoderISR(void)
{
  static RolloverTime_t lastRise = {0};
  static RolloverTime_t lastFall = {0};
  static bool isRise = true;

  // Read until FIFO buf is empty
  while (0 != IC2CONbits.ICBNE)
  {
    // lastEdge
    __builtin_disable_interrupts();
    if (IFS0bits.T2IF)
    {
      lastEdge.MSB += 1;
      IFS0CLR = _IFS0_T2IF_MASK;
    }
    lastEdge.LSB = (uint16_t) IC2BUF; 
    __builtin_enable_interrupts();

    // encoderHiPulse
    if (isRise)
    {
      lastRise = lastEdge;
      isRise = false;
    }
    else
    {
      lastFall = lastEdge;
      isRise = true;
      uint32_t encoderHiPulse = lastFall.w - lastRise.w;
    }
  }

  IFS0CLR = _IFS0_IC2IF_MASK; // clear interrupt source
}