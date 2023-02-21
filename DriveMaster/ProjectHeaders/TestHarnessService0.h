#ifndef TestHarnessService0_H
#define TestHarnessService0_H

#include <stdint.h>
#include <stdbool.h>

#include "ES_Events.h"
#include "ES_Port.h"                // needed for definition of REENTRANT

bool InitTestHarnessService0(uint8_t Priority);
bool PostTestHarnessService0(ES_Event_t ThisEvent);
ES_Event_t RunTestHarnessService0(ES_Event_t ThisEvent);

#endif /* ServTemplate_H */

