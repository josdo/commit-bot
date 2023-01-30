#include "ES_Configure.h"
#include "ES_Framework.h"

typedef union
{
  uint32_t w;
  struct
  {
    uint16_t MSB;
    uint16_t LSB;
  };
} RolloverTime_t;


void InitMeasureEncoder(void);
uint32_t getEncoderHiPulse(void);