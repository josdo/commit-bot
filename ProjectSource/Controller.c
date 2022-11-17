/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Controller.h"
// #include "dbprintf.h"
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
static uint32_t MinPiezoAnalog = 10;
static uint32_t MaxPiezoAnalog = 300;
static uint32_t NumPiezoIntensities = 9;

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

  // DB_printf("\nInitializing Controller\n");
  printf("\nInitializing Controller\n");

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

bool DrumsAreHit(void)
{
  uint32_t PiezosAnalog[3];
  ADC_MultiRead(PiezosAnalog);
  // TODO remove debug short circuit
  if (PiezosAnalog[0] < MinPiezoAnalog & PiezosAnalog[1] < MinPiezoAnalog
     & PiezosAnalog[2] < MinPiezoAnalog)
  {
    return false;
  }
  uint32_t LeftIntensity = AnalogToIntensity(PiezosAnalog[0]);
  // TODO unmagic the Right and Bottom intensities by moving this into analog module
  // uint32_t BottomIntensity = AnalogToIntensity(PiezosAnalog[1]);
  // uint32_t RightIntensity = AnalogToIntensity(PiezosAnalog[2]);
  uint32_t BottomIntensity = 0;
  uint32_t RightIntensity = 0;
  if (1 <= LeftIntensity || 1 <= BottomIntensity || 1 <= RightIntensity)
  {
    Intensities_t DrumIntensities = {{LeftIntensity, BottomIntensity, RightIntensity}};
    // Intensities_t DrumIntensities = {LeftIntensity, BottomIntensity, RightIntensity};
    ES_Event_t DrumsHit = {ES_DRUMS_HIT, DrumIntensities.All};
    PostController(DrumsHit);
    return true;
  }
  return false;
}

/***************************************************************************
 private functions
 ***************************************************************************/
static uint32_t AnalogToIntensity(uint32_t Analog)
{
  if (0 > Analog || 1023 < Analog)
  {
    // DB_printf("Invalid analog reading given");
    printf("Invalid analog reading given");
    return 0;
  }
  // If analog is outside min max range
  if (Analog <= MinPiezoAnalog)
  {
    return 0;
  }
  if (Analog >= MaxPiezoAnalog)
  {
    // DB_printf("Piezo analog exceeded maximum");
    printf("Piezo analog exceeded maximum");
    return NumPiezoIntensities;
  }

  // Analog is inside min max range, so subtraction and division is safe
  float BucketSize = 1. * (MaxPiezoAnalog - MinPiezoAnalog) / NumPiezoIntensities;
  float Intensity = 1. * (Analog - MinPiezoAnalog) / BucketSize;
  printf("\r\nAnalog: %d, Intensity: %.2f, BucketSize: %.2f\r\n", Analog, Intensity, BucketSize);
  return ceil(Intensity);
}

