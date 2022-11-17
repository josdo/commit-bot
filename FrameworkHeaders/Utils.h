#ifndef UTILS_H
#define UTILS_H

typedef enum
{
    Drums = 0, Timer, Intensity, None
}LED_MUX_t;

void InitMUXPins(void);

void SetMuxOutput(LED_MUX_t WhichOutput);

#endif 