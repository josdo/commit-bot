/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ControllerFSM.h"

// HALs
#include "PIC32_AD_Lib.h"
#include "PIC32_SPI_HAL.h"
#include "LED_Strip.h"

#include "LEDFSM.h"
/*----------------------------- Module Defines ----------------------------*/
#define ONE_SEC 1000 // 1 sec timer
#define HALF_SEC (ONE_SEC/2) // 1/2 sec timer
#define TWO_SEC (ONE_SEC * 2) // 2 sec timer
#define THIRTY_SEC (ONE_SEC * 30) // interaction timer

#define IR_PIN (1<<11) // AN11

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
static ControllerState_t CurrentState;
static uint8_t MyPriority;

static uint32_t MinPiezoOutput;
static uint32_t MaxPiezoOutput;
static uint32_t NumPiezoBuckets;

static uint32_t AnalogReadings[1]; 
static uint32_t PrevReadings[1];

/*------------------------------ Module Code ------------------------------*/
bool InitController(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  // Init module level variables
  MyPriority = Priority;
  CurrentState = InitPState_Controller;
  MinPiezoOutput  = 0;
  MaxPiezoOutput  = 250;
  NumPiezoBuckets = 10;
  
  clrScrn();
  printf("In Controller Initialization\r\n");
  
  // Set up analog read for IR sensor
  ADC_ConfigAutoScan( IR_PIN, 1);
  ADC_MultiRead(AnalogReadings);
  PrevReadings[0] = 0;

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
            CurrentState = WelcomingState;
        }
      } break;
    
      case WelcomingState:{
          switch(ThisEvent.EventType){
              case ES_IR_COVERED: {
                  CurrentState = IRCoveredState;
                  
                  // start the IR covered timer
                  ES_Timer_InitTimer(IR_COVERED_TIMER, TWO_SEC);
                  printf("The 2 second timer has started\r\n");
              }
              break;
          }
      }
      break;
    
      case IRCoveredState: {
            switch(ThisEvent.EventType){
              case ES_IR_UNCOVERED: {
                  CurrentState = WelcomingState;
                  printf("Timer was stopped!\r\n");
                  ES_Timer_StopTimer(IR_COVERED_TIMER);
              }
              break;
              
              case ES_TIMEOUT: {
                  CurrentState = PlayingState;
                  printf("Now playing the game!\r\n");
                  
                  // Let the LEDs know the game has started
                  ES_Event_t NewEvent;
                  NewEvent.EventType = ES_ENTER_GAME;
                  PostLEDFSM(NewEvent);
                  
                  printf("Being interaction timer\r\n");
                  ES_Timer_InitTimer(INTERACTION_TIMER, THIRTY_SEC);
              }
              break;
          }
      }
      break;
    
      case PlayingState: {
          // begin the 30 second interaction timer
          
          
          switch(ThisEvent.EventType){
              case ES_NEW_KEY: {
                  // get a point
                  if ('p' == ThisEvent.EventParam){
                      // reset the interaction timer
                      ES_Timer_StopTimer(INTERACTION_TIMER);
                      ES_Timer_InitTimer(INTERACTION_TIMER, THIRTY_SEC);
                      // post to the LED point
                  }
              }
              break;
              
              case ES_TIMEOUT: {
                  if (INTERACTION_TIMER == ThisEvent.EventParam){
                      printf("interaction timeout controller\r\n");
                      CurrentState = WelcomingState;
                  }
              }
              break;
          }
      }
      break;     
  }

  return ReturnEvent;
}

ControllerState_t QueryController(void)
{
  return CurrentState;
}



/***************************************************************************
 private functions
 ***************************************************************************/

bool DrumIsHit(void)
{
  // TODO fill in using A/D library
  return true;
}

bool checkIRSensor(void){
    bool returnVal = false;
    
    ADC_MultiRead(AnalogReadings); // read the analog pins
    uint32_t currVal = AnalogReadings[0];
    
    uint32_t difference = abs(AnalogReadings[0] - PrevReadings[0]);
    
    if (difference > 10){ // to account for noise in the signal
        PrevReadings[0] = currVal;
        
        // IR covered and in the welcoming state
        if ((currVal < 500) && (WelcomingState == CurrentState)){ 

            ES_Event_t ThisEvent;
            ThisEvent.EventType = ES_IR_COVERED;
            ThisEvent.EventParam = Green;
            PostLEDFSM(ThisEvent); // post to LED FSM
            PostController(ThisEvent); // post to this FSM
            returnVal = true;
        }
        
        else if ((currVal >= 500) && (IRCoveredState == CurrentState)){
            
            ES_Event_t ThisEvent;
            ThisEvent.EventType = ES_IR_UNCOVERED;
            ThisEvent.EventParam = Green;
            PostLEDFSM(ThisEvent); // post to LED FSM
            PostController(ThisEvent); // post to this FSM
            returnVal = true;
            
        }
    }
    
    return returnVal;
}