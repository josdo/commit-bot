/****************************************************************************
 Module
   TemplateService.c

 Revision
   1.0.1

 Description
   This is a template file for implementing a simple service under the
   Gen2 Events and Services Framework.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 01/16/12 09:58 jec      began conversion from TemplateFSM.c
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ReceiverService.h"
#include "dbprintf.h"
#include "../ProjectHeaders/PIC32_AD_Lib.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
#define AD_CHANNEL (1 << 9)
#define NUM_AD_CHANNELS 1
static uint32_t LastAD_Value[1];
static bool play_note = true;
#define TICS_PER_MS 2500
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define TENTH_SEC (ONE_SEC / 10)
#define FIFTH_SEC (ONE_SEC / 5)
#define HUND_SEC (ONE_SEC / 100)
static uint32_t MaxAD_Value = 0;
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
bool InitReceiverService(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  /********************************************
   in here you write your initialization code
   *******************************************/
  // post the initial transition event
  ThisEvent.EventType = ES_INIT;
  ADC_ConfigAutoScan(AD_CHANNEL, NUM_AD_CHANNELS);
  ADC_MultiRead(LastAD_Value);
  ThisEvent.EventType = ES_INIT;
  //Setting tris
  TRISBbits.TRISB3 = 0;
  TRISBbits.TRISB4 = 0;
  TRISBbits.TRISB5 = 0;
  TRISBbits.TRISB6 = 0;
  TRISBbits.TRISB7 = 0;
  TRISBbits.TRISB8 = 0;
  //Setting ANSEL
  ANSELBbits.ANSB3 = 0;
  //Setting LAT
  LATBbits.LATB3 = 1;
  LATBbits.LATB4 = 1;
  LATBbits.LATB5 = 1;
  LATBbits.LATB6 = 1;
  LATBbits.LATB7 = 1;
  LATBbits.LATB8 = 1;
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
bool PostReceiverService(ES_Event_t ThisEvent)
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
ES_Event_t RunReceiverService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  /********************************************
   in here you write your service code
   *******************************************/
  
  switch (ThisEvent.EventType)
  {
        
        case ES_INIT:
        {
//            ES_Timer_InitTimer(SERVICE0_TIMER, HALF_SEC);
//            puts("Service 01:");
//            DB_printf("\rES_INIT received in Receiver Service %d\r\n", MyPriority);
            LATBbits.LATB8 = 0;
            LATBbits.LATB3 = 1;
        }
        break;
        case ES_TIMEOUT:
        {
//            ThisEvent.EventParam 
//            if(play_note)
            if(ThisEvent.EventParam == COM_TIMER)
            {
                puts("hello1");
                ES_Event_t ThisEvent;
                ThisEvent.EventType = ES_PLAY_NOTE;
                PostReceiverService(ThisEvent);
            }
            if(ThisEvent.EventParam == NOTE_TIMER){
                puts("hello2");
                LATBbits.LATB3 = 1;
                
//                LATBbits.LATB5 = 1;
//                LATBbits.LATB6 = 1;
//                LATBbits.LATB7 = 1; 
                LATBbits.LATB8 = 0; 
                
            }
            if(ThisEvent.EventParam == ZEN_TIMER){
                LATBbits.LATB4 = 1;
                LATBbits.LATB8 = 0;
            }
            else{
                
            }
            
            
            
        }  
        break;
        case EV_AD_UPDATE:
        {
            DB_printf("Analog val = %u\r\n", LastAD_Value[0]);
            if(MaxAD_Value < LastAD_Value[0])
            {
                MaxAD_Value = LastAD_Value[0];
            }
//            play_note = true;
            ES_Timer_InitTimer(COM_TIMER, HUND_SEC);
            
        }
        break;
      case ES_PLAY_NOTE:
      {
          DB_printf("MAX val = %u\r\n", MaxAD_Value);
          play_note = false;
          if(MaxAD_Value > 700 && MaxAD_Value < 900)
          { LATBbits.LATB8 = 1;
            LATBbits.LATB3 = 0;
            ES_Timer_InitTimer(NOTE_TIMER, ONE_SEC*49.004);
          }
          if(MaxAD_Value > 140 && MaxAD_Value < 250)
          { LATBbits.LATB8 = 0;
            
          }
          if(MaxAD_Value > 440 && MaxAD_Value < 550)
          { LATBbits.LATB8 = 1;
            LATBbits.LATB4 = 0;
            ES_Timer_InitTimer(ZEN_TIMER, ONE_SEC*28);
          }
          
          MaxAD_Value = 0;
      }
        
        break;
        
          
  }
  return ReturnEvent;
}

/***************************************************************************
 private functions
 ***************************************************************************/

bool CheckADEvent( void ){
    int32_t DifferenceInAD_Result;
    uint32_t CurrentAD_Value[1];
    ADC_MultiRead(CurrentAD_Value);
    DifferenceInAD_Result = LastAD_Value[0] - CurrentAD_Value[0];
    bool ReturnVal = false;
    
    if(abs(DifferenceInAD_Result) >= 30){
        ES_Event_t ThisEvent;
        ThisEvent.EventType = EV_AD_UPDATE;
        ThisEvent.EventParam = (uint16_t)CurrentAD_Value[0];
        PostReceiverService(ThisEvent);
        ReturnVal = true;
        LastAD_Value[0] = (uint16_t)CurrentAD_Value[0];
        
    }
//    if(CurrentAD_Value[0] > LastAD_Value[0]){
//        ReturnVal = true;
//        LastAD_Value[0] = (uint16_t)CurrentAD_Value[0];
//        read_analog = 1;
//    }
    return ReturnVal;
}
/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/

