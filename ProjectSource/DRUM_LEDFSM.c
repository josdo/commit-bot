/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DRUM_LEDFSM.h"
#include "Utils.h"

#include "LED_Strip.h"
#include "PIC32_SPI_HAL.h"

/*----------------------------- Module Defines ----------------------------*/
#define ONE_SEC 1000
#define TWO_SEC 2000

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match htat of enum in header file
static LEDFSMState_t CurrentState;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

// keep track of LED intensity
static uint8_t LEDIntensity = 1;

// next color in welcoming state
static Colors_t NextWelcomingColor;

/*------------------------------ Module Code ------------------------------*/
bool InitDRUM_LEDFSM(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  printf("In drum led init\r\n");
  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitPState_Drums;
  
  // Set the drum LED strip
  InitMUXPins();
  SetMuxOutput(LeftDrum);
  Clear_Strip(LeftDrum_LEDs); // clear the LEDs
  Set_Intensity(LeftDrum_LEDs, LEDIntensity); // min intensity
  
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

bool PostDRUM_LEDFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunDRUM_LEDFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitPState_Drums:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
          CurrentState = WelcomingState_Drums;
          
          // always make the LEDs turquoise when entering WelcomingState
          SetMuxOutput(LeftDrum);
          Set_All_Color(LeftDrum_LEDs, NextWelcomingColor);
          Set_Intensity(LeftDrum_LEDs, LEDIntensity);
          NextWelcomingColor = Purple;
          
          ES_Event_t NewEvent;
          NewEvent.EventType = ES_UPDATING_LED;
          NewEvent.EventParam = 0;
          PostDRUM_LEDFSM(NewEvent);
      }
    } break;
    
      case WelcomingState_Drums: {
          
          switch(ThisEvent.EventType){
              case ES_TIMEOUT: {
                  SetMuxOutput(LeftDrum);
                  
                  // write the next color
                  Set_All_Color(LeftDrum_LEDs, NextWelcomingColor);
                  Set_Intensity(LeftDrum_LEDs, LEDIntensity);
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostDRUM_LEDFSM(NewEvent);
                  
                  if (LED_REFRESH_TIMER == ThisEvent.EventParam){
                      if (Purple == NextWelcomingColor){
                          NextWelcomingColor = Turquoise;
                      }
                      
                      else if (Turquoise == NextWelcomingColor){
                          NextWelcomingColor = Purple;
                      }
                  }
              }
              case ES_UPDATING_LED: {
                  SetMuxOutput(LeftDrum);
                  // still updating the LEDs
                  if (false == TakeDisplayUpdateStep(LeftDrum_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostDRUM_LEDFSM(NewEvent);
                  }
                  
                  // done updating the LEDs, now start timer for next color
                  else { 
//                      ES_Timer_InitTimer(LED_REFRESH_TIMER, TWO_SEC);
                  }
              }
              break;
              
              case ES_IR_COVERED: {
                  printf("IR covered in Drum FSM\r\n");
//                  ES_Timer_StopTimer(LED_REFRESH_TIMER); // stop the timer
                  CurrentState = IRCoveredState_Drums; // advance the state
                  
                  // set the new color
                  SetMuxOutput(LeftDrum);
                  Set_All_Color(LeftDrum_LEDs, ThisEvent.EventParam);
                  Set_Intensity(LeftDrum_LEDs, LEDIntensity);
                  
                  // start updating the LEDs
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostDRUM_LEDFSM(NewEvent);
              }
              break;
          }
      }
      break;
      
      case IRCoveredState_Drums: {
          switch(ThisEvent.EventType){
              case ES_UPDATING_LED: { 
                  SetMuxOutput(LeftDrum);
                  // update LED display
                  if (false == TakeDisplayUpdateStep(LeftDrum_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostDRUM_LEDFSM(NewEvent);
                  }
              }
              break;
              
              case ES_IR_UNCOVERED: {
                  // go back to welcoming state
                  CurrentState = WelcomingState_Drums; 
                  
                  // write the next welcoming color
                  SetMuxOutput(LeftDrum);
                  Set_All_Color(LeftDrum_LEDs, NextWelcomingColor);
                  Set_Intensity(LeftDrum_LEDs, LEDIntensity);
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostDRUM_LEDFSM(NewEvent);
              }
              break;
              
              case ES_ENTER_GAME: {
                  CurrentState = PlayingState_Drums;
              }
              break;
          }
          
      }
      break;
      
      case PlayingState_Drums: {
          switch(ThisEvent.EventType){
              case ES_TIMEOUT: {
                  if (INTERACTION_TIMER == ThisEvent.EventParam){
                    printf("interaction timeout LED\r\n");
                    // go back to welcoming state
                    CurrentState = WelcomingState_Drums; 
                  
                    // write the next welcoming color
                    Set_All_Color(LeftDrum_LEDs, NextWelcomingColor);
                    Set_Intensity(LeftDrum_LEDs, LEDIntensity);
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = 0;
                    PostDRUM_LEDFSM(NewEvent);
                  }
              }
              break;
          }
      }
      break;
  }

  return ReturnEvent;
}

LEDFSMState_t QueryDRUM_LEDFSM(void)
{
  return CurrentState;
}

/***************************************************************************
 private functions
 ***************************************************************************/

