#ifndef LeaderService_H
#define LeaderService_H

#include "ES_Types.h"

bool InitLeaderService(uint8_t Priority);
bool PostLeaderService(ES_Event_t ThisEvent);
ES_Event_t RunLeaderService(ES_Event_t ThisEvent);
void setLeaderMode(void);
void setPWM(void);
#endif 

