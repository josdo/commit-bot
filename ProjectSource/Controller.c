/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Controller.h"
#include "dbprintf.h"
#include "PIC32_AD_Lib.h"
// #include "pc32mx170f256b.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
static ControllerState_t CurrentState;
static uint8_t MyPriority;

// TODO specify in mV
// static float analog_to_mV = 1024.0 / 3300;
// static uint32_t MinPiezoVoltage_mV = 100;
// static uint32_t MaxPiezoVoltage_mV = 1000;
static uint32_t MinPiezoAnalog = 0;
static uint32_t MaxPiezoAnalog = 300;
static uint32_t NumPiezoVoltageBuckets = 9;

// Analog pins for drum piezos
// TODO: update NumANxPins as more added and modify how ADC_MultiRead result is used.
static uint32_t LeftDrumANx = 4; // RB2
static uint32_t BottomDrumANx = 5; // RB3
static uint32_t RightDrumANx = 12; // RB12
static uint32_t NumANxPins = 3;

static uint16_t LastPiezoReadTime;

/*------------------------------ Module Code ------------------------------*/
bool InitController(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  DB_printf("\nInitializing Controller\n");

  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitPState_Controller;

  LastPiezoReadTime = ES_Timer_GetTime();

  // Initialize analog read library
  uint16_t ANxPins = 1 << LeftDrumANx| 1 << BottomDrumANx | 1 << RightDrumANx;
  ADC_ConfigAutoScan(ANxPins, NumANxPins);

  // Post successful initialization
  ThisEvent.EventType = ES_INIT;
  if (ES_PostToService(MyPriority, ThisEvent) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PostController(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunController(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitPState_Controller:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
        // TODO: do something, e.g. set CurrentState
      }
    } break;
  }

  return ReturnEvent;
}

ControllerState_t QueryController(void)
{
  return CurrentState;
}

bool DrumIsHit(void)
{
  static uint32_t LastMaxReading = 0;
  uint16_t CurrPiezoReadTime = ES_Timer_GetTime();
  // if (ES_Timer_GetTime() - LastPiezoReadTime > 1000 * ES_Timer_RATE_1mS)
  if (CurrPiezoReadTime - LastPiezoReadTime > 0)
  {
    uint32_t CurrPiezoReading[3];
    ADC_MultiRead(CurrPiezoReading);
    uint32_t LeftPiezoReading = CurrPiezoReading[0];
    if (LeftPiezoReading >= LastMaxReading)
    {
      LastMaxReading = LeftPiezoReading;
      DB_printf("\n%u\n", LastMaxReading);
    }
    // uint32_t threshold = 20;
    // if (LeftPiezoReading <= threshold)
    // {
    //   LastMaxReading = threshold;
    // }
    LastPiezoReadTime = CurrPiezoReadTime;
  }
  return false;
}

/***************************************************************************
 private functions
 ***************************************************************************/
static uint32_t PiezoReadingToIntensity(uint32_t PiezoReading)
{
  // TODO: after mV reading is confirmed, do bucketing via for loop
  return 0;
}

