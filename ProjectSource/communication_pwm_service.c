#include "ES_Configure.h"
#include "ES_Framework.h"
#include "communication_pwm_service.h"
#include "PWM_PIC32.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
#define TICS_PER_MS 2500
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define TENTH_SEC (ONE_SEC / 10)
#define HUND_SEC (ONE_SEC / 100)
#define ComPin PWM_RPB8
#define ComTimer _Timer2_
#define ComFreq 20000
#define ComChannel 2



/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitTemplateService

 Parameters
     uint8_t : the priorty of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, and does any
     other required initialization for this service
 Notes

 Author
     J. Edward Carryer, 01/16/12, 10:00
****************************************************************************/
bool Initcommunication_pwm_service(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  /********************************************
   in here you write your initialization code
   *******************************************/
  // post the initial transition event
  ThisEvent.EventType = ES_INIT;
  printf("\rStarting communication \r");
//  PWMSetup_BasicConfig(2);
  PWMSetup_SetFreqOnTimer(ComFreq, ComTimer);
  PWMSetup_AssignChannelToTimer(ComChannel, ComTimer);
  PWMSetup_MapChannelToOutputPin(ComChannel, ComPin);

  
  if (ES_PostToService(MyPriority, ThisEvent) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/****************************************************************************
 Function
     PostTemplateService

 Parameters
     EF_Event_t ThisEvent ,the event to post to the queue

 Returns
     bool false if the Enqueue operation failed, true otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
     J. Edward Carryer, 10/23/11, 19:25
****************************************************************************/
bool Postcommunication_pwm_service(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunTemplateService

 Parameters
   ES_Event_t : the event to process

 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes

 Author
   J. Edward Carryer, 01/15/12, 15:23
****************************************************************************/
ES_Event_t Runcommunication_pwm_service(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  /********************************************
   in here you write your service code
   *******************************************/
  switch(ThisEvent.EventType){
      case ES_INIT:
      {
        puts("In Communication Service");
        
        
      }
      break;
      case ES_TIMEOUT:
      {
        if(ThisEvent.EventParam == COMMUNICATION_PULSE_TIMER){
            PWMOperate_SetDutyOnChannel(0, ComChannel);
            puts("<<<<<<<<<<<<<<<<<");
        }
          
      }
      break;
      case ES_ENTER_GAME:
      {
        PWMOperate_SetDutyOnChannel(70, ComChannel); 
        puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
//           if ('e' == ThisEvent.EventParam)
//           {
// //            if(!PWMOperate_SetPulseWidthOnChannel((1*TICS_PER_MS),1))
//               if(!PWMOperate_SetDutyOnChannel(10, 1))
//                 while(1);
//               ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
              
//           }
//           if ('r' == ThisEvent.EventParam)
//           {
// //            if(!PWMOperate_SetPulseWidthOnChannel((1*TICS_PER_MS),1))
//               if(!PWMOperate_SetDutyOnChannel(20, 1))
//                 while(1);
//               ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
//           }
//           if ('t' == ThisEvent.EventParam)
//           {
// //            if(!PWMOperate_SetPulseWidthOnChannel((1*TICS_PER_MS),1))
//               if(!PWMOperate_SetDutyOnChannel(30, 1))
//                 while(1);
//               ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
//           }
//           if ('y' == ThisEvent.EventParam)
//           {
// //            if(!PWMOperate_SetPulseWidthOnChannel((1*TICS_PER_MS),1))
//               if(!PWMOperate_SetDutyOnChannel(40, 1))
//                 while(1);
//               ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
//           }
//           if ('u' == ThisEvent.EventParam)
//           {
// //            if(!PWMOperate_SetPulseWidthOnChannel((2*TICS_PER_MS),1))
//               if(!PWMOperate_SetDutyOnChannel(50,1))
//                 while(1);
//               ES_Timer_InitTimer(COMMUNICATION_PULSE_TIMER, HUND_SEC);
//           }
      }
      break;
      default:
        {}
      break;
  }
  return ReturnEvent;
}