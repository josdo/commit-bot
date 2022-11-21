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
#include "PIC32PortHAL.h"
// #include "pc32mx170f256b.h"

/*----------------------------- Module Defines ----------------------------*/
#define BUTTON_PORT PORTBbits.RB5

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
static uint32_t MinPiezoAnalogRange[3] = {25, 50, 100};
static uint32_t MinPiezoAnalog = 50;
static uint32_t MaxPiezoAnalog = 300;
static uint32_t NumPiezoIntensities = 9;

// Analog pins for drum piezos
// TODO: update NumANxPins as more added and modify how ADC_MultiRead result is used.
static uint32_t LeftDrumANx = 4;   // RB2
static uint32_t BottomDrumANx = 5; // RB3
static uint32_t RightDrumANx = 12; // RB12
static uint32_t NumANxPins = 3;

static uint16_t LastPiezoReadTime;
static bool LastButtonState;
static uint16_t ButtonDebounceCooldown = 100; // 20 ms for debounce
static uint32_t MinPiezoAnalogIdx = 0;

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
  LastButtonState = BUTTON_PORT;

  // Configure button pin
  PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_5);

  // Initialize analog read library
  uint16_t ANxPins = 1 << LeftDrumANx | 1 << BottomDrumANx | 1 << RightDrumANx;
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
  // Stop if no drums hit
  if (PiezosAnalog[0] < MinPiezoAnalog & PiezosAnalog[1] < MinPiezoAnalog & PiezosAnalog[2] < MinPiezoAnalog)
  {
    return false;
  }
  // TODO unmagic intensities by moving this into analog module
  uint32_t LeftIntensity = AnalogToIntensity(PiezosAnalog[0]);
  uint32_t BottomIntensity = AnalogToIntensity(PiezosAnalog[1]);
  uint32_t RightIntensity = AnalogToIntensity(PiezosAnalog[2]);
  printf("\r\nL %u, B %u, R %u\r\n", LeftIntensity, BottomIntensity, RightIntensity);
  if (1 <= LeftIntensity || 1 <= BottomIntensity || 1 <= RightIntensity)
  {
    Intensities_t DrumIntensities = {{LeftIntensity, BottomIntensity, RightIntensity}};
    ES_Event_t DrumsHit = {ES_DRUMS_HIT, DrumIntensities.All};
    PostController(DrumsHit);
    return true;
  }
  return false;
}

// TODO: create button service with state transition? or keep current cooldown
bool ButtonPressed(void)
{
  static uint16_t LastReadTime = 0;
  bool ReturnVal = false;

  bool CurrButtonState = BUTTON_PORT;
  uint16_t CurrReadTime = ES_Timer_GetTime();
  bool ReadyToRead = CurrReadTime - LastReadTime > ButtonDebounceCooldown;
  bool StateChanged = LastButtonState != CurrButtonState;
  bool ButtonUp = CurrButtonState == 1;

  if (ReadyToRead && StateChanged && ButtonUp)
  {
    // printf("\r\nButton state changed to %i\r\n", CurrButtonState);
    // Change minimum smack intensity
    MinPiezoAnalogIdx++;
    uint32_t RangeLength = sizeof(MinPiezoAnalogRange) / sizeof(MinPiezoAnalogRange[0]);
    if (MinPiezoAnalogIdx == RangeLength)
    {
      MinPiezoAnalogIdx = 0;
    }
    MinPiezoAnalog = MinPiezoAnalogRange[MinPiezoAnalogIdx];
    printf("\r\nMinimum analog threshold now %u\r\n", MinPiezoAnalog);
    ReturnVal = true;
  }

  LastButtonState = CurrButtonState;
  return ReturnVal;
}

/***************************************************************************
 private functions
 ***************************************************************************/
static uint32_t AnalogToIntensity(uint32_t Analog)
{
  if (0 > Analog || 1023 < Analog)
  {
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
    printf("Piezo analog exceeded max by %u", Analog - MaxPiezoAnalog);
    return NumPiezoIntensities;
  }

  // Analog is inside min max range, so subtraction and division is safe
  float BucketSize = 1. * (MaxPiezoAnalog - MinPiezoAnalog) / NumPiezoIntensities;
  float Intensity = 1. * (Analog - MinPiezoAnalog) / BucketSize;
  // printf("\r\nAnalog: %d, Intensity: %.2f, BucketSize: %.2f\r\n", Analog, Intensity, BucketSize);
  return ceil(Intensity);
}
