#ifndef OptoSensorService_H
#define OptoSensorService_H

#include "ES_Types.h"

bool InitOptoSensorService(uint8_t Priority);
bool PostOptoSensorService(ES_Event_t ThisEvent);
ES_Event_t RunOptoSensorService(ES_Event_t ThisEvent);

#endif 