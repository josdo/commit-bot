#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"
#include "../../Shared/ES_Shared_Configure.h"
#include "DCMotor.h"
#include "BeaconSensor.h"

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
        puts("In LeaderFSM init\r\n");
        InitDCMotor();            // init the DC motors
        InitBeaconSensor();       // init the beacon sensor
        NextState = AlignWithBeacon_LeaderFSM;  // next state is aligning
      }

      else if (ES_NEW_KEY == ThisEvent.EventType){
        if ('0' == ThisEvent.EventParam){
          puts("STOP motors\r\n");
          setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        }

        else if ('1' == ThisEvent.EventParam){
          puts("FORWARD full speed\r\n");
          setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
        }

        else if ('2' == ThisEvent.EventParam){
          puts("REVERSE full speed\r\n");
          setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, BACKWARD, 100);
        }
      }
    } break;

    case AlignWithBeacon_LeaderFSM:{
      if (ES_NEW_KEY == ThisEvent.EventType){
        if ('a' == ThisEvent.EventParam){
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
        NextState = AlignWithBeacon_LeaderFSM;          // stay in current state

        // turn CW until local beacon is found
        setMotorSpeed(LEFT_MOTOR, FORWARD, 50);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 50);

        IEC0SET = _IEC0_IC5IE_MASK;                     // turn on the short range beacon ISR
      }

      else if (ES_FOUND_BEACON_B == ThisEvent.EventType){
        // turn off motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);

        NextState = Idle_LeaderFSM;                     // next state is idling

        puts("Aligned with beacon B\r\n");
      }

      else if (ES_FOUND_BEACON_C == ThisEvent.EventType){
        // turn off motors
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);

        NextState = Idle_LeaderFSM;                     // next state is idling

        puts("Aligned with beacon C\r\n");
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