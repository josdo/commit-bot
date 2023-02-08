#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TemplateService.h"
#include "OptoSensorService.h"
#include "PIC32_AD_Lib.h"
#include "dbprintf.h"
#include "PIC32PortHAL.h"



static uint8_t MyPriority;
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define HUND_SEC (ONE_SEC / 100)
uint32_t analog_signal[1];


bool InitOptoSensorService(uint8_t Priority)
{
  MyPriority = Priority;

  // Post successful initialization
  
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostOptoSensorService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunOptoSensorService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code

  return ReturnEvent;
}