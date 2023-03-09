#include "ES_Configure.h"
#include "ES_Framework.h"
#include "dbprintf.h"
#include "TopHSM.h"
#include "GoToBranchOriginSM.h"
#include "ComeBackSM.h"
#include "DCMotor.h"


static ES_Event_t DuringRotateInRepo( ES_Event_t Event);
static ES_Event_t DuringMoveForwardABit( ES_Event_t Event);
static ES_Event_t DuringReverse1ToWall( ES_Event_t Event);
static ES_Event_t DuringReverse2ToWall( ES_Event_t Event);
static ES_Event_t DuringReverseLastToWall( ES_Event_t Event);
GoToBranchOriginState_t CurrentBranch;
static ComeBackState_t CurrentState;

#ifdef DEBUG_ON
static const uint32_t a_bit_cm = 20;
static const uint32_t a_bit_speed = 50;
static const uint32_t rotate_speed = 50;
static const uint32_t reverselast_speed = 100;
#else
static const uint32_t a_bit_cm = 10;
static const uint32_t a_bit_speed = 80;
static const uint32_t rotate_speed = 60;

static const uint32_t reverse1_speed = 75;
static const uint32_t reverse1_cm = 5;
static const uint32_t reverse2_speed = 125;
static const uint32_t reverse2_cm = 5;
static const uint32_t reverselast_speed = 175;

static const uint16_t stop_ms = 500;
#endif

static uint32_t debounce_time = 200;

ES_Event_t RunComeBackSM( ES_Event_t CurrentEvent )
{
   bool MakeTransition = false;/* are we making a state transition? */
   ComeBackState_t NextState = CurrentState;
   ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
   ES_Event_t ReturnEvent = CurrentEvent; // assume we are not consuming event

   switch ( CurrentState )
   {
        case STOP_COME_BACK:
        {
            if (ES_TIMEOUT == CurrentEvent.EventType && CurrentEvent.EventParam == COME_BACK_STOP_TIMER)
            {
                NextState = REVERSE1_TO_WALL;
                MakeTransition = true;
            }
        }
        break;
        

       case REVERSE1_TO_WALL :
           CurrentEvent = DuringReverse1ToWall(CurrentEvent);
         //process any events
         if ( CurrentEvent.EventType != ES_NO_EVENT ) //If an event is active
         {
            switch (CurrentEvent.EventType)
            {
               case ES_TRANSLATED : //If event is event one
               {
                  NextState = REVERSE2_TO_WALL;
                  MakeTransition = true; //mark that we are taking a transition
               }
               break;
            }
         }
       break;

       case REVERSE2_TO_WALL :
           CurrentEvent = DuringReverse2ToWall(CurrentEvent);
         //process any events
         if ( CurrentEvent.EventType != ES_NO_EVENT ) //If an event is active
         {
            switch (CurrentEvent.EventType)
            {
               case ES_TRANSLATED : //If event is event one
               {
                  NextState = REVERSELAST_TO_WALL;
                  MakeTransition = true; //mark that we are taking a transition
               }
               break;
            }
         }
       break;

       case REVERSELAST_TO_WALL :
           CurrentEvent = DuringReverseLastToWall(CurrentEvent);
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
                    
                    CurrentBranch = QueryGoToBranchOriginSM();
                    SetGoToBranchOriginPrevSM(CurrentBranch);
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

/* Stop on entry into ComeBack SM. */
void StartComeBackSM ( ES_Event_t CurrentEvent )
{
   // to implement entry to a history state or directly to a substate
   // you can modify the initialization of the CurrentState variable
   // otherwise just start in the entry state every time the state machine
   // is started
   if ( ES_ENTRY_HISTORY != CurrentEvent.EventType )
   {
      ES_Timer_InitTimer(COME_BACK_STOP_TIMER, stop_ms);
      CurrentState = STOP_COME_BACK;
      setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
      setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
   }
   // call the entry function (if any) for the ENTRY_STATE
   RunComeBackSM(CurrentEvent);
}

ComeBackState_t QueryComeBackSM ( void )
{
   return(CurrentState);
}

static ES_Event_t DuringReverse1ToWall( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
      drive(BACKWARD, reverse1_cm, reverse1_speed);
    }
    else if ( Event.EventType == ES_EXIT )
    {
    }else
    {
    }
    return(ReturnEvent);
}

static ES_Event_t DuringReverse2ToWall( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
      drive(BACKWARD, reverse2_cm, reverse2_speed);
    }
    else if ( Event.EventType == ES_EXIT )
    {
    }else
    {
    }
    return(ReturnEvent);
}

static ES_Event_t DuringReverseLastToWall( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assume no re-mapping or consumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, reverselast_speed);
        setDesiredSpeed(LEFT_MOTOR, BACKWARD, reverselast_speed);
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
        drive(FORWARD, a_bit_cm, a_bit_speed);
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
      rotate90(CW, rotate_speed);
    }
    else if ( Event.EventType == ES_EXIT )
    {
    }else
    {
    }
    return(ReturnEvent);
}

#define backSwitchPort PORTBbits.RB15

bool Check4Wall(void)
{
  static bool lastSwitchState = 0;
  static uint32_t lastTime = 0;
  bool ReturnVal = false;

  bool currSwitchState = backSwitchPort;
  uint32_t currTime = ES_Timer_GetTime();
  bool stateChanged = (currSwitchState != lastSwitchState);
  bool beyondCooldown = (currTime - lastTime > debounce_time);
  if(CurrentState == REVERSELAST_TO_WALL)
  {
    if (stateChanged && beyondCooldown && (currSwitchState == 1)) {
      ES_Event_t ThisEvent = {ES_REACHED_WALL};
      PostTopHSM(ThisEvent);
      ReturnVal = true;
      lastTime = currTime;
    }
  }
  lastSwitchState = currSwitchState;

  return ReturnVal;
}