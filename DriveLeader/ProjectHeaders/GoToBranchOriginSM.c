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
#include "TapeSensor.h"
#include "PIC32PortHAL.h"
#include "../../Shared/ES_Shared_Configure.h"
#include "../../Shared/EventOverSPI.h"


static GoToBranchOriginState_t CurrentState;
static GoToBranchOriginState_t PrevState;
//static GoToBranchOriginState_t CurrentState = BRANCH_ONE;
static ES_Event_t DuringBranchOne (ES_Event_t Event);
static ES_Event_t DuringBranchTwo (ES_Event_t Event);
static ES_Event_t DuringBranchThree (ES_Event_t Event);

#define QueryTime 100
const uint32_t dist_from_one_to_two = 76;
const uint32_t dist_from_three_to_two = 76;

static const uint32_t debounce_ms = 200;
#define backSwitchState PORTBbits.RB15
#define frontSwitchState PORTBbits.RB12

ES_Event_t RunGoToBranchOriginSM(ES_Event_t CurrentEvent)
{
    bool MakeTransition = false;/* are we making a state transition? */
    CalibrationSMState_t NextState = CurrentState;
    ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
    ES_Event_t ReturnEvent = CurrentEvent; 
    ES_Event_t QueryEvent;
    QueryEvent.EventType = ES_NO_EVENT;
    switch(CurrentState)
    {
        case  BRANCH_ONE:
        {  
            CurrentEvent = DuringBranchOne(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                ES_Event_t NewEvent;
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            PostEventOverSPI(QueryEvent);
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_BUTTON_PRESS:
                    {    
                        if (CurrentEvent.EventParam == Branch1)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1 from branch 1\r\n");
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                        }
                        else if(CurrentEvent.EventParam == Branch2)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2 from branch 1\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_TWO;
                        }
                        else if(CurrentEvent.EventParam == Branch3)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3 from branch 1\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_THREE;
                        }
                    }
                    break;
                    
                    case ES_REACHED_ONE:
                    {
                        
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
                    }
                }
            }
        }
        break;
        
        case BRANCH_TWO:
        {
            CurrentEvent = DuringBranchTwo(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                ES_Event_t NewEvent;
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            PostEventOverSPI(QueryEvent);
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_BUTTON_PRESS:
                    {
                        
                        if (CurrentEvent.EventParam == Branch1)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1 from branch 2\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_ONE;
                        }
                        else if(CurrentEvent.EventParam == Branch2)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2 from branch 2\r\n");
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                        }
                        else if(CurrentEvent.EventParam == Branch3)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3 from branch 2\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_THREE;
                        }
                    }
                    break;
                    
                    case ES_TRANSLATED:
                    {
                        
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
                    }
                    break;
                }
            }
        }
        break;
        
        case BRANCH_THREE:
        {
            CurrentEvent = DuringBranchThree(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                ES_Event_t NewEvent;
                switch (CurrentEvent.EventType)
                {
                    case ES_TIMEOUT:
                    {
                        if (CurrentEvent.EventParam == QUERY_TIMER)
                        {
                            puts("Query the follower\r\n");
                            PostEventOverSPI(QueryEvent);
                            ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
                        }
                    }
                    break;
                    
                    case ES_BUTTON_PRESS:
                    {
                        
                        if (CurrentEvent.EventParam == Branch1)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 1 from branch 3\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_ONE;
                        }
                        else if(CurrentEvent.EventParam == Branch2)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 2 from branch 3\r\n");
                            MakeTransition = true;
                            NextState = BRANCH_TWO;
                        }
                        else if(CurrentEvent.EventParam == Branch3)
                        {
                            ES_Timer_StopTimer(QUERY_TIMER);
                            puts("\tGo to branch 3 from branch 3\r\n");
                            NewEvent.EventType = ES_FINISH;
                            PostTopHSM(NewEvent);
                        }
                    }
                    break;
                    
                    case ES_REACHED_THIRD:
                    {
                        
                        NewEvent.EventType = ES_FINISH;
                        PostTopHSM(NewEvent);
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
        PrevState = BRANCH_ONE;
    }
    
    DB_printf("GoToBranchOrigin: starting from branch %d\r\n", 
                CurrentState+1);
    
    // Front limit switch R12
    ES_Timer_InitTimer(QUERY_TIMER, QueryTime);
    RunGoToBranchOriginSM(CurrentEvent);
}

GoToBranchOriginState_t QueryGoToBranchOriginSM ( void )
{
   return(CurrentState);
}

GoToBranchOriginState_t QueryGoToBranchOriginPrevSM (void)
{
    return(PrevState);
}

static ES_Event_t DuringBranchOne(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
        puts("GoToBranchOrigin: Entering branch 1\r\n");
        if(CurrentState > PrevState){
            setDesiredSpeed(LEFT_MOTOR, FORWARD, 50);
            setDesiredSpeed(RIGHT_MOTOR, FORWARD, 50);
        }
        if(CurrentState < PrevState)
        {
            setDesiredSpeed(LEFT_MOTOR, BACKWARD, 50);
            setDesiredSpeed(RIGHT_MOTOR, BACKWARD, 50);
        }
    }
    else if (Event.EventType == ES_EXIT)
    {
        PrevState = BRANCH_ONE;
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("GoToBranchOrigin: Exit branch 1\r\n");
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
        puts("GoToBranchOrigin: Entering branch 2\r\n");
        if(CurrentState > PrevState){
            drive(FORWARD, dist_from_one_to_two);
        }
        if(CurrentState < PrevState)
        {
            drive(BACKWARD, dist_from_three_to_two);
        }
    }
    else if (Event.EventType == ES_EXIT)
    {
        PrevState = BRANCH_TWO;
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("GoToBranchOrigin: Exit branch 2\r\n");
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
        puts("GoToBranchOrigin: Entering branch 3\r\n");
        if(CurrentState > PrevState){\
            setDesiredSpeed(LEFT_MOTOR, FORWARD, 50);
            setDesiredSpeed(RIGHT_MOTOR, FORWARD, 50);
        }
        if(CurrentState < PrevState)
        {
            setDesiredSpeed(LEFT_MOTOR, BACKWARD, 50);
            setDesiredSpeed(RIGHT_MOTOR, BACKWARD, 50);
        }
    }
    else if (Event.EventType == ES_EXIT)
    {
        PrevState = BRANCH_THREE;
        ES_Timer_StopTimer(QUERY_TIMER);
        puts("GoToBranchOrigin: Exit branch 3\r\n");
    }
    else
    {
        
    }
    return ReturnEvent;
}

bool Check4FirstBranch(void)
{
  static bool lastSwitchState = 0;
  static uint32_t lastTime = 0;

  bool ReturnVal = false;
  bool currSwitchState = backSwitchState;
  uint32_t currTime = ES_Timer_GetTime();
  bool goingIntoBranchOne = CurrentState == BRANCH_ONE && (PrevState == BRANCH_TWO || PrevState == BRANCH_THREE);
  bool stateChanged = currSwitchState != lastSwitchState;
  bool switchPressed = currSwitchState == 1;
  bool doneWithDebounce = currTime - lastTime > debounce_ms;
  if (goingIntoBranchOne && stateChanged && switchPressed && doneWithDebounce)
  {
        ES_Event_t ThisEvent = {ES_REACHED_ONE, 0};
        PostTopHSM(ThisEvent);
        ReturnVal = true;
        lastTime = currTime;
  }
  lastSwitchState = currSwitchState;
  return ReturnVal;
}

bool Check4ThirdBranch(void)
{
  static bool lastSwitchState = 0;
  static uint32_t lastTime = 0;

  bool ReturnVal = false;
  bool currSwitchState = frontSwitchState;
  uint32_t currTime = ES_Timer_GetTime();
  bool goingIntoBranchThree = CurrentState == BRANCH_THREE && (PrevState == BRANCH_TWO || PrevState == BRANCH_ONE);
  bool stateChanged = currSwitchState != lastSwitchState;
  bool switchPressed = currSwitchState == 1;
  bool doneWithDebounce = currTime - lastTime > debounce_ms;
  if (goingIntoBranchThree && stateChanged && switchPressed && doneWithDebounce)
  {
        ES_Event_t ThisEvent = {ES_REACHED_ONE, 0};
        PostTopHSM(ThisEvent);
        ReturnVal = true;
        lastTime = currTime;
  }
  lastSwitchState = currSwitchState;
  return ReturnVal;
}