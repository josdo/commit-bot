#ifndef DRUM_LEDFSM_H
#define DRUM_LEDFSM_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */
#include "Utils.h"

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  InitPState_Drums, WelcomingState_Drums, IRCoveredState_Drums, 
  IRUncoveredState_Drums, PlayingState_Drums, ZenState_Drums
}LEDFSMState_t;


// Public Function Prototypes

/*
Params: 
     uint8_t : the priorty of this service
Return:
     bool, false if error in initialization, true otherwise
Description:
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
*/
bool InitDRUM_LEDFSM(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostDRUM_LEDFSM(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunDRUM_LEDFSM(ES_Event_t ThisEvent);

/*
Params:
  None
Return:
  TemplateState_t The current state of the Template state machine
Description:
  Returns the current state of the Template state machine
*/
LEDFSMState_t QueryLEDFSM(void);

/*
Update MinBrightness module variable.
*/
bool Update_DrumIntensity(uint8_t NewIntensity);


/*
Description:
  Posts a ES_UPDATING_LED event back to DRUM_LEDFSM with the new color and brightness 
  for the specified drum.
*/
static void LightDrum(LED_Types_t Drum, uint32_t Color, uint32_t Brightness);

#endif /* TemplateFSM_H */

