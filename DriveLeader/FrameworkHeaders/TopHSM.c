#include "ES_Configure.h"
#include "ES_Framework.h"
#include "dbprintf.h"
#include "../../Shared/EventOverSPI.h"

#include "DCMotor.h"
#include "PushCommitSM.h"
#include "TopHSM.h"
#include "GoToBranchOriginSM.h"
#include "CalibrationSM.h"
#include "ComeBackSM.h"
#include "PIC32PortHAL.h"
#include "Timer5.h"

static MasterState_t CurrentState;
static uint8_t MyPriority;
#define follower_query_timer 20
#define CASE_GAME_OVER \
        case ES_GAME_END:  \
        {                                   \
            MakeTransition = true;          \
            NextState = IDLE;               \
            setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);  \
            setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0); \
        } break;

static ES_Event_t DuringIdle(ES_Event_t Event);
static ES_Event_t DuringCalibration( ES_Event_t Event);
static ES_Event_t DuringGo2BranchOrigin( ES_Event_t Event );
static ES_Event_t DuringPushCommit( ES_Event_t Event );
static ES_Event_t DuringComeBack(ES_Event_t Event);

bool InitTopHSM ( uint8_t Priority )
{
    puts("A NEW START!!!\r\n");
  ES_Event_t ThisEvent;
  
  InitDCMotor(true);
  InitEventOverSPI(true);
  InitTimer5();

//  InitDistanceSensor();
//  InitTapeSensor();
//  InitBeaconSensor();
  // InitDCMotor();
  
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_15);
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_12);
  
  MyPriority = Priority;  // save our priority

  ThisEvent.EventType = ES_ENTRY;
  // Start the Master State machine
  DB_printf("ES_INIT received in Top HSM\r\n");
  StartTopHSM( ThisEvent );
  
  return true;
}

bool PostTopHSM( ES_Event_t ThisEvent )
{
  return ES_PostToService( MyPriority, ThisEvent);
}

ES_Event_t RunTopHSM( ES_Event_t CurrentEvent )
{
   bool MakeTransition = false;/* are we making a state transition? */
   MasterState_t NextState = CurrentState;
   ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
   ES_Event_t ReturnEvent = { ES_NO_EVENT, 0 }; // assume no error

   switch(CurrentState)
   {
       case IDLE: // TODO: QUERY TO FOLLOWER TO SEE WHEN GAME STARTS
       {
//           DB_printf("IDLE STATE\r\n");
           CurrentEvent = DuringIdle(CurrentEvent);
           
           if (CurrentEvent.EventType != ES_NO_EVENT)
           {
               switch(CurrentEvent.EventType)
               {
                   // change this to start btn click event
                   case ES_TIMEOUT:
                   {
                       if (CurrentEvent.EventParam == QUERY_FOLLOWER_TIMER)
                       {
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_NO_EVENT;
                            PostEventOverSPI(NewEvent);
                            ES_Timer_InitTimer(QUERY_FOLLOWER_TIMER, follower_query_timer);
                       }
                   }
                   break;
                   
                   case ES_BUTTON_PRESS:
                   {
                       ES_Timer_StopTimer(QUERY_FOLLOWER_TIMER);
                       DB_printf("TopHSM: got button press (event type %d)\r\n", CurrentEvent.EventType);
                        MakeTransition = true;
                        NextState = CALIBRATION;
                   }      
                   break;
                   CASE_GAME_OVER
               }
           }
       }
       break;
       
       case CALIBRATION:
       {
           CurrentEvent = DuringCalibration(CurrentEvent);
           if (CurrentEvent.EventType != ES_NO_EVENT)
           {
               switch(CurrentEvent.EventType)
               {
                   case ES_FOUND_BEACON_B:
                   {
                       PostEventOverSPI(CurrentEvent);
                       
                   }
                   break;
                   case ES_FOUND_BEACON_C:
                   {
                       PostEventOverSPI(CurrentEvent);
                   }
                   break;
                   case ES_FINISH:
                   {    
                        EntryEventKind.EventType = ES_ENTRY;
                        MakeTransition = true;
                        NextState = GO_TO_BRANCH_ORIGIN;
                   }
                   break;
                   CASE_GAME_OVER
               }
           } 
       }
       break;

       case GO_TO_BRANCH_ORIGIN:
       {
           CurrentEvent = DuringGo2BranchOrigin(CurrentEvent);
           if (CurrentEvent.EventType != ES_NO_EVENT)
           {
               switch(CurrentEvent.EventType)
               {
                   case ES_FINISH:
                   {
                        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
                        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
                        EntryEventKind.EventType = ES_ENTRY;
                        MakeTransition = true;
                        NextState = PUSH_COMMIT;
                   }
                   break;
                   CASE_GAME_OVER
               }
           }
       }
       break;
       
       case PUSH_COMMIT:
       {
           CurrentEvent = DuringPushCommit(CurrentEvent);
           if (CurrentEvent.EventType != ES_NO_EVENT)
           {
               switch(CurrentEvent.EventType)
               {
                   // change this to start btn click event
                   case ES_NEW_KEY:
                   {
                       if (CurrentEvent.EventParam == 'z')
                       {
                           EntryEventKind.EventType = ES_ENTRY;
                            MakeTransition = true;
                            NextState = COME_BACK;
                       }
                   }
                   break;   

                   case ES_FINISH:
                   {
                       EntryEventKind.EventType = ES_ENTRY;
                        MakeTransition = true;
                        NextState = COME_BACK;
                   }
                   break;
                   CASE_GAME_OVER
                }
           }
       }
       break;
       
       case COME_BACK:
       {
           CurrentEvent = DuringComeBack(CurrentEvent);
           if (CurrentEvent.EventType != ES_NO_EVENT)
           {
               switch(CurrentEvent.EventType)
               {
                   // change this to start btn click event
                   case ES_NEW_KEY:
                   {
                       if (CurrentEvent.EventParam == 'x')
                       {
                            EntryEventKind.EventType = ES_ENTRY_HISTORY;
                            puts("COME_BACK\r\n");
                            MakeTransition = true;
                            NextState = GO_TO_BRANCH_ORIGIN;
                       }
                   }
                   break;
                   
                   case ES_FINISH: {
                       EntryEventKind.EventType = ES_ENTRY_HISTORY;
                       MakeTransition = true;
                       NextState = GO_TO_BRANCH_ORIGIN;
                   } 
                   break;
                   CASE_GAME_OVER
               }
           }
       }
       break;  
   }
   
   if (MakeTransition == true)
   {
       //   Execute exit function for current state
       CurrentEvent.EventType = ES_EXIT;
       RunTopHSM(CurrentEvent);

       CurrentState = NextState; //Modify state variable

       // Execute entry function for new state
       // this defaults to ES_ENTRY
       RunTopHSM(EntryEventKind);
   }
   
   return(ReturnEvent);
}


void StartTopHSM (ES_Event_t CurrentEvent)
{
    CurrentState = IDLE;
    
    RunTopHSM(CurrentEvent);
}

MasterState_t  QueryTopHSM ( void )
{
   return(CurrentState);
}

static ES_Event_t DuringIdle( ES_Event_t Event )
{
    ES_Event_t ReturnEvent = Event;
    if ((Event.EventType == ES_ENTRY) || 
        (Event.EventType == ES_ENTRY_HISTORY))
    {
        ES_Timer_InitTimer(QUERY_FOLLOWER_TIMER,follower_query_timer);
    }
    else if ( Event.EventType == ES_EXIT )
    {
        ES_Timer_StopTimer(QUERY_FOLLOWER_TIMER);
    }
    else
    {
        
    }
}

static ES_Event_t DuringCalibration( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assme no re-mapping or comsumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        startGameTimer();
        // implement any entry actions required for this state machine
        
        // after that start any lower level machines that run in this state
        //StartLowerLevelSM( Event );
        // repeat the StartxxxSM() functions for concurrent state machines
        // on the lower level
        
        StartCalibrationSM(Event);
    }
    else if ( Event.EventType == ES_EXIT )
    {
        // on exit, give the lower levels a chance to clean up first
        //RunLowerLevelSM(Event);
        // repeat for any concurrently running state machines
        // now do any local exit functionality
        RunCalibrationSM(Event);
      
    }else
    // do the 'during' function for this state
    {
        // run any lower level state machine
        // ReturnEvent = RunLowerLevelSM(Event);
      
        // repeat for any concurrent lower level machines
      
        // do any activity that is repeated as long as we are in this state
        RunCalibrationSM(Event);
    }
    // return either Event, if you don't want to allow the lower level machine
    // to remap the current event, or ReturnEvent if you do want to allow it.
    return(ReturnEvent);
}


static ES_Event_t DuringGo2BranchOrigin( ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event; // assme no re-mapping or comsumption

    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    { 
        StartGoToBranchOriginSM(Event);
    }
    else if ( Event.EventType == ES_EXIT )
    {
        RunGoToBranchOriginSM(Event);
    }
    else
    {
        RunGoToBranchOriginSM(Event);
    }
    return(ReturnEvent);
}

static ES_Event_t DuringPushCommit(ES_Event_t Event){
    ES_Event_t ReturnEvent = Event;
    
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    {
        StartPushCommitSM(Event);
    }
    else if (Event.EventType == ES_EXIT)
    {
        RunPushCommitSM(Event);
    }
    
    else 
    {
        RunPushCommitSM(Event);
    }
    
    return (ReturnEvent);
}

static ES_Event_t DuringComeBack(ES_Event_t Event){
    ES_Event_t ReturnEvent = Event;
    
    // process ES_ENTRY, ES_ENTRY_HISTORY & ES_EXIT events
    if ( (Event.EventType == ES_ENTRY) ||
         (Event.EventType == ES_ENTRY_HISTORY) )
    { 
        StartComeBackSM(Event);
    }
    else if ( Event.EventType == ES_EXIT )
    {
        RunComeBackSM(Event);
    }
    else
    {
        RunComeBackSM(Event);
    }
    return(ReturnEvent);
}