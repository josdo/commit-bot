#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32PortHAL.h"
#include "PhaseControl.h"
#include "SharedData.h"

#define PhaseA1Latch LATAbits.LATA0
#define PhaseA2Latch LATAbits.LATA1
#define PhaseB1Latch LATAbits.LATA3
#define PhaseB2Latch LATAbits.LATA2
#define EnableALatch LATBbits.LATB3
#define EnableBLatch LATBbits.LATB9
#define PhaseA1Port PORTAbits.RA0
#define PhaseA2Port PORTAbits.RA1
#define PhaseB1Port PORTAbits.RA3
#define PhaseB2Port PORTAbits.RA2

/*  PWM pins chosen as legal for their channel number. */
static const PWM_PinMap_t PhaseA1PWMPin = PWM_RPA0;
static const PWM_PinMap_t PhaseA2PWMPin = PWM_RPA1;
static const PWM_PinMap_t PhaseB1PWMPin = PWM_RPA3;
static const PWM_PinMap_t PhaseB2PWMPin = PWM_RPA2;

static const uint16_t PortASetupPins = _Pin_0 | _Pin_1 | _Pin_2 | _Pin_3;
static const uint16_t PortBSetupPins = _Pin_3 | _Pin_9;

static channel_t channelsPhA[2] = {1,2};
static channel_t channelsPhB[2] = {3,4};

// Specific to PWM library
static uint32_t NumPWMChs = 4;
static uint16_t PWMTimerPeriod = 2500;
static uint16_t PWMTimerFreq = 20000;
static const WhichTimer_t PWMTimer = _Timer3_;

// Specific to lab specs for 100% duty cycle on full step and half step
static bool useMaxDutyCycle = false;

static bool NearZero(phaseV_t v);
static bool IsForward(phaseV_t v);

void InitPhaseControl()
{
  // Configure pins
  PortSetup_ConfigureDigitalOutputs(_Port_A, PortASetupPins);
  PortSetup_ConfigureDigitalOutputs(_Port_B, PortBSetupPins);

 // Configure PWM, disabling any pin response to their latch registers
 PWMSetup_BasicConfig(NumPWMChs);
 PWMSetup_AssignChannelToTimer(channel(1), PWMTimer);
 PWMSetup_AssignChannelToTimer(channel(2), PWMTimer);
 PWMSetup_AssignChannelToTimer(channel(3), PWMTimer);
 PWMSetup_AssignChannelToTimer(channel(4), PWMTimer);
 PWMSetup_SetPeriodOnTimer(PWMTimerPeriod, PWMTimer);
 PWMSetup_SetFreqOnTimer(PWMTimerFreq, PWMTimer);
 PWMSetup_SetFreqOnTimer(PWMTimerFreq, PWMTimer);
 PWMSetup_MapChannelToOutputPin(channel(1), PhaseA1PWMPin);
 PWMSetup_MapChannelToOutputPin(channel(2), PhaseA2PWMPin);
 PWMSetup_MapChannelToOutputPin(channel(3), PhaseB1PWMPin);
 PWMSetup_MapChannelToOutputPin(channel(4), PhaseB2PWMPin);
}

/*  Return phase voltage. */
phaseV_t phaseV(float v)
{
  if (fabs(v) >= GetSupplyVoltage())
  {
    printf("Invalid phase voltage!");
  }
  return v;
}

/*  Return phase. */
phase_t phase(uint32_t p)
{
  if (1 != p && 2 != p)
  {
    printf("Invalid phase!");
  }
  return p;
}

channel_t channel(uint32_t c)
{
  if (1 > c || 4 < c)
  {
    printf("Invalid channel!");
  }
  return c;
}

static bool NearZero(phaseV_t v)
{
  static const float eps = 0.001;
  return fabs(v) < eps;
}

/*  Return 1 out of the 2 channels of a phase that will be
  high voltage. */
channel_t ActiveChannel(phase_t p, bool isForward)
{
  if (phase(1) == p)
  {
    channel_t ch = isForward ? channelsPhA[0] : channelsPhA[1];
    return ch;
  }
  channel_t ch = isForward ? channelsPhB[0] : channelsPhB[1];
  return ch;
}

/*  Return 1 out of the 2 channels of a phase that will be
  held low (0 V). */
channel_t PassiveChannel(phase_t p, bool isForward)
{
  if (phase(1) == p)
  {
    return isForward ? channelsPhA[1] : channelsPhA[0];
  }
  return isForward ? channelsPhB[1] : channelsPhB[0];
}

static bool IsForward(phaseV_t v)
{
  return (v > 0.0);
}

void SetUseMaxDutyCycle(bool b)
{
  useMaxDutyCycle = b;
}

/*  Set stator's effective north pole.
  Args
    theta: orientation of stator's north pole in radians */
void SetStatorNorth(float theta)
{
  // Set voltage for both terminals of both phase coils
  SetPhaseVoltage(phase(1), sin(theta) * GetSupplyVoltage());
  SetPhaseVoltage(phase(2), cos(theta) * GetSupplyVoltage());
}

/*  Set phase voltage using PWM. */
void SetPhaseVoltage(phase_t p, phaseV_t v)
{
  bool phaseDisabled = NearZero(v);
  bool isForward = IsForward(v);
  uint8_t dutyCycle = round(100.0 * fabs(v / GetSupplyVoltage()));
  if (useMaxDutyCycle)
  {
    dutyCycle = 100;
  }

  // Enable H-bridge
  if (phase(1) == p)
  {
  	EnableALatch = phaseDisabled ? 0 : 1;
  }
  else if (phase(2) == p)
  {
  	EnableBLatch = phaseDisabled ? 0 : 1;
  }

  // Set voltage across coil
  if (!phaseDisabled)
  {
    // printf("A: %u   D: %u\n\r", ActiveChannel(p, isForward), dutyCycle);
  }
  bool status = PWMOperate_SetDutyOnChannel(dutyCycle, ActiveChannel(p, isForward));
  status = PWMOperate_SetDutyOnChannel(0, PassiveChannel(p, isForward));
}