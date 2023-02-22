#ifndef BeaconSensor_H
#define BeaconSensor_H

#include "ES_Types.h"

void InitBeaconSensor(void);

typedef enum {
    ShortRangeBeaconSensor = 0,        
    LongRangeBeaconSensor
}BeaconSensor_t;

uint32_t getBeconSensorFreq(BeaconSensor_t whichSensor);

uint32_t getBeaconSensorTick(BeaconSensor_t whichSensor);

#endif

