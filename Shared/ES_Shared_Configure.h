#ifndef ES_SHARED_CONFIGURE_H
#define ES_SHARED_CONFIGURE_H

/****************************************************************************/
// Name/define the events of interest
// Universal events occupy the lowest entries, followed by user-defined events
typedef enum
{
  ES_NO_EVENT = 0,
  ES_ERROR,                 /* used to indicate an error from the service */
  ES_INIT,                  /* used to transition from initial pseudo-state */
  ES_TIMEOUT,               /* signals that the timer has expired */
  ES_SHORT_TIMEOUT,         /* signals that a short timer has expired */
  /* User-defined events start here */
  ES_NEW_KEY,               /* signals a new key received from terminal */
  ES_LOCK,
  ES_UNLOCK,
  ES_REVERSE_ROTATION,
  ES_START_COM,
  ES_STOP_COM,
  ES_TAPE_DETECTED,
  ES_ButtonDown,
  ES_ButtonUp,
  ES_NEW_COMMAND,
  ES_READ_OPTO,
  ES_STOP_OPTO,
  ES_FOLLOWER_SPI_EVENT,
  ES_TEST_TO_FOLLOWER
}ES_EventType_t;

#endif