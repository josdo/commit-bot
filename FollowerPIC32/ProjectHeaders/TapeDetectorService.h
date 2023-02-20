#ifndef TapeDetectorService_H
#define TapeDetectorService_H

#include "ES_Types.h"

typedef struct {
    bool TapeState;
    uint16_t TapeNumber;
}TapeStateAndNumber;

bool InitTapeDetectorService(uint8_t Priority);
bool PostTapeDetectorService(ES_Event_t ThisEvent);
ES_Event_t RunTapeDetectorService(ES_Event_t ThisEvent);
TapeStateAndNumber tapeSandN(int);
#endif