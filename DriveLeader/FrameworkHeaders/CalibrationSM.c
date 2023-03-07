#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"
#include "CalibrationSM.h"
#include "BeaconSensor.h"
#include "dbprintf.h"
#include "TopHSM.h"
#include "TapeSensor.h"
//#include "../../Shared/EventOverSPI.h"


static CalibrationSMState_t CurrentState;
static ES_Event_t DuringRotateToAlign (ES_Event_t Event);
static ES_Event_t DuringBackUp(ES_Event_t Event);
static ES_Event_t DuringForwardUntilBeacon(ES_Event_t Event);

static const uint8_t NUM_PULSE = 3;
static uint8_t countB = 0;
static uint8_t countC = 0;

static uint16_t stop_ms = 200;

#ifdef DEBUG_ON
static uint32_t a_bit_cm = 20;
static uint32_t backup_speed = 50;
static uint32_t forward_speed = 50;
static uint32_t rotate_speed = 50;
#else
static uint32_t a_bit_cm = 15;
static uint32_t backup_speed = 20;
static uint32_t forward_speed = 40;
static uint32_t rotate_speed = 20;
#endif

ES_Event_t RunCalibrationSM(ES_Event_t CurrentEvent)
{
    bool MakeTransition = false;/* are we making a state transition? */
    CalibrationSMState_t NextState = CurrentState;
    ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
    ES_Event_t ReturnEvent = CurrentEvent; // assume we are not consuming event
    
    switch(CurrentState)
    {       
        case ROTATE_TO_ALIGN:
        {
            CurrentEvent = DuringRotateToAlign(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_NEW_KEY:
                    {
                        if(CurrentEvent.EventParam == 'f')
                        {
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_FOUND_BEACON;
                            NewEvent.EventParam = BeaconB;
                            PostTopHSM(NewEvent);
                        }
                        
                    }
                    break;
                    
                    case ES_FOUND_BEACON:
                    {
                        ES_Event_t BeaconEvent;
                        WhichBeacon_t BeaconName = CurrentEvent.EventParam;
                        if (CurrentEvent.EventParam == BeaconB || CurrentEvent.EventParam == BeaconC) 
                        {
                            
                            NextState = STOP;
                            MakeTransition = true;
                            
                            switch(BeaconName)
                            {
                                case BeaconB:
                                    puts("Beacon B Detected\r\n");
                                    BeaconEvent.EventType = ES_FOUND_BEACON_B;
                                    PostTopHSM(BeaconEvent);
                                    
                                break;
                                case BeaconC:
                                    puts("Beacon C Detected\r\n");
                                    BeaconEvent.EventType = ES_FOUND_BEACON_C;
                                    PostTopHSM(BeaconEvent);
                                break;
                            }
                        }
                    }
                    break;
                    
                }
            
            }
        }
        break;
        
        case STOP:
        {
            if (ES_TIMEOUT == CurrentEvent.EventType && CurrentEvent.EventParam == STOP_TIMER)
            {
                NextState = BACK_UP;
                MakeTransition = true;
            }
        }
        break;
        
        case BACK_UP:
        {   CurrentEvent = DuringBackUp(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_DONE_BACK_UP:
                    {
                        NextState = FORWARD_UNTIL_BEACON;
                        MakeTransition = true;
                    }
                    break;
                }
            }
        }
        break;
        
        case FORWARD_UNTIL_BEACON:
        {
            CurrentEvent = DuringForwardUntilBeacon(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                switch (CurrentEvent.EventType)
                {
                    case ES_NEW_KEY:
                    {
                        if(CurrentEvent.EventParam == 'g')
                        {
                            ES_Event_t NewEvent;
                            NewEvent.EventType = ES_FOUND_BEACON;
                            NewEvent.EventParam = BeaconB;
                            PostTopHSM(NewEvent);
                        }
                        
                    }
                    break;
                    case ES_TRANSLATED:
                    {
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
        CurrentEvent.EventType = ES_EXIT;
        RunCalibrationSM(CurrentEvent);
        
        CurrentState = NextState;
        
        RunCalibrationSM(EntryEventKind);
                
    }
    return ReturnEvent;
}


void StartCalibrationSM( ES_Event_t CurrentEvent )
{
    if (ES_ENTRY_HISTORY != CurrentEvent.EventType)
    {
        CurrentState = ROTATE_TO_ALIGN;
    }
    RunCalibrationSM(CurrentEvent);
}

CalibrationSMState_t QueryCalibrationSM ( void )
{
   return(CurrentState);
}



static ES_Event_t DuringRotateToAlign(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
        setDesiredSpeed(LEFT_MOTOR, FORWARD, rotate_speed);
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, rotate_speed);
    }
    else if (Event.EventType == ES_EXIT)
    {
        ES_Timer_InitTimer(STOP_TIMER, stop_ms);
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
    }
    else
    {
        // run any lower level state machine
        // ReturnEvent = RunLowerLevelSM(Event);
      
        // repeat for any concurrent lower level machines
      
        // do any activity that is repeated as long as we are in this state
    }
    return ReturnEvent;

}
   
static ES_Event_t DuringBackUp(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
        setDesiredSpeed(LEFT_MOTOR, BACKWARD, backup_speed);
        setDesiredSpeed(RIGHT_MOTOR, BACKWARD, backup_speed);
        puts("Moving Back\r\n");
    }
    else if (Event.EventType == ES_EXIT)
    {
        setDesiredSpeed(LEFT_MOTOR, FORWARD, 0);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, 0);
        puts("Stop Moving\r\n");
    }
    else
    {
    }
    return ReturnEvent;
}

static ES_Event_t DuringForwardUntilBeacon(ES_Event_t Event)
{
    ES_Event_t ReturnEvent = Event;
    if ( (Event.EventType == ES_ENTRY) || 
         (Event.EventType == ES_ENTRY_HISTORY))
    {
      drive(FORWARD, a_bit_cm, forward_speed);
    }
    else if (Event.EventType == ES_EXIT)
    {
    }
    else
    {
    }
    return ReturnEvent;
}


bool Check4CornerBeacons(void)
{
    if(CurrentState == ROTATE_TO_ALIGN)
    {
        ES_Event_t ThisEvent;
        WhichBeacon_t BeaconName = getBeaconName(ShortRangeBeaconSensor);
        
        if (BeaconName == BeaconB){
            countB++;
            countC = 0;
        }
        
        else if (BeaconName == BeaconC){
            countB = 0;
            countC++;
        }
        
        else{
            countB = 0;
            countC = 0;
        }
        
        if (countB >= NUM_PULSE || countC >= NUM_PULSE){
            countB = 0;
            countC = 0;
            ThisEvent.EventType   = ES_FOUND_BEACON;
            ThisEvent.EventParam  = BeaconName;
            PostTopHSM(ThisEvent);
            return true;
        }
        
    }
    return false;
}

#define buttonBack PORTBbits.RB15
bool lastBackButtonState = 0;
uint32_t prevTime = 0;

bool Check4InitialDistance(void)
{
    bool ReturnVal = false;
    
    bool val = buttonBack;
    uint32_t currTime = ES_Timer_GetTime();
    
    if(CurrentState == BACK_UP)
    {
        ES_Event_t ThisEvent;
        if ((val != lastBackButtonState) && (currTime - prevTime > 200)) {
            if (val == 1) {
                ThisEvent.EventType   = ES_DONE_BACK_UP;
                PostTopHSM(ThisEvent);
                ReturnVal = true;
            }
            lastBackButtonState = val;    
            prevTime = currTime;
      }
    }
    return ReturnVal;
}

