#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"
#include "PushCommitSM.h"
#include "TopHSM.h"
#include "GoToBranchOriginSM.h"
#include "dbprintf.h"
#include "DistanceSlider.h"

static PushCommitSMState_t CurrentState;
static ES_Event_t DuringRotateToFaceBranch(ES_Event_t Event);
static ES_Event_t DuringSlowMoveForward(ES_Event_t Event);
static ES_Event_t DuringMoveForward(ES_Event_t Event);
static ES_Event_t DuringBackUpABit(ES_Event_t Event);
static ES_Event_t DuringForwardABit(ES_Event_t Event);

#ifdef DEBUG_ON
static const uint32_t slow_forward_speed = 150;
static const uint32_t forward_speed = 100;
static const uint32_t a_bit_speed = 50;
static const uint32_t a_bit_cm = 10;
static const uint32_t rotate_speed = 40;
#else
static const uint32_t slow_forward_speed = 50;
static const uint32_t forward_speed = 150;
static const uint32_t a_bit_speed = 40;
static const uint32_t a_bit_cm = 15;
static const uint32_t rotate_speed = 40;

static const float slow_forward_cm = 15;

#endif

ES_Event_t RunPushCommitSM(ES_Event_t CurrentEvent)
{
    bool MakeTransition = false;/* are we making a state transition? */
    PushCommitSMState_t NextState = CurrentState;
    ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
    ES_Event_t ReturnEvent = CurrentEvent;
    
    switch(CurrentState)
    {
        case BACK_UP_A_BIT:
        {
            CurrentEvent = DuringBackUpABit(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_TRANSLATED:
                    {
                        NextState = ROTATE_TO_FACE_BRANCH;
                        MakeTransition = true;
                    }
                }
            }
        }
        break;
        
        case FORWARD_A_BIT:
        {
            CurrentEvent = DuringForwardABit(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_TRANSLATED:
                    {
                        NextState = ROTATE_TO_FACE_BRANCH;
                        MakeTransition = true;
                    }
                }
            }
        }
        break;
        
        case ROTATE_TO_FACE_BRANCH:
        {
            CurrentEvent = DuringRotateToFaceBranch(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_ROTATED:
                    {
                        DB_printf("PushCommitSM: Finished rotating to face branch\r\n");
                        NextState = SLOW_MOVE_FORWARD;
                        MakeTransition = true;
                    }
                }
            }
        }
        break;

        case SLOW_MOVE_FORWARD:
        {
            CurrentEvent = DuringSlowMoveForward(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_TRANSLATED:
                    {
                      DB_printf("PushCommitSM: done SLOWER move forward\r\n");
                      NextState = MOVE_FORWARD;
                      MakeTransition = true;
                    }
                }
            }
        }
        break;
        
        case MOVE_FORWARD:
        {
            CurrentEvent = DuringMoveForward(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_TRANSLATED:
                    {
                      DB_printf("PushCommitSM: done FASTER move forward\r\n");
                        ES_Event_t NewEvent;
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
                    }
                }
            }
        }
        break;
    }
    
    if (MakeTransition == true)
    {
        CurrentEvent.EventType = ES_EXIT;
        RunPushCommitSM(CurrentEvent);
        
        CurrentState = NextState;
        
        RunPushCommitSM(EntryEventKind);
                
    }
    return ReturnEvent;
}



void StartPushCommitSM( ES_Event_t CurrentEvent )
{
    if (ES_ENTRY_HISTORY != CurrentEvent.EventType)
    {
        GoToBranchOriginState_t CurrentBranch = QueryGoToBranchOriginSM();
        GoToBranchOriginState_t PrevBranch = QueryGoToBranchOriginPrevSM();
        DB_printf("PushCommitSM: Previous Branch : %d\r\n", PrevBranch + 1);
        DB_printf("PushCommitSM: Current Branch : %d\r\n", CurrentBranch + 1);
       if (CurrentBranch == PrevBranch)
       {
           CurrentState = ROTATE_TO_FACE_BRANCH;
       }

        else if(CurrentBranch == BRANCH_THREE)
        {
            CurrentState = BACK_UP_A_BIT;
        }
        else if(CurrentBranch == BRANCH_TWO)
        {
            CurrentState = ROTATE_TO_FACE_BRANCH;
        }
        else if(CurrentBranch == BRANCH_ONE)
        {
            CurrentState = FORWARD_A_BIT;
        }

    }
    RunPushCommitSM(CurrentEvent);
}

PushCommitSMState_t QueryPushCommitSM ( void )
{
   return(CurrentState);
}


static ES_Event_t DuringBackUpABit(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
      drive(BACKWARD, a_bit_cm, a_bit_speed);
    }
    else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}

static ES_Event_t DuringRotateToFaceBranch(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
        rotate90(CCW, rotate_speed);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}

static ES_Event_t DuringForwardABit(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
      drive(FORWARD, a_bit_cm, a_bit_speed);
    }
     else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}

static ES_Event_t DuringSlowMoveForward(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
      drive(FORWARD, slow_forward_cm, slow_forward_speed);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}


static ES_Event_t DuringMoveForward(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
      drive(FORWARD, getDesiredBranchDistance() - slow_forward_cm, forward_speed);
      
    }
    
    else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}

