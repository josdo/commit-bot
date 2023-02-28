#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeDetectorService.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>


static uint8_t MyPriority;
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define HUND_SEC (ONE_SEC / 100)
uint32_t analog_signal[1];

#define THRESHOLD 100
static uint16_t LastAnalogValue = 0;
static uint16_t CurrentAnalogValue = 0;
static uint16_t count = 0;



bool InitTapeDetectorService(uint8_t Priority)
{
    ES_Event_t ThisEvent;
    clrScrn();
    MyPriority = Priority;
    /********************************************
     in here you write your initialization code
     *******************************************/
    // post the initial transition event

    ANSELBbits.ANSB2 = 1;
    TRISBbits.TRISB2 = 1;
    ADC_ConfigAutoScan(BIT4HI, 1);
    
    
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


ES_Event_t RunTapeDetectorService(ES_Event_t ThisEvent)
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
        DB_printf("\rES_INIT received in ADService %d\r\n", MyPriority);
        ES_Timer_InitTimer(ANALOG_READ_TIMER, HALF_SEC);
        
    }
    break;
    case ES_TIMEOUT:
    {
        if(ThisEvent.EventParam == ANALOG_READ_TIMER){
            TapeStateAndNumber T1 = tapeSandN(1);
//            DB_printf("Tape Number reading is: %d\r\n", T1.TapeNumber);
            
            ES_Timer_InitTimer(ANALOG_READ_TIMER, HALF_SEC/2);
        }
    }
    break;
    
  }
  return ReturnEvent;
}




// Tape state and number function tells which Tape we are on and whether 
// we are on a tape or not.
// Takes input of direction i.e. forward (1) or backward (-1) and keeps track of 
// the tape.

TapeStateAndNumber tapeSandN(int direction){
    TapeStateAndNumber T1;
    
    ADC_MultiRead(analog_signal);
    CurrentAnalogValue = analog_signal[0];
    
    if (CurrentAnalogValue > THRESHOLD){
        T1.TapeState = 1;
    }
    else{
        T1.TapeState = 0;
    }

    
    if ((CurrentAnalogValue - LastAnalogValue) > THRESHOLD && CurrentAnalogValue > THRESHOLD){
        
        if (direction == 1){
            ++count;
        }
        else if (direction == -1){
            --count;
        }
    }
    
    if (abs(CurrentAnalogValue - LastAnalogValue) > THRESHOLD){
        LastAnalogValue = CurrentAnalogValue;
    }
    T1.TapeNumber = count;
//    DB_printf("Analog reading is: %d\r\n", analog_signal[0]);
    return T1;
}