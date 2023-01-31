#include "ES_Configure.h"
#include "ES_Framework.h"

typedef union
{
  uint32_t w;
  struct
  {
    uint16_t LSB;
    uint16_t MSB;
  };
} RolloverTime_t;


void InitMeasureEncoder(void);
uint32_t GetEncoderPeriod(void);
uint32_t GetEncoderPeriodBin(void);
uint32_t GetEncoderRPM(void);