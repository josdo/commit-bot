/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include <math.h>

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_AD_Lib.h"
#include "PIC32_SPI_HAL.h"
#include "PIC32PortHAL.h"

#include "Controller.h"
#include "LED_Strip.h"
#include "DRUM_LEDFSM.h"
#include "PointServoService.h"
#include "ClockFSM.h"
#include "Utils.h"

/*----------------------------- Module Defines ----------------------------*/
#define ONE_SEC 1000 // 1 sec timer
#define HALF_SEC (ONE_SEC/2) // 1/2 sec timer
#define TWO_SEC (ONE_SEC * 2) // 2 sec timer
#define THIRTY_SEC (ONE_SEC * 30) // 30 sec timer
#define ONE_MIN (ONE_SEC * 60) // 30 sec timer
#define INTERACTION_SEC (ONE_SEC * 15) // interaction timer

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
static uint32_t MinPiezoAnalogIdx = 0;
static uint32_t MinPiezoAnalog = 50;
static uint32_t MaxPiezoAnalog = 300;
static uint32_t NumPiezoIntensities = 9;

// IR readings
static uint32_t IRReadings[1]; 
static uint32_t IRPrevReadings[1];

// Analog pins for drum piezos
// TODO: update NumANxPins as more added and modify how ADC_MultiRead result is used.
static uint32_t LeftDrumANx = 4;   // RB2
static uint32_t BottomDrumANx = 5; // RB3
static uint32_t IRDetectorANx = 11; // RB13
static uint32_t RightDrumANx = 12; // RB12
static uint32_t NumANxPins = 4;
static uint32_t AnalogReadings[4];

static uint16_t LastPiezoReadTime;
static bool LastButtonState;
static uint16_t ButtonDebounceCooldown = 100; // in ms for debounce

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

  // Set up analog read for IR sensor
  ADC_MultiRead(IRReadings);
  IRPrevReadings[0] = 0;

  // Initialize analog read library
  uint16_t ANxPins = 1 << LeftDrumANx | 1 << BottomDrumANx 
                   | 1 << RightDrumANx | 1 << IRDetectorANx;
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

  switch (CurrentState) {
      case InitPState_Controller:
      {
        if (ThisEvent.EventType = ES_INIT)
        {
            CurrentState = WelcomingState_Controller;
        }
      } break;
    
      case WelcomingState_Controller:{
          switch(ThisEvent.EventType){
              case ES_IR_COVERED: {
                  CurrentState = IRCoveredState_Controller;
                  
                  // start the IR covered timer
                  ES_Timer_InitTimer(IR_COVERED_TIMER, TWO_SEC);
                  printf("The 2 second timer has started\r\n");
              }
              break;
          }
      }
      break;
    
      case IRCoveredState_Controller: {
            switch(ThisEvent.EventType){
              case ES_IR_UNCOVERED: {
                  CurrentState = WelcomingState_Controller;
                  printf("Timer was stopped!\r\n");
                  ES_Timer_StopTimer(IR_COVERED_TIMER);
              }
              break;
              
              case ES_TIMEOUT: {
                  CurrentState = PlayingState_Controller;
                  printf("Now playing the game!\r\n");
                  
                  // Let the LEDs know the game has started
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_ENTER_GAME;
                  PostDRUM_LEDFSM(NewEvent);
                  PostClockFSM(NewEvent);
                  
                  printf("Begin interaction timer: 15 SECONDS\r\n");
                  ES_Timer_InitTimer(INTERACTION_TIMER, INTERACTION_SEC);
                  
                  printf("Begin zen timer: ONE MINUTE \r\n");
                  ES_Timer_InitTimer(ZEN_TIMER, ONE_MIN);
              }
              break;
          }
      }
      break;
    
      case PlayingState_Controller: {
          switch(ThisEvent.EventType){
              case ES_NEW_KEY: {
                  // get a point
                  if ('p' == ThisEvent.EventParam){
                      // reset the interaction timer
                      ES_Timer_StopTimer(INTERACTION_TIMER);
                      ES_Timer_InitTimer(INTERACTION_TIMER, INTERACTION_SEC);
                      
                      ES_Event_t NewEvent;
                      NewEvent.EventType = ES_VALID_HIT;
                      NewEvent.EventParam = 0;                   
                      PostPointServoService(NewEvent);
                      // post to the LED point
                  }
              }
              break;
              
              case ES_TIMEOUT: {
                  if (INTERACTION_TIMER == ThisEvent.EventParam){
                      printf("Interaction timeout controller\r\n");
                      CurrentState = WelcomingState_Controller;
                      
                      // stop zen timer
                      ES_Timer_StopTimer(ZEN_TIMER);
                  }
              }
              break;
          }
      }
      break;   
      
      case ZenState_Controller: {
          
      }
      break;
  }

  return ReturnEvent;
}

ControllerState_t QueryController(void)
{
  return CurrentState;
}

// TODO: replace magic numbers, which are hard to update with new analog
void ReadAnalogPiezos(uint32_t *Buffer)
{
  ADC_MultiRead(AnalogReadings);
  Buffer[0] = AnalogReadings[0];
  Buffer[1] = AnalogReadings[1];
  Buffer[2] = AnalogReadings[3];
}

void ReadAnalogIR(uint32_t *Buffer)
{
  ADC_MultiRead(AnalogReadings);
  Buffer[0] = AnalogReadings[2];
}

bool DrumsAreHit(void)
{
  uint32_t PiezosAnalog[3];
  ReadAnalogPiezos(PiezosAnalog);
  // Stop if no drums hit
  if ((PiezosAnalog[0] < MinPiezoAnalog) && (PiezosAnalog[1] < MinPiezoAnalog) && (PiezosAnalog[2] < MinPiezoAnalog))
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

bool checkIRSensor(void){
    bool returnVal = false;
    
    // ADC_MultiRead(IRReadings); // read the analog pins
    ReadAnalogIR(IRReadings);
    uint32_t currVal = IRReadings[0];
    
    uint32_t difference = abs(IRReadings[0] - IRPrevReadings[0]);
    
    if (difference > 10){ // to account for noise in the signal
        IRPrevReadings[0] = currVal;
        
        // IR covered and in the welcoming state
        if ((currVal < 500) && (WelcomingState_Controller == CurrentState)){ 

            ES_Event_t ThisEvent;
            ThisEvent.EventType = ES_IR_COVERED;
            ThisEvent.EventParam = Green;
            
            PostDRUM_LEDFSM(ThisEvent); // post to drum FSM
            PostController(ThisEvent); // post to this FSM
            PostClockFSM(ThisEvent); // post to the clock FSM
            
            returnVal = true;
        }
        
        else if ((currVal >= 500) && (IRCoveredState_Controller == CurrentState)){
            
            ES_Event_t ThisEvent;
            ThisEvent.EventType = ES_IR_UNCOVERED;
            ThisEvent.EventParam = Green;
            
            PostDRUM_LEDFSM(ThisEvent); // post to LED FSM
            PostClockFSM(ThisEvent); 
            PostController(ThisEvent); // post to this FSM
            returnVal = true;
            
        }
    }
    
    return returnVal;
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
