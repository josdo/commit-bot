/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PointServoService.h"

#include "PWM_PIC32.h"

/*----------------------------- Module Defines ----------------------------*/
#define TICS_PER_MS 2500

#define NUM_PWM 2
#define SERVO_PERIOD (20 * TICS_PER_MS)
#define SERVO_TIMER _Timer3_
#define SERVO_CHANNEL 1
#define SERVO_PIN PWM_RPB4

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

static uint8_t TotalPoints; // player's point count

/*------------------------------ Module Code ------------------------------*/
bool InitPointServoService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;

  TotalPoints = 0; // start with 0 points
  
  printf("In Servo Initialization\r\n");
  printf("\tTotal points = %d\r\n", TotalPoints);
  
  // set up PWM channel to RB4 - pin 11
  PWMSetup_BasicConfig(NUM_PWM);
  PWMSetup_SetPeriodOnTimer(SERVO_PERIOD, SERVO_TIMER);
  PWMSetup_AssignChannelToTimer(SERVO_CHANNEL, SERVO_TIMER);
  PWMOperate_SetPulseWidthOnChannel((uint16_t)(1 * TICS_PER_MS), SERVO_CHANNEL);
  
  // Set to 0 position
  PWMSetup_MapChannelToOutputPin(SERVO_CHANNEL, SERVO_PIN);

  // Post successful initialization
  ES_Event_t ThisEvent;
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

bool PostPointServoService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunPointServoService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code
  switch(ThisEvent.EventType){
      case ES_INIT: {
          TotalPoints = 0;
          uint16_t ServoPos = (uint16_t)(1.0/10.0*TotalPoints*TICS_PER_MS + TICS_PER_MS);
          PWMOperate_SetPulseWidthOnChannel(ServoPos, SERVO_CHANNEL);
      }
      break;
      
      case ES_CORRECT_HIT: {
          TotalPoints++;
              
          if (11 == TotalPoints){
              TotalPoints = 0;
          }
              
          printf("Total points = %d\r\n", TotalPoints);
 
          uint16_t ServoPos = (uint16_t)(1.0/10.0*TotalPoints*TICS_PER_MS + TICS_PER_MS);
          PWMOperate_SetPulseWidthOnChannel(ServoPos, SERVO_CHANNEL);

      }
      break;
      
      case ES_TIMEOUT: {
          if (INTERACTION_TIMER == ThisEvent.EventParam){
              TotalPoints = 0;
              uint16_t ServoPos = (uint16_t)(1.0/10.0*TotalPoints*TICS_PER_MS + TICS_PER_MS);
              PWMOperate_SetPulseWidthOnChannel(ServoPos, SERVO_CHANNEL);
          }
      }
      break;
      
      case ES_ENTER_ZEN: {
          PWMOperate_SetPulseWidthOnChannel((uint16_t)(2*TICS_PER_MS), SERVO_CHANNEL);
      }
      break;
  }

  return ReturnEvent;
}

/***************************************************************************
 private functions
 ***************************************************************************/

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/

