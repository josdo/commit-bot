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


static CalibrationSMState_t CurrentState;
static ES_Event_t DuringRotateToAlign (ES_Event_t Event);
static ES_Event_t DuringBackUp(ES_Event_t Event);
static uint8_t MyPriority;

static const uint8_t NUM_PULSE = 3;
static uint8_t countB = 0;
static uint8_t countC = 0;

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
                    case ES_FOUND_BEACON:
                    {
                        WhichBeacon_t BeaconName = CurrentEvent.EventParam;
                        if (CurrentEvent.EventParam == BeaconB || CurrentEvent.EventParam == BeaconC) 
                        {
                            setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
                            setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
                            NextState = BACK_UP;
                            MakeTransition = true;

                            ///////////////////////////
                            switch(BeaconName)
                            {
                                case BeaconB:
                                    puts("Beacon B Detected\r\n");
                                break;
                                case BeaconC:
                                    puts("Beacon C Detected\r\n");
                                break;
                            }
                            ///////////////////////////
                        }
                    }
                    break;
                }
            
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
                        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
                        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
                        puts("Done Backing up\r\n");
                        NextState = FINISH_CALIBRATION;
                        MakeTransition = true;
                        ES_Event_t NewEvent;
                        NewEvent.EventType = ES_FINISH_CALIBRATION;
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
        // implement any entry actions required for this state machine
        
        // after that start any lower level machines that run in this state
        //StartLowerLevelSM( Event );
        // repeat the StartxxxSM() functions for concurrent state machines
        // on the lower level
        // turn CW until local beacon is found
        setMotorSpeed(LEFT_MOTOR, FORWARD, 15);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 15);
        puts("Started Rotating\r\n");
    }
    else if (Event.EventType == ES_EXIT)
    {
        // on exit, give the lower levels a chance to clean up first
        //RunLowerLevelSM(Event);
        // repeat for any concurrently running state machines
        // now do any local exit functionality
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        puts("Stop Rotating\r\n");
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
        setMotorSpeed(LEFT_MOTOR, BACKWARD, 15);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 15);
        puts("Moving Back\r\n");
    }
    else if (Event.EventType == ES_EXIT)
    {
        // on exit, give the lower levels a chance to clean up first
        //RunLowerLevelSM(Event);
        // repeat for any concurrently running state machines
        // now do any local exit functionality
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        puts("Stop Moving\r\n");
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



bool Check4CornerBeacons(void)
{
    if(CurrentState == ROTATE_TO_ALIGN )
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


bool Check4InitialDistance(void)
{
    if(CurrentState == BACK_UP)
    {
        ES_Event_t ThisEvent;
        if (getDistance() < 100)
        {
            ThisEvent.EventType   = ES_DONE_BACK_UP;
            PostTopHSM(ThisEvent);
            return true;
        }
    }
    return false;
}