#ifndef UTILS_H
#define UTILS_H

typedef enum
{
    LeftDrum = 0, RightDrum, BottomDrum, Clock
}LED_MUX_t;

void InitMUXPins(void);

void SetMuxOutput(LED_MUX_t WhichOutput);

#endif 