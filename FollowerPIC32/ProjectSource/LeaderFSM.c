#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"
#include "../Shared/ES_Shared_Configure.h"

static LeaderFSMState_t CurrentState;
static LeaderFSMState_t NextState;

static uint8_t MyPriority;

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
        InitDCMotor();            // init the DC motors
        NextState = AlignWithBeacon_LeaderFSM;  // next state is aligning
      }

      else if (ES_NEW_KEY == ThisEvent.EventType){
        if ('0' == ThisEvent.EventParam){
          puts('STOP motors\r\n');
          setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        }

        else if ('1' == ThisEvent.EventParam){
          puts('FORWARD full speed\r\n');
          setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
        }

        else if ('2' == ThisEvent.EventParam){
          puts('REVERSE full speed\r\n');
          setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
          setMotorSpeed(RIGHT_MOTOR, BACKWARD, 100);
        }
      }
    } break;

    case AlignWithBeacon_LeaderFSM:{
      if (ES_NEW_KEY == ThisEvent.EventType){
        if ('a' == ThisEvent.EventParam){
          ES_Event_t AlignEvent = {ES_BEGIN_ALIGN};
          PostLeaderFSM(AlignEvent);
        }
      }

      if (ES_BEGIN_ALIGN == ThisEvent.EventType){
        // turn CCW
        setMotorSpeed(LEFT_MOTOR, FORWARD, 50);
        setMotorSpeed(RIGHT_MOTOR, BACKWARD, 50);

        IEC0SET = _IEC0_IC3IE_MASK;
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