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
  ES_TEST_TO_FOLLOWER,
  ES_STOP_MOTORS,
  ES_TURN_CCW,
  ES_TURN_CW,
  ES_FORWARD,
  ES_REVERSE,
  ES_BEGIN_ALIGN,
  ES_FOUND_BEACON_B,
  ES_FOUND_BEACON_C,
  ES_BACK_UP,
  ES_EXIT,
  ES_ENTRY,
  ES_ENTRY_HISTORY,
  ES_FOUND_BEACON,
  ES_DONE_BACK_UP,
  ES_FINISH,
  ES_BUTTON_PRESS,
  ES_GAME_START,
  ES_GAME_END,
  ES_REACHED_MIDDLE,
  ES_REACHED_THIRD,
  ES_REACHED_ONE,
  ES_ROTATED,
  ES_FOUND_TAPE,
  NUM_ES_EVENTS,

}ES_EventType_t;

typedef enum{
    BranchErr = 0,
    Branch1,
    Branch2,
    Branch3    
} BranchType_t;

#endif