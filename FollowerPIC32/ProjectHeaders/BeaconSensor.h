#ifndef BeaconSensor_H
#define BeaconSensor_H

#include "ES_Types.h"

void InitBeaconSensor();

typedef enum {
    ShortRangeBeaconSensor = 0,        
    LongRangeBeaconSensor
}BeaconSensor_t;

uint32_t getBeconSensorFreq(BeaconSensor_t);

#endif

