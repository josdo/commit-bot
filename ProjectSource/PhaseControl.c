#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PhaseControl.h"
#include "SharedData.h"

#define PhaseA1Latch LATAbits.LATA0
#define PhaseA2Latch LATAbits.LATA1
#define PhaseB1Latch LATAbits.LATA3
#define PhaseB2Latch LATAbits.LATA2
#define EnableALatch LATBbits.LATB3
#define EnableBLatch LATBbits.LATB9

/*  PWM pins chosen as legal for their channel number. */
static const PWM_PinMap_t PhaseA1PWMPin = PWM_RPA0;
static const PWM_PinMap_t PhaseA2PWMPin = PWM_RPA1;
static const PWM_PinMap_t PhaseB1PWMPin = PWM_RPA3;
static const PWM_PinMap_t PhaseB2PWMPin = PWM_RPA2;

static const uint16_t PortASetupPins = _Pin_0 | _Pin_1 | _Pin_2 | _Pin_3;
static const uint16_t PortBSetupPins = _Pin_3 | _Pin_9;

// Phase 1 owns the first row of channels. Phase 2 owns the second row.
static channel_t channelOrder[2][2] = {{1,2},{3,4}};
// = {
//   {channel(1), channel(2)},
//   {channel(3), channel(4)},
// };

// Specific to PWM library
static uint32_t NumPWMChs = 4;
static uint16_t PWMTimerPeriod = 2500;
static uint16_t PWMTimerFreq = 20000;
static const WhichTimer_t PWMTimer = _Timer2_;

void InitPhaseControl()
{
  // Configure pins
  PortSetup_ConfigureDigitalOutputs(_Port_A, PortASetupPins);
  PortSetup_ConfigureDigitalOutputs(_Port_B, PortBSetupPins);

  // Configure PWM
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
  if (abs(v) >= GetSupplyVoltage())
  {
    printf("Invalid phase voltage!");
  }
  return v;
}

/*  Return phase. */
phase_t phase(uint32_t p)
{
  if (1 != p || 2 != p)
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

/*  Gets the pair of channels corresponding to a phase. */
void GetChannels(phase_t p, channel_t *chs)
{
  chs = (phase(1) == p) ? channelOrder[0] : channelOrder[1];
}

/*  Return 1 out of the 2 channels of a phase that will be
  high voltage. */
channel_t ActiveChannel(phase_t p, bool isForward)
{
  channel_t chs[2];
  GetChannels(p, chs);
  // Return the active channel
  return (isForward) ? chs[0] : chs[1];
}

/*  Return 1 out of the 2 channels of a phase that will be
  held low (0 V). */
channel_t PassiveChannel(phase_t p, bool isForward)
{
  channel_t chs[2];
  GetChannels(p, chs);
  // Return the passive channel
  return (isForward) ? chs[1] : chs[0];
}

bool IsForward(phase_t v)
{
  return v > phaseV(0);
}

/*  Set stator's effective north pole.
  Args
    theta: orientation of stator's north pole in radians */
void SetStatorNorth(float theta)
{
  // Set voltage for both terminals of both phase coils
  SetPhaseVoltage(phase(1), sin(theta));
  SetPhaseVoltage(phase(2), cos(theta));
}

/*  Set phase voltage using PWM. */
void SetPhaseVoltage(phase_t p, phaseV_t v)
{
  bool phaseDisabled = (phaseV(0) == v);
  bool isForward = IsForward(v);
  float dutyCycle = abs(v) / GetSupplyVoltage();

  // Temporary implementation for 1 phase on
  if (phase(1) == p)
  {
    EnableALatch = 1;
    PhaseA1Latch = isForward ? 1 : 0;
    PhaseA2Latch = isForward ? 0 : 1;
  }
  else if (phase(2) == p)
  {
    EnableBLatch = 1;
    PhaseB1Latch = isForward ? 1 : 0;
    PhaseB2Latch = isForward ? 0 : 1;
  }

  // // Permanent implementation
  // // Enable
  // if (phase(1) == p)
  // {
  // 	EnableALatch = phaseDisabled ? 0 : 1;
  // }
  // else if (phase(2) == p)
  // {
  // 	EnableBLatch = phaseDisabled ? 0 : 1;
  // }
  // // Set voltage
  // PWMOperate_SetDutyOnChannel(dutyCycle, ActiveChannel(p, isForward));
  // PWMOperate_SetDutyOnChannel(0, PassiveChannel(p, isForward));
}