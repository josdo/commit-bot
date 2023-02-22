#include "ES_Configure.h"
#include "ES_Framework.h"

typedef union
{
  struct
  {
    uint8_t EventType;
    uint8_t EventParam;
  };
  uint16_t w;
} SPI_Event_t;

void InitEventOverSPI(bool isDriveMaster);
bool PostEventOverSPI(ES_Event_t e);
