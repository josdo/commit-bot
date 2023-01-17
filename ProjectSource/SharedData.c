#include "SharedData.h"

const float GetSupplyVoltage()
{
  static const float v = 3.3;
  return v;
}