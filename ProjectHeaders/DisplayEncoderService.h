#ifndef DisplayEncoderService_H
#define DisplayEncoderService_H

#include "ES_Types.h"

bool InitDisplayEncoderService(uint8_t Priority);
bool PostDisplayEncoderService(ES_Event_t ThisEvent);
ES_Event_t RunDisplayEncoderService(ES_Event_t ThisEvent);

void B15ToHi();
void B15ToLo();

#endif /* DisplayEncoderService_H */

