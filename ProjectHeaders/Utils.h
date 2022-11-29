#ifndef UTILS_H
#define UTILS_H

#include "ES_Configure.h"
#include "ES_Framework.h"

typedef enum {
    LeftDrum_LEDs = 0, RightDrum_LEDs, BottomDrum_LEDs, Clock_LEDs, NoDrum_LEDs
} LED_Types_t;

// typedef enum
// {
//     LeftDrum = 0, RightDrum, BottomDrum, Clock
// }LED_MUX_t;

typedef union
{
  struct
  {
    uint16_t Left : 4;
    uint16_t Bottom : 4;
    uint16_t Right : 4;
    uint16_t Filler : 4;
  };
  uint16_t All;
}Intensities_t;

// set MUX pins as digital outputs
void InitMUXPins(void);

// change the MUX output depending on which LED strip is passed
void SetMuxOutput(LED_Types_t WhichOutput);

// update the fade intensity during IR covered
uint8_t UpdateFadeIntensity(void);

// get the Fade Intensity
uint8_t GetFadeIntensity(void);

// reset the fade intensity to 0
void ResetFadeIntensity(void);

#endif 