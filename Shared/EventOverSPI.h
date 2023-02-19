#include "ES_Configure.h"
#include "ES_Framework.h"

void InitEventOverSPI(bool is_leader);
void PostToOther(ES_Event_t e);
bool PostFromOther(uint16_t word);
bool IsSendableEvent (ES_EventType_t t);