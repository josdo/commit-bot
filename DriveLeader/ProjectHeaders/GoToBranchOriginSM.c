#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"
#include "CalibrationSM.h"
#include "BeaconSensor.h"
#include "dbprintf.h"
#include "TopHSM.h"
#include "GoToBranchOriginSM.h"

static GoToBranchOriginState_t CurrentState;
//static GoToBranchOriginState_t CurrentState = BRANCH_ONE;
static ES_Event_t DuringBranchOne (ES_Event_t Event);
static ES_Event_t DuringBranchTwo (ES_Event_t Event);
static ES_Event_t DuringBranchThree (ES_Event_t Event);
#define QueryTime 100

ES_Event_t RunGoToBranchOriginSM(ES_Event_t CurrentEvent)
{
    bool MakeTransition = false;/* are we making a state transition? */
    CalibrationSMState_t NextState = CurrentState;
    ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
    ES_Event_t ReturnEvent = CurrentEvent; 
    
    switch(CurrentState)
    {
        case  BRANCH_ONE:
        {  
            CurrentEvent = DuringBranchOne(CurrentEvent);
            puts("In Branch 1\r\n");
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            puts("Query the follower\r\n");
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_NEW_KEY:
                    {
                        
                        if (CurrentEvent.EventParam == '1')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_ONE;
                        }
                        else if(CurrentEvent.EventParam == '2')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_TWO;
                        }
                        else if(CurrentEvent.EventParam == '3')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_THREE;
                        }
                        else if(CurrentEvent.EventParam == 'd')
                        {
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                        }
                    }
                    break;
                }
            }
        }
        break;
        
        case BRANCH_TWO:
        {
            CurrentEvent = DuringBranchTwo(CurrentEvent);
            puts("In branch 2\r\n");
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            puts("Query the follower\r\n");
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_NEW_KEY:
                    {
                        
                        if (CurrentEvent.EventParam == '1')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_ONE;
                        }
                        else if(CurrentEvent.EventParam == '2')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_TWO;
                        }
                        else if(CurrentEvent.EventParam == '3')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_THREE;
                        }
                        else if(CurrentEvent.EventParam == 'j')
                        {
                            puts("here!");
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                            
                        }
                    }
                    break;
                    
                }
            }
        }
        break;
        
        case BRANCH_THREE:
        {
            CurrentEvent = DuringBranchThree(CurrentEvent);
            puts("In branch 3\r\n");
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            puts("Query the follower\r\n");
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_NEW_KEY:
                    {
                        
                        if (CurrentEvent.EventParam == '1')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_ONE;
                        }
                        else if(CurrentEvent.EventParam == '2')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_TWO;
                        }
                        else if(CurrentEvent.EventParam == '3')
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_THREE;
                        }
                        else if(CurrentEvent.EventParam == 'j')
                        {
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                        }
                    }
                    break;
                    
                }
            }
        }
    }
    
    if (MakeTransition == true)
    {
        CurrentEvent.EventType = ES_EXIT;
        RunGoToBranchOriginSM(CurrentEvent);
        
        CurrentState = NextState;
        
        RunGoToBranchOriginSM(EntryEventKind);
                
    }
    return ReturnEvent;
}

void StartGoToBranchOriginSM( ES_Event_t CurrentEvent )
{
    if (ES_ENTRY_HISTORY != CurrentEvent.EventType)
    {
        CurrentState = BRANCH_ONE;
    }
    
    DB_printf("starting gotobranchorigin with currentstate = %d\r\n", 
                CurrentState+1);
    
    ES_Timer_InitTimer(QUERY_TIMER, 1000);
    RunGoToBranchOriginSM(CurrentEvent);
}

GoToBranchOriginState_t QueryGoToBranchOriginSM ( void )
{
   return(CurrentState);
}

static ES_Event_t DuringBranchOne(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
//        ES_Timer_InitTimer(QUERY_TIMER, 1000);
    }
    else if (Event.EventType == ES_EXIT)
    {
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("Exit branch 1\r\n");
    }
    else
    {
        
    }
    return ReturnEvent;
}

static ES_Event_t DuringBranchTwo(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
//        ES_Timer_InitTimer(QUERY_TIMER, 1000);
    }
    else if (Event.EventType == ES_EXIT)
    {
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("Exit branch 2\r\n");
    }
    else
    {
        
    }
    return ReturnEvent;
}

static ES_Event_t DuringBranchThree(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
//        ES_Timer_InitTimer(QUERY_TIMER, 1000);
    }
    else if (Event.EventType == ES_EXIT)
    {
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("Exit branch 3\r\n");
    }
    else
    {
        
    }
    return ReturnEvent;
}