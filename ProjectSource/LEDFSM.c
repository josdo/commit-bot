/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LEDFSM.h"

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
Colors_t NextWelcomingColor;

/*------------------------------ Module Code ------------------------------*/
bool InitLEDFSM(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitLEDPState;
  
  // set SPI up for LEDs
  SPISetup_BasicConfig(SPI_SPI1);
  SPISetup_SetLeader(SPI_SPI1, SPI_SMP_MID); // make pic332 leader  
//  SPISetup_SetBitTime(SPI_SPI1, 10000); // 1000 kHz clock
  SPISetup_SetBitTime(SPI_SPI1, 10000/5);
  SPISetup_MapSSOutput(SPI_SPI1, SPI_RPA0); // set SS to pin 2
  SPISetup_MapSDOutput(SPI_SPI1, SPI_RPA1); // set SDO to pin 3
  SPISetup_SetXferWidth(SPI_SPI1, SPI_32BIT); // 16 bit datawidth
  SPISetup_SetClockIdleState(SPI_SPI1, SPI_CLK_HI); // active high
  SPISetup_SetActiveEdge(SPI_SPI1, SPI_SECOND_EDGE); // second edge
  SPISetEnhancedBuffer(SPI_SPI1, true); // enable enhanced buffer
  SPISetup_EnableSPI(SPI_SPI1); // turn on the SPI module
  IFS0CLR = _IFS0_INT4IF_MASK;
  
  // Set the drum LED strip
  
  Clear_Strip(Timer_LEDs); // clear the LEDs
  Set_Intensity(Timer_LEDs, LEDIntensity); // min intensity
  
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

bool PostLEDFSM(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunLEDFSM(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    case InitLEDPState:
    {
      if (ThisEvent.EventType = ES_INIT)
      {
          CurrentState = WelcomingLEDState;
          
          // always make the LEDs turquoise when entering WelcomingState
          Set_All_Color(Timer_LEDs, NextWelcomingColor);
          Set_Intensity(Timer_LEDs, LEDIntensity);
          NextWelcomingColor = Purple;
          
          ES_Event_t NewEvent;
          NewEvent.EventType = ES_UPDATING_LED;
          NewEvent.EventParam = 0;
          PostLEDFSM(NewEvent);
      }
    } break;
    
      case WelcomingLEDState: {
          switch(ThisEvent.EventType){
              case ES_TIMEOUT: {
                  // write the next color
                  Set_All_Color(Timer_LEDs, NextWelcomingColor);
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostLEDFSM(NewEvent);
                  
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
                  // still updating the LEDs
                  if (false == TakeDisplayUpdateStep(Timer_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostLEDFSM(NewEvent);
                  }
                  
                  // done updating the LEDs, now start timer for next color
                  else { 
                      ES_Timer_InitTimer(LED_REFRESH_TIMER, TWO_SEC);
                  }
              }
              break;
              
              case ES_IR_COVERED: {
                  ES_Timer_StopTimer(LED_REFRESH_TIMER); // stop the timer
                  CurrentState = IRCoveredLEDState; // advance the state
                  
                  // set the new color
                  Set_All_Color(Timer_LEDs, ThisEvent.EventParam);
                  Set_Intensity(Timer_LEDs, LEDIntensity);
                  
                  // start updating the LEDs
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostLEDFSM(NewEvent);
              }
              break;
          }
      }
      break;
      
      case IRCoveredLEDState: {
          switch(ThisEvent.EventType){
              case ES_UPDATING_LED: { 
                  // update LED display
                  if (false == TakeDisplayUpdateStep(Timer_LEDs)){
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = ThisEvent.EventParam;
                    
                    PostLEDFSM(NewEvent);
                  }
              }
              break;
              
              case ES_IR_UNCOVERED: {
                  // go back to welcoming state
                  CurrentState = WelcomingLEDState; 
                  
                  // write the next welcoming color
                  Set_All_Color(Timer_LEDs, NextWelcomingColor);
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_UPDATING_LED;
                  NewEvent.EventParam = 0;
                  PostLEDFSM(NewEvent);
              }
              break;
              
              case ES_ENTER_GAME: {
                  CurrentState = PlayingLEDState;
              }
              break;
          }
          
      }
      break;
      
      case PlayingLEDState: {
          switch(ThisEvent.EventType){
              case ES_TIMEOUT: {
                  if (INTERACTION_TIMER == ThisEvent.EventParam){
                    printf("interaction timeout LED\r\n");
                    // go back to welcoming state
                    CurrentState = WelcomingLEDState; 
                  
                    // write the next welcoming color
                    Set_All_Color(Timer_LEDs, NextWelcomingColor);
                    ES_Event_t NewEvent;
                    NewEvent.EventType = ES_UPDATING_LED;
                    NewEvent.EventParam = 0;
                    PostLEDFSM(NewEvent);
                  }
              }
              break;
          }
      }
      break;
  }

  return ReturnEvent;
}

LEDFSMState_t QueryLEDFSM(void)
{
  return CurrentState;
}

/***************************************************************************
 private functions
 ***************************************************************************/

