#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LeaderFSM.h"
#include "DCMotor.h"
#include "DistanceSensor.h"
#include "FollowTapeSM.h"
#include "dbprintf.h"
#include "TopHSM.h"
#include "TapeSensor.h"


static FollowTapeSMState_t CurrentState;
static ES_Event_t DuringRotate90 (ES_Event_t Event);
static ES_Event_t FollowTape (ES_Event_t Event);

static uint8_t MyPriority;

ES_Event_t RunFollowTapeSM(ES_Event_t CurrentEvent)
{
    bool MakeTransition = false;/* are we making a state transition? */
    CalibrationSMState_t NextState = CurrentState;
    ES_Event_t EntryEventKind = { ES_ENTRY, 0 };// default to normal entry to new state
    ES_Event_t ReturnEvent = CurrentEvent; // assume we are not consuming event
    
    switch(CurrentState)
    {
        case ROTATE_90:
        {
            CurrentEvent = DuringRotate90(CurrentEvent);
            if(CurrentEvent.EventType != ES_NO_EVENT)
            {
                rotate90CW
            }
        }
    }
}