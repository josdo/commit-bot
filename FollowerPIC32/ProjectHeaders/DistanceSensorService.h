#ifndef DistanceSensorService_H
#define DistanceSensorService_H

#include "ES_Types.h"

// Public Function Prototypes

bool InitDistanceSensorService(uint8_t Priority);
bool PostDistanceSensorService(ES_Event_t ThisEvent);
ES_Event_t RunDistanceSensorService(ES_Event_t ThisEvent);
uint32_t getDistance(void);
#endif /* ServTemplate_H */