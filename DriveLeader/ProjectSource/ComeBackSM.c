#include "ES_Configure.h"
#include "ES_Framework.h"
#include "dbprintf.h"
#include "TopHSM.h"

#include "ComeBackSM.h"
#include "DCMotor.h"

#define ENTRY_STATE REVERSE_TO_WALL
#define TURN_90 1000


static ES_Event_t DuringReverseToWall( ES_Event_t Event);
static ES_Event_t DuringRotateInRepo( ES_Event_t Event);
static ES_Event_t DuringMoveForwardABit( ES_Event_t Event);

static ComeBackState_t CurrentState;

#ifdef DEBUG_ON
static const uint32_t a_bit_cm = 20;
static const uint32_t reverse_speed = 100;
#else
static const uint32_t a_bit_cm = 15;
static const uint32_t reverse_speed = 50;
#endif

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
               case ES_REACHED_WALL : //If event is event one
               {
                  NextState = MOVE_FORWARD_A_BIT;
                  MakeTransition = true; //mark that we are taking a transition
               }
               break;
            }
         }
       break;

       case MOVE_FORWARD_A_BIT:
       {
            DB_printf("ComeBackSM: got MOVE_FORWARD_A_BIT\r\n");
            CurrentEvent = DuringMoveForwardABit(CurrentEvent);
            if ( CurrentEvent.EventType != ES_NO_EVENT )
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_TRANSLATED:
                    {
                      DB_printf("ComeBackSM: got ES_TRANSLATED\r\n");
                        NextState = ROTATE_IN_REPO;
                        MakeTransition = true;
                    }
                    break;
                }
            }
       }
       break;

       case ROTATE_IN_REPO: {
           CurrentEvent = DuringRotateInRepo(CurrentEvent);
           
           if (CurrentEvent.EventType != ES_NO_EVENT){
               switch (CurrentEvent.EventType){
                  case ES_ROTATED: {
                    DB_printf("ComeBackSM: got ES_ROTATED\r\n");
                        ES_Event_t NewEvent;
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
                  }
                  break;
               }
           }
       }
       break;
    }

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

ComeBackState_t QueryComeBackSM ( void )
{
   return(CurrentState);
}

static ES_Event_t DuringReverseToWall( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, reverse_speed);
        setDesiredSpeed(LEFT_MOTOR, BACKWARD, reverse_speed);
    }
    else if ( Event.EventType == ES_EXIT )
    {
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, 0);
        setDesiredSpeed(LEFT_MOTOR, BACKWARD, 0);
    }else
    {
    }
    return(ReturnEvent);
}

static ES_Event_t DuringMoveForwardABit( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; 
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        DB_printf("ComeBackSM: drive forward in DuringMoveForwardABit\r\n");
        drive(FORWARD, a_bit_cm);
    }
    else if ( Event.EventType == ES_EXIT )
    {
    }
    else
    {
    }
    return (ReturnEvent);
}

static ES_Event_t DuringRotateInRepo( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
      rotate90(CW);
    }
    else if ( Event.EventType == ES_EXIT )
    {
    }else
    {
    }
    return(ReturnEvent);
}

#define backSwitchPort PORTBbits.RB15
static bool lastSwitchState = 0;

bool Check4Wall(void)
{
  static uint32_t lastTime = 0;
  bool ReturnVal = false;

  bool currSwitchState = backSwitchPort;
  uint32_t currTime = ES_Timer_GetTime();
  bool stateChanged = (currSwitchState != lastSwitchState);
  bool beyondCooldown = (currTime - lastTime > 200);
  if(CurrentState == REVERSE_TO_WALL)
  {
    if (stateChanged && beyondCooldown) { //  && currSwitchState == 1
      ES_Event_t ThisEvent = {ES_REACHED_WALL};
      PostTopHSM(ThisEvent);

      ReturnVal = true;
      lastSwitchState = currSwitchState;
      lastTime = currTime;
    }
  }
  return ReturnVal;
}