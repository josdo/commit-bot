/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ClockFSM.h"
#include "Utils.h"

#include "LED_Strip.h"
#include "PIC32_SPI_HAL.h"

/*----------------------------- Module Defines ----------------------------*/
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC/2)
#define TWO_SEC (2 * ONE_SEC)
#define FIVE_SEC (5 * ONE_SEC)
#define SIX_SEC (6 * ONE_SEC)
#define TEN_SEC (10 * ONE_SEC)

#define MAX_FADE 10
#define FADE_TIME (ONE_SEC/10)

#define NUM_TIMER_LED 13

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

static void SetLEDs(uint8_t NumLEDs, Colors_t WhichColor);
//static void UpdateFadeIntensity(void);

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match htat of enum in header file
static ClockFSMState_t CurrentState;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

// keep track of LED intensities
static uint8_t LEDIntensity = 1;
static uint8_t FadeIntensity = 1;

// next color in welcoming state
static Colors_t NextWelcomingColor;

// index of clock while playing the game
static uint8_t Clock_idx = 1;

// time between each led lighting up on our clock
static uint16_t TimeToNextLED = (uint16_t)(49/NUM_TIMER_LED*ONE_SEC);
//static uint16_t TimeToNextLED = 2 * ONE_SEC;
/*------------------------------ Module Code ------------------------------*/
bool InitClockFSM(uint8_t Priority)
{
  ES_Event_t ThisEvent;
  
  printf("Init clock module\r\n");

  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitPState_ClockFSM;
  
  // set SPI up for LEDs
  SPISetup_BasicConfig(SPI_SPI1);
  SPISetup_SetLeader(SPI_SPI1, SPI_SMP_MID); // make pic332 leader  
  //  SPISetup_SetBitTime(SPI_SPI1, 10000); // 1000 kHz clock
  SPISetup_SetBitTime(SPI_SPI1, 10000/10);
  SPISetup_MapSSOutput(SPI_SPI1, SPI_RPA0); // set SS to pin 2
  SPISetup_MapSDOutput(SPI_SPI1, SPI_RPA1); // set SDO to pin 3
  SPISetup_SetXferWidth(SPI_SPI1, SPI_32BIT); // 16 bit datawidth
  SPISetup_SetClockIdleState(SPI_SPI1, SPI_CLK_HI); // active high
  SPISetup_SetActiveEdge(SPI_SPI1, SPI_SECOND_EDGE); // second edge
  SPISetEnhancedBuffer(SPI_SPI1, true); // enable enhanced buffer
  SPISetup_EnableSPI(SPI_SPI1); // turn on the SPI module
  IFS0CLR = _IFS0_INT4IF_MASK;
   
  // set up the MUX pins
  InitMUXPins();
  SetMuxOutput(Clock_LEDs);
  Clear_Strip(Clock_LEDs); // clear the LEDs
  Set_Intensity(Clock_LEDs, LEDIntensity); // min intensity
  
  // set the next color
  NextWelcomingColor = Turquoise;

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

bool PostClockFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunClockFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitPState_ClockFSM:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
          CurrentState = WelcomeState_ClockFSM;
          
          // always make the LEDs turquoise when entering WelcomingState
          SetMuxOutput(Clock_LEDs);
          Set_All_Color(Clock_LEDs, NextWelcomingColor);
          Set_Intensity(Clock_LEDs, LEDIntensity);
          NextWelcomingColor = Purple;
          
          ES_Event_t NewEvent;
          NewEvent.EventType = ES_UPDATING_LED;
          NewEvent.EventParam = 0;
          PostClockFSM(NewEvent);
      }
    } break;
    
      case WelcomeState_ClockFSM: {
          Clock_idx = 1;
          switch (ThisEvent.EventType){
            case ES_TIMEOUT: {
              // write the next color
                  SetMuxOutput(Clock_LEDs);
                  Set_All_Color(Clock_LEDs, NextWelcomingColor);
                  Set_Intensity(Clock_LEDs, LEDIntensity);
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
                  
                  if (LED_REFRESH_TIMER == ThisEvent.EventParam){
                      if (Purple == NextWelcomingColor){
                          NextWelcomingColor = Turquoise;
                      }
                      
                      else if (Turquoise == NextWelcomingColor){
                          NextWelcomingColor = Purple;
                      }
                  }
            }
            break;
          
            case ES_UPDATING_LED: {
                  // still updating the LEDs
                  SetMuxOutput(Clock_LEDs);
                  if (false == TakeDisplayUpdateStep(Clock_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostClockFSM(NewEvent);
                  }
                  
                  // done updating the LEDs, now start timer for next color
                  else { 
                      ES_Timer_InitTimer(LED_REFRESH_TIMER, TWO_SEC);
                  }
                }
                break;
              
              case ES_IR_COVERED: {
                  ES_Timer_StopTimer(LED_REFRESH_TIMER); // stop the refresh timer
                  ES_Timer_InitTimer(FADE_TIMER, FADE_TIME); // begin fade timer
                  CurrentState = IRCovered_ClockFSM; // advance the state
                  
                  // set the new color
                  SetMuxOutput(Clock_LEDs);
                  Set_All_Color(Clock_LEDs, ThisEvent.EventParam);
                  Set_Intensity(Clock_LEDs, UpdateFadeIntensity());
                  
                  // start updating the LEDs
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
              }
              break;
          }
      }
      break;
      
      case IRCovered_ClockFSM: {
          switch(ThisEvent.EventType){
              case ES_UPDATING_LED: { 
                  SetMuxOutput(Clock_LEDs);
                  // update LED display
                  if (false == TakeDisplayUpdateStep(Clock_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostClockFSM(NewEvent);
                  }
              }
              break;
              
              case ES_TIMEOUT: {
                  if (FADE_TIMER == ThisEvent.EventParam){
//                      UpdateFadeIntensity();
                      Set_Intensity(Clock_LEDs, UpdateFadeIntensity());
                      
                      ES_Event_t FadeEvent = {ES_UPDATING_LED, 0};
                      PostClockFSM(FadeEvent);
                      
                      ES_Timer_InitTimer(FADE_TIMER, FADE_TIME); // start fade again
                  }
              }
              break;
          
          
          case ES_IR_UNCOVERED: {
                  // go back to welcoming state
                  CurrentState = WelcomeState_ClockFSM; // back to welcome mode
                  
                  ES_Timer_StopTimer(FADE_TIMER); // stop the fade timer
                  ResetFadeIntensity(); // reset the fade intensity
                  
                  // write the next welcoming color
                  SetMuxOutput(Clock_LEDs);
                  Set_All_Color(Clock_LEDs, NextWelcomingColor);
                  Set_Intensity(Clock_LEDs, LEDIntensity);
                  
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
              }
              break;
              
              case ES_ENTER_GAME: {
                  CurrentState = PlayingGameState_ClockFSM;
                  Clear_Strip(Clock_LEDs); // turn off Timer LEDs for now
                  
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = ThisEvent.EventParam; 
                  PostClockFSM(NewEvent);
                  
                  printf("timer clock init\r\n");
                  ES_Timer_InitTimer(TIME_ELAPSED_TIMER, TimeToNextLED);
              }
              break;
          }
      }
      break;
      
      case PlayingGameState_ClockFSM: { 
          switch(ThisEvent.EventType){
              case ES_UPDATING_LED: { 
                  SetMuxOutput(Clock_LEDs);
                  // update LED display
                  if (false == TakeDisplayUpdateStep(Clock_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostClockFSM(NewEvent);
                  }
              }
              break;
              
              case ES_CORRECT_HIT: {
                  Clear_Strip(Clock_LEDs);
                  SetLEDs(Clock_idx, Gold);
                  Set_Intensity(Clock_LEDs, 1);
                  
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
              }
              break;
              
              case ES_ENTER_ZEN: {
                  printf("Zen in the timer module\r\n");
                  CurrentState = ZenState_ClockFSM;
                  LEDIntensity = 12;
                  
                  Clear_Strip(Clock_LEDs);
                  Set_All_Color(Clock_LEDs, White);
                  Set_Intensity(Clock_LEDs, LEDIntensity);
                    
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
              }
              break;
              
              case ES_TIMEOUT: {
                  if (INTERACTION_TIMER == ThisEvent.EventParam){
                    // go back to welcoming state
                    CurrentState = WelcomeState_ClockFSM; 
                  
                    // write the next welcoming color
                    Clear_Strip(Clock_LEDs);
                    Set_All_Color(Clock_LEDs, NextWelcomingColor);
                    Set_Intensity(Clock_LEDs, LEDIntensity);
                    
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = 0;
                    PostClockFSM(NewEvent);
                  }
                  
                  else if (MOTOR_TIMER == ThisEvent.EventParam){
                      Clear_Strip(Clock_LEDs);
                      SetLEDs(Clock_idx, Pink);
                      Set_Intensity(Clock_LEDs, 1);
                  
                      ES_Event_t NewEvent;
                      NewEvent.EventType = ES_UPDATING_LED;
                      NewEvent.EventParam = 0;
                      PostClockFSM(NewEvent);
                  }
                  
                  else if (TIME_ELAPSED_TIMER == ThisEvent.EventParam){
                    CurrentState = PlayingGameState_ClockFSM;
                    printf("6 sec clock timeout\r\n");
                    SetMuxOutput(Clock_LEDs);
                    
                    // Light the next LED for the timer
                    SetLEDs(Clock_idx, Pink);
                    Set_Intensity(Clock_LEDs, 1);
                    Clock_idx++;
                    
                    if (Clock_idx > NUM_TIMER_LED){
                        Clock_idx = NUM_TIMER_LED;
                    }
                    
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = 0;
                    PostClockFSM(NewEvent);
                    
                    // restart the timer
                    ES_Timer_InitTimer(TIME_ELAPSED_TIMER, TimeToNextLED);
                  }
              }
              break;
          }
      }
      break;
      
      case ZenState_ClockFSM: {
          switch(ThisEvent.EventType){
              
              case ES_UPDATING_LED: {
                  SetMuxOutput(Clock_LEDs);
                  // update LED display
                  if (false == TakeDisplayUpdateStep(Clock_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostClockFSM(NewEvent);
                  }
              }
              break;
              
              case ES_TIMEOUT: {
                if (ZEN_TIMER == ThisEvent.EventParam){
                  // go back to welcoming state
                  CurrentState = WelcomeState_ClockFSM; 
                  
                  // write the next welcoming color
                  Set_All_Color(Clock_LEDs, NextWelcomingColor);
                  Set_Intensity(Clock_LEDs, LEDIntensity);
                    
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
                }
                
                else if(LED_REFRESH_TIMER == ThisEvent.EventParam){
                  Set_All_Color(Clock_LEDs, NextWelcomingColor);
                  LEDIntensity -= 4;
                  Set_Intensity(Clock_LEDs, LEDIntensity);
                    
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostClockFSM(NewEvent);
                }
                  
              }
              break;
          }
      }
      break;
  }

  return ReturnEvent;
}

ClockFSMState_t QueryClockFSM(void)
{
  return CurrentState;
}

/***************************************************************************
 private functions
 ***************************************************************************/
static void SetLEDs(uint8_t NumLEDs, Colors_t WhichColor){
    if (NumLEDs >= 1 && NumLEDs <= NUM_TIMER_LED){
        for (uint8_t i=1; i<=NumLEDs; i++){
            Set_Single_Color(Clock_LEDs, WhichColor, i);
        }
    }
}

//static void UpdateFadeIntensity(void){
//    FadeIntensity++;
//    
//    if (MAX_FADE < FadeIntensity){
//        FadeIntensity = MAX_FADE;
//    }
//}