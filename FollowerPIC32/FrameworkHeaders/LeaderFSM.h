#ifndef LeaderFSM_H
#define LeaderFSM_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */\


typedef enum
{
  InitPState_LeaderFSM,
  AlignAtStart_LeaderFSM
}LeaderFSMState_t;

bool InitLeaderFSM(uint8_t Priority);
bool PostLeaderFSM(ES_Event_t ThisEvent);
ES_Event_t RunLeaderFSM(ES_Event_t ThisEvent);

LeaderFSMState_t QueryLeaderFSM(void);
#endif