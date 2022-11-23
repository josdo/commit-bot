#ifndef Controller_H
#define Controller_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

#include "Utils.h"

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  InitPState_Controller, IRCoveredState_Controller, WelcomingState_Controller,
  PlayingState_Controller, PlayedCorrectNoteState_Controller, ZenState_Controller
}ControllerState_t;

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
bool InitController(uint8_t Priority);

/*
Params: 
  ES_Event_t, the event to post to the queue
Return:
  boolean False if the Enqueue operation failed, True otherwise
Description:
  Posts an event to this state machine's queue
*/
bool PostController(ES_Event_t ThisEvent);

/*
Params: 
  ES_Event_t, the event to process
Return:
  ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise
Description:
  returns the current state of the Template state machine
*/
ES_Event_t RunController(ES_Event_t ThisEvent);

/*
Params:
  None
Return:
  TemplateState_t The current state of the Template state machine
Description:
  Returns the current state of the Template state machine
*/
ControllerState_t QueryController(void);

/*
Params
  None
Return
  bool: true if above minimum voltage threshold, false otherwise
Description
  Reads analog pins connected to drum piezos. If any drum is above the minimum analog threshold,
  this event checker returns true, updates the module's intensities, and posts ES_DrumsHit to 
  the Controller service.
*/
bool DrumsAreHit(void);

// TODO add comment
bool ButtonPressed(void);
void ReadAnalogIR(uint32_t *Buffer);
void ReadAnalogPiezos(uint32_t *Buffer);

bool checkIRSensor(void);

// Initialize motor pins to digital output
static bool InitMotors();

/*
Params
  uint32_t analog value (0-1023)
Return
  uint32_t: intensity level
Description
  Returns hit intensity level corresponding to analog input.
*/
static uint32_t AnalogToIntensity(uint32_t Analog);


static void StartNextNoteWindow(void);

/*
Params
Return
Description
    Resets interaction timer.
*/
static void RestartInteractionTimer(void);

/*
Params
    Intensities, from the ES_DRUMS_HIT event param
Return
Description
    Updates the module level variables tracking the drums hit in
    the current note window.
*/
static void UpdateWhichDrumsHit(Intensities_t NewDrumIntensities);

/*
Params
Return
Description
    Clears to false the module level variables tracking the drums hit.
*/
static void ClearWhichDrumsHit(void);


/*
Params
Return
    bool
Description
    Returns if all the correct drums and only the correct drums are hit
    in this note window.
    TODO: generalize to multiple drums
*/
static bool IsCorrectHit(void);

#endif /* Controller_H */

