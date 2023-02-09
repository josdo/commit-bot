#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateService.h"
#include "OptoSensorService.h"
#include "PIC32_AD_Lib.h"
#include "dbprintf.h"
#include "PIC32PortHAL.h"
#include "DCMotorService.h"



static uint8_t MyPriority;
static bool readOpto = false;

#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define HUND_SEC (ONE_SEC / 100)
#define THRESHOLD 750

uint32_t analog_signal[1];


bool InitOptoSensorService(uint8_t Priority)
{
    MyPriority = Priority;

    // Post successful initialization
    //  setting up the analog pins
    ANSELBbits.ANSB15 = 1;
    TRISBbits.TRISB15 = 1;
    ADC_ConfigAutoScan(BIT9HI, 1);

    ES_Event_t ThisEvent = {ES_INIT};
    if (ES_PostToService(MyPriority, ThisEvent) == true)
    {
      return true;
    }
    else
    {
      return false;
    }
}

bool PostOptoSensorService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunOptoSensorService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  
  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
//        ES_Timer_InitTimer(ANALOG_READ_TIMER, adjust_analog_signal());
        DB_printf("\rES_INIT received in Service %d\r\n", MyPriority);
    }
    break;
    
      case ES_READ_OPTO:{
          readOpto = true;
      }
      break;
  
    case ES_TAPE_DETECTED:
    {
        // TODO
        DB_printf("Analog signal: %d\r\n", analog_signal[0]);
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
        
        readOpto = false;
    }
    break;
      
  }
  
  return ReturnEvent;
}

bool readOptoSensor(){
    bool ReturnVal = false;
    
    if (1 == readOpto){
        ADC_MultiRead(analog_signal);
    
        if(analog_signal[0] > THRESHOLD) {
            ReturnVal = true;
            ES_Event_t ReturnEvent;
            ReturnEvent.EventType = ES_TAPE_DETECTED;
            PostOptoSensorService(ReturnEvent);  
        }
    }
    
    return ReturnVal;
}