#include "ES_Configure.h"
#include "ES_Framework.h"

#include "ComeBackSM.h"
#include "DCMotor.h"

#define ENTRY_STATE REVERSE_TO_WALL
#define TURN_90 1000

static ES_Event_t DuringReverseToWall( ES_Event_t Event);
static ES_Event_t DuringRotateInRepo( ES_Event_t Event);


static ComeBackState_t CurrentState;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    RunTemplateSM

 Parameters
   ES_Event_t: the event to process

 Returns
   ES_Event_t: an event to return

 Description
   add your description here
 Notes
   uses nested switch/case to implement the machine.
 Author
   J. Edward Carryer, 2/11/05, 10:45AM
****************************************************************************/
ES_Event_t RunComeBackSM( ES_Event_t CurrentEvent )
{
   bool MakeTransition = false;/* are we making a state transition? */
   ComeBackState_t NextState = CurrentState;
   ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
   ES_Event_t ReturnEvent = CurrentEvent; // assume we are not consuming event

   switch ( CurrentState )
   {
       case REVERSE_TO_WALL :
           CurrentEvent = DuringReverseToWall(CurrentEvent);
         //process any events
         if ( CurrentEvent.EventType != ES_NO_EVENT ) //If an event is active
         {
            switch (CurrentEvent.EventType)
            {
               case ES_FINISH : //If event is event one
                  // Execute action function for state one : event one
                  NextState = ROTATE_IN_REPO;
                  MakeTransition = true; //mark that we are taking a transition
                  // if transitioning to a state with history change kind of entry
                  EntryEventKind.EventType = ES_ENTRY;
                  // optionally, consume or re-map this event for the upper
                  // level state machine
                  ReturnEvent.EventType = ES_NO_EVENT;
                  break;
                // repeat cases as required for relevant events
            }
         }
       break;
       
       case ROTATE_IN_REPO: {
           CurrentEvent = DuringRotateInRepo(CurrentEvent);
           
           if (CurrentEvent.EventType != ES_NO_EVENT){
               switch (CurrentEvent.EventType){
                   case ES_TIMEOUT: {
                       if (TURN_90_TIMER == CurrentEvent.EventParam){
                           puts("90 deg turn timer finished\r\n");
                           setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
                           setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
                       }
                   }
                   break;
               }
           }
       }
       break;
      // repeat state pattern as required for other states
    }
    //   If we are making a state transition
    if (MakeTransition == true)
    {
       //   Execute exit function for current state
       CurrentEvent.EventType = ES_EXIT;
       RunComeBackSM(CurrentEvent);

       CurrentState = NextState; //Modify state variable

       //   Execute entry function for new state
       // this defaults to ES_ENTRY
       RunComeBackSM(EntryEventKind);
     }
     return(ReturnEvent);
}
/****************************************************************************
 Function
     StartTemplateSM

 Parameters
     None

 Returns
     None

 Description
     Does any required initialization for this state machine
 Notes

 Author
     J. Edward Carryer, 2/18/99, 10:38AM
****************************************************************************/
void StartComeBackSM ( ES_Event_t CurrentEvent )
{
   // to implement entry to a history state or directly to a substate
   // you can modify the initialization of the CurrentState variable
   // otherwise just start in the entry state every time the state machine
   // is started
   if ( ES_ENTRY_HISTORY != CurrentEvent.EventType )
   {
        CurrentState = ENTRY_STATE;
   }
   // call the entry function (if any) for the ENTRY_STATE
   RunComeBackSM(CurrentEvent);
}

/****************************************************************************
 Function
     QueryTemplateSM

 Parameters
     None

 Returns
     TemplateState_t The current state of the Template state machine

 Description
     returns the current state of the Template state machine
 Notes

 Author
     J. Edward Carryer, 2/11/05, 10:38AM
****************************************************************************/
ComeBackState_t QueryComeBackSM ( void )
{
   return(CurrentState);
}

/***************************************************************************
 private functions
 ***************************************************************************/

static ES_Event_t DuringReverseToWall( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 50);        // start reversing
        setMotorSpeed(LEFT_MOTOR, BACKWARD, 50);         // start reversing
    }
    else if ( Event.EventType == ES_EXIT )
    {
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);         // stop motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);          // stop motors
      
    }else
    // do the 'during' function for this state
    {
        // run any lower level state machine
        // ReturnEvent = RunLowerLevelSM(Event);
      
        // repeat for any concurrent lower level machines
      
        // do any activity that is repeated as long as we are in this state
    }
    // return either Event, if you don't want to allow the lower level machine
    // to remap the current event, or ReturnEvent if you do want to allow it.
    return(ReturnEvent);
}
static ES_Event_t DuringRotateInRepo( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 50);        // right backwards
        setMotorSpeed(LEFT_MOTOR, BACKWARD, 50);        // left forwards
        
        ES_Timer_InitTimer(TURN_90_TIMER, TURN_90);     // for now turn by time
        puts("Start 90 deg turn timer\r\n");
    }
    else if ( Event.EventType == ES_EXIT )
    {
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);         // stop motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);          // stop motors
      
    }else
    // do the 'during' function for this state
    {
        // run any lower level state machine
        // ReturnEvent = RunLowerLevelSM(Event);
      
        // repeat for any concurrent lower level machines
      
        // do any activity that is repeated as long as we are in this state
    }
    // return either Event, if you don't want to allow the lower level machine
    // to remap the current event, or ReturnEvent if you do want to allow it.
    return(ReturnEvent);
}

