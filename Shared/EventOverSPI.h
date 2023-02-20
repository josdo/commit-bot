#include "ES_Configure.h"
#include "ES_Framework.h"

void InitEventOverSPI(bool is_leader);
void PostToOther(ES_Event_t e);
bool PostFromOther(uint16_t word);

/* Usage
leader event > pump > follower no event

leader no event > pump > follower event

If the leader always pumps, then the follower will always
be interrupted. Is there a way to avoid this?
* Turning on interrupts from the leader pic
* From the follower pic, issuing a signal to the leader pic via a free pin

Could also query the follower pic. Just like the command generator.

If the follower pic were the game play HSM, then we could get what to do next
after we're finished.

The command generator keeps track of game state. The leader keeps querying.

When the follower is finished executing its task, it sends an event to the leader
asking for what's next.

------------------------

Leader: driver and sensors
Follower: game manager

Driver sends events to game manager.
Driver polls game manager every 50ms for events -- sends one 0xAA and continues sending until receives 

Drive manager sends 0xAAAA 

Game manager receive ISR:
* If got 0xAAAA or another event type:
  * Post event (if not 0xAAAA)
  * If something queued up
    * Send SPI_Event_t
  * Else
    * Send 0xFFFF

Drive manager receiver ISR:
* If got a SPI_Event_t:
  * Post event
* If got something other than 0xFFFF:
  * Don't do anything, but print warning message about noisy signal coming across.

Leader's polling service
  Every 100ms, call EOS_PostToOther(ES_QueryFollowerForEvent)

EOS_PostToOther(ES_Event_t e)
  Encode event into word
  If isLeader:
    Send word
  Else:
    Queue word, which will get sent by the ISR

EOS_NextWordToLeader()
  return next word in queue, or 0xFFFF if queue is empty

EOS_ISR()
  Read word from buffer and reset RXIF
  If isLeader:
    If received an event (word.EventType is valid):
      Post to all
      Get any more queued events (EOS_PostToOther(ES_QueryFollowerForEvent))
    Else:
      Ignore since not an event
      But print warning message if not 0xFFFF, since that means noise
  Else:
    If received an event (word.EventType is valid):
      If not ES_QueryFollowerForEvent:
        Post to all
      EOS_PostToOther(NextWordToLeader())
    Else:
      No valid event
      Post ES_NoEvents
      Send 0xFFFF

TODO: send word or send event function? Seems like send word is better and faster.
    
*/