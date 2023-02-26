#ifndef FollowerService_H
#define FollowerService_H

#include "ES_Types.h"

bool InitFollowerService(uint8_t Priority);
bool PostFollowerService(ES_Event_t ThisEvent);
ES_Event_t RunFollowerService(ES_Event_t ThisEvent);

typedef enum{
    ExecutingCommand = 0,
    NewCommand
} Follower_Response_t;

#endif 

