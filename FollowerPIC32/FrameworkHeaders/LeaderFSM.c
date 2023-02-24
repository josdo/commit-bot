#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"
#include "../../Shared/ES_Shared_Configure.h"
#include "DCMotor.h"
#include "BeaconSensor.h"
#include "DistanceSensor.h"

// ----------------------------- module vars ----------------------------
static LeaderFSMState_t CurrentState;
static LeaderFSMState_t NextState;

static uint8_t MyPriority;


// -----------------------------------------------------------------------

bool InitLeaderFSM(uint8_t Priority)
{
  MyPriority = Priority;
  CurrentState = InitPState_LeaderFSM;
  
  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostLeaderFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunLeaderFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  NextState = CurrentState;           // assume no change in state

  switch (CurrentState)
  {
    case InitPState_LeaderFSM:
    {
      if (ThisEvent.EventType == ES_INIT)
      {
        DB_printf("In LeaderFSM init\r\n");
        InitDCMotor();            // init the DC motors
        InitBeaconSensor();       // init the beacon sensor
        NextState = AlignWithBeacon_LeaderFSM;  // next state is aligning
      }

      else if (ES_NEW_KEY == ThisEvent.EventType){
        if ('0' == ThisEvent.EventParam){
          DB_printf("STOP motors\r\n");
          setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        }

        else if ('1' == ThisEvent.EventParam){
          DB_printf("FORWARD full speed\r\n");
          setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
        }

        else if ('2' == ThisEvent.EventParam){
          DB_printf("REVERSE full speed\r\n");
          setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, BACKWARD, 100);
        }
      }
    } break;

    case AlignWithBeacon_LeaderFSM:{
      if (ES_NEW_KEY == ThisEvent.EventType){
        if ('a' == ThisEvent.EventParam){
            DB_printf("a was pressed, now aligning with beacon\r\n");
          NextState = AlignWithBeacon_LeaderFSM;        // stay in current state

          ES_Event_t AlignEvent = {ES_BEGIN_ALIGN};
          PostLeaderFSM(AlignEvent);
        }

        else if ('b' == ThisEvent.EventParam){
          NextState = AlignWithBeacon_LeaderFSM;        // stay in current state
          
          ES_Event_t BeaconBEvent = {ES_FOUND_BEACON_B};  // post found beacon B
          PostLeaderFSM(BeaconBEvent);
        }

        else if ('c' == ThisEvent.EventParam){
          NextState = AlignWithBeacon_LeaderFSM;        // stay in current state
          
          ES_Event_t BeaconCEvent = {ES_FOUND_BEACON_C};  // post found beacon B
          PostLeaderFSM(BeaconCEvent);
        }
      }

      else if (ES_BEGIN_ALIGN == ThisEvent.EventType){
          DB_printf("asdfasdfds\r\n");
        NextState = AlignWithBeacon_LeaderFSM;          // stay in current state

        // turn CW until local beacon is found
        setMotorSpeed(LEFT_MOTOR, FORWARD, 50);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 50);

        IEC0SET = _IEC0_IC5IE_MASK;                     // turn on the short range beacon ISR
      }

      else if (ES_FOUND_BEACON_B == ThisEvent.EventType){
        // turn off motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 25);

        DB_printf("Aligned with beacon B\r\n");
        ES_Event_t BackUp = {ES_BACK_UP};
        PostLeaderFSM(BackUp);
      }

      else if (ES_FOUND_BEACON_C == ThisEvent.EventType){
        // turn off motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 25);

        DB_printf("Aligned with beacon C\r\n");
        ES_Event_t BackUp = {ES_BACK_UP};
        PostLeaderFSM(BackUp);
      }
      
      else if(ES_BACK_UP == ThisEvent.EventType){
        uint32_t distance;
        DB_printf("Backing up\r\n");
        do{
            distance = getDistance();
            setMotorSpeed(LEFT_MOTOR, BACKWARD, 25);
            setMotorSpeed(RIGHT_MOTOR, BACKWARD, 25);
        }while(distance > 100);
        setMotorSpeed(LEFT_MOTOR, BACKWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 0);
        DB_printf("Done Backing up\r\n");
        NextState = Idle_LeaderFSM;
      }
      
    }
    break;
    case Idle_LeaderFSM:
    {
        if(ES_NEW_KEY == ThisEvent.EventType){
            if ('1' == ThisEvent.EventParam){
                DB_printf("Go to branch 1\r\n");
            }
            else if ('2' == ThisEvent.EventParam){
                DB_printf("Go to branch 2\r\n");
            }
            else if ('3' == ThisEvent.EventParam){
                DB_printf("Go to branch 3\r\n");
            }
        }
    }
    break;
    

  }

  CurrentState = NextState;     // set the next state
  return ReturnEvent;
}

LeaderFSMState_t QueryLeaderFSM(void)
{
  return CurrentState;
}