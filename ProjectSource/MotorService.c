/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "MotorService.h"

/*----------------------------- Module Defines ----------------------------*/
#define ONE_SEC 1000


/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

/*------------------------------ Module Code ------------------------------*/
bool InitMotorService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;

  // Post successful initialization
  ES_Event_t ThisEvent;
  ThisEvent.EventType = ES_INIT;
  if (ES_PostToService(MyPriority, ThisEvent) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PostMotorService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunMotorService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch(ThisEvent.EventType){
      case ES_INIT: {
          
      }
      break;
      
      case ES_CORRECT_HIT: {
          
      }
      break;
      
      case ES_TIMEOUT: {
          
      }
      break;
  }

  return ReturnEvent;
}

/***************************************************************************
 private functions
 ***************************************************************************/

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/

