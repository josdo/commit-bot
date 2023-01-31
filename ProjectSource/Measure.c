#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "Measure.h"

// For ISRs
#include <xc.h>
#include <sys/attribs.h>

// Length of high pulse in a PWM period. Read / write is interrupt protected.
volatile static RolloverTime_t currRise = {0};
static const uint32_t maxPR2Value = 0xffff;
static uint32_t encoderPeriod = 0;
static const uint32_t pulsesPerRev = 512;
static const uint32_t ticksPerMin = 1200000000; // 20M ticks / s * 60s / min
static const float gearboxRatio = 5.9;

// Configure 5VT pin B10 for IC2 and timer 2 for IC2.
void InitMeasureEncoder(void)
{
  // Map to IC2 module
  IC2R = 0b0011;

  IC2CONbits.w = 0;     // Turn off and set to defaults
  IC2CONbits.ICM = 0b011; // every rising edge
  IC2CONbits.ICTMR = 1; // Use Timer2
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
uint32_t GetEncoderPeriod(void)
{
  // printf("EPeriod: %u\n\r", encoderPeriod);
  return encoderPeriod;
}

// Split encoder period into bin 1 (smallest) to 8 (largest).
// Bins chosen from empirically observed min and max periods.
uint32_t GetEncoderPeriodBin(void)
{
  static const uint32_t minEncoderPeriod = 10000;
  static const uint32_t maxEncoderPeriod = 25000;
  static const uint32_t numBins = 8;

  uint32_t period = GetEncoderPeriod();
  uint32_t binSize = (maxEncoderPeriod - minEncoderPeriod) / numBins;
  if (period < minEncoderPeriod)
    period = minEncoderPeriod;
  if (period > maxEncoderPeriod)
    period = maxEncoderPeriod;
  
  // Integer division rounds to 0, so quotient has values [0,6], thus +1 needed
  uint32_t bin = (period - minEncoderPeriod) / binSize + 1;
  if (bin > numBins)
    bin = numBins;
  return bin;
}

uint32_t GetEncoderRPM(void)
{
  if (0 == GetEncoderPeriod())
  {
    return 0;
  }
  // ticks / min * pulse / ticks = pulses / min
  float pulsesPerMin = (float) ticksPerMin / (float) GetEncoderPeriod();
  // pulse / min * outer rev / inner rev * inner rev / pulse = rev / min
  float rpm = (float) pulsesPerMin / (gearboxRatio * (float) pulsesPerRev);
  return rpm;
}

// Update MSB of currRise
void __ISR(_TIMER_2_VECTOR, IPL6SOFT) RolloverISR(void)
{
  __builtin_disable_interrupts();
  if (IFS0bits.T2IF)
  {
    currRise.MSB += 1;
    IFS0CLR = _IFS0_T2IF_MASK;
  }
  __builtin_enable_interrupts();
}

// Update currRise and encoderPeriod. Assumes every interrupt is rise.
void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL7SOFT) MeasureEncoderISR(void)
{
  volatile static RolloverTime_t lastRise = {0};

  // Read until FIFO buf is empty
  while (1 == IC2CONbits.ICBNE)
  {
    // currRise
    currRise.LSB = (uint16_t) IC2BUF; 
    if ((IFS0bits.T2IF) && (currRise.LSB < 0x8000))
    {
      currRise.MSB += 1;
      IFS0CLR = _IFS0_T2IF_MASK;
    }

    // encoderPeriod
    encoderPeriod = currRise.w - lastRise.w;
    // printf("%u\n\r", encoderPeriod);
    if (lastRise.w > currRise.w)
    {
      printf("\n\r\n\r");
      printf("currRise %x\n\r", currRise.w);
      printf("lastRise %x\n\r", lastRise.w);
    }
    lastRise = currRise;
  }

  IFS0CLR = _IFS0_IC2IF_MASK; // clear interrupt source
}