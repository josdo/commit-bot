#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"
#include "PushCommitSM.h"
#include "GoToBranchOriginSM.h"

static PushCommitSMState_t CurrentState;
static ES_Event_t DuringRotateToFaceBranch(ES_Event_t Event);
static ES_Event_t DuringMoveForward(ES_Event_t Event);
static ES_Event_t DuringBackUpABit(ES_Event_t Event);
static ES_Event_t DuringForwardABit(ES_Event_t Event);


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
                    case ES_TIMEOUT:
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
                    case ES_TIMEOUT:
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
                        NextState = STOP_PUSH_COMMIT;
                        MakeTransition = true;
                    }
                }
            }
        }
        break;
        
        case STOP_PUSH_COMMIT:
        {
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch(CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
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
        }
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
        puts("here1");
        GoToBranchOriginState_t CurrentBranch = QueryGoToBranchOriginSM();
        GoToBranchOriginState_t PrevBrnach = QueryGoToBranchOriginPrevSM();
//        if (CurrentBranch == PrevBrnach)
//        {
//            puts("_-_-_-_-_\r\n");
//            CurrentState = ROTATE_TO_FACE_BRANCH;
//        }
        if(CurrentBranch == BRANCH_THREE)
        {
            CurrentState = BACK_UP_A_BIT;
        }
        else if(CurrentBranch == BRANCH_TWO)
        {
            CurrentState = FORWARD_A_BIT;
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
        setDesiredSpeed(LEFT_MOTOR, BACKWARD, 30);
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, 30);
        ES_Timer_InitTimer(STOP_TIMER, 1200);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
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
        rotate90(CCW);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
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
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 30);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 30);
        ES_Timer_InitTimer(STOP_TIMER, 500);
    }
     else if (Event.EventType == ES_EXIT)
    {
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
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
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 100);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 100);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
        
    }
    else
    {
        
    }
    return ReturnEvent;
}

