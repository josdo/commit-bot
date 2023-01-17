/*  Control three parts of stepping: 
    * where is magnetic pull
    * how strong is the pull
    * how quickly does the pull move around the circumference
*/

#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"

/* Safe constructors. */
typedef float phaseV_t;
typedef uint32_t phase_t;
typedef uint32_t channel_t;

void InitPhaseControl();
phaseV_t phaseV(float v);
phase_t phase(uint32_t p);
channel_t channel(uint32_t c);
void GetChannels(phase_t p, channel_t *chs);
channel_t ActiveChannel(phase_t p, bool isForward);
channel_t PassiveChannel(phase_t p, bool isForward);
bool IsForward(phase_t v);
void SetStatorNorth(float theta);
void SetPhaseVoltage(phase_t p, phaseV_t v);