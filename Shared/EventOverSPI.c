#include "ES_Types.h"
#include "../Shared/ES_Shared_Configure.h"
#include "ES_Events.h"
#include "dbprintf.h"
#include "PIC32_SPI_HAL.h"

/* All events that will be sent to the follower. The event ID
   is its index in this array. */
static ES_EventType_t followerEventTypes[] = {ES_TEST_TO_FOLLOWER};

union SPI_Event
{
  struct
  {
    uint8_t EventType;
    uint8_t EventParam;
  };
  uint16_t w;
};

static bool FitsIn8Bits(uint16_t data);

/* Returns -1 if not found, or the id if found. */
bool IsFollowerEvent (ES_EventType_t t)
{
  for (uint32_t i = 0; i < sizeof(followerEventTypes) / sizeof(followerEventTypes[0]); i++)
  {
    if (t == followerEventTypes[i])
    {
      return true;
    }
  }
  return false;
}

/* Encode event into 16 bits and send over SPI. */
void EncodeSendToFollower(ES_Event_t e)
{
  if (!FitsIn8Bits(e.EventParam) || !FitsIn8Bits(e.EventType))
    DB_printf("ERROR: EventOverSPI.c, EncodeSendToFollower.\r\n");
  
  SPI_Event se = {(uint8_t) e.EventType, (uint8_t) e.EventParam};
  SPIOperate_SPI1_Send16(se.w);
}

/* Decode event from SPI buf and post to all. */
void DecodePostFromFollower()
{
  // TODO
}

static bool FitsIn8Bits(uint16_t data)
{
  return (0 <= data <= 0xff);
}