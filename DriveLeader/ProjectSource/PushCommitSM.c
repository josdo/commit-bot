#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"
#include "PushCommitSM.h"
#include "TopHSM.h"
#include "GoToBranchOriginSM.h"
#include "dbprintf.h"

static PushCommitSMState_t CurrentState;
static ES_Event_t DuringRotateToFaceBranch(ES_Event_t Event);
static ES_Event_t DuringMoveForward(ES_Event_t Event);
static ES_Event_t DuringBackUpABit(ES_Event_t Event);
static ES_Event_t DuringForwardABit(ES_Event_t Event);

static const uint32_t drive_forward_speed = 100;
static const uint32_t a_bit_cm = 7;

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
                        ES_Event_t NewEvent;
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
                    }
                }
            }
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
        GoToBranchOriginState_t CurrentBranch = QueryGoToBranchOriginSM();
        GoToBranchOriginState_t PrevBranch = QueryGoToBranchOriginPrevSM();
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
      drive (BACKWARD, a_bit_cm);
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
        rotate90(CCW);
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
      drive (FORWARD, a_bit_cm);
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
      DB_printf("PushCommitSM: Drive forward\r\n");
      drive(FORWARD, 138);
    }
    
    else if (Event.EventType == ES_EXIT)
    {
        
    }
    else
    {
        
    }
    return ReturnEvent;
}

