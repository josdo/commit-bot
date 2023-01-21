#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_AD_Lib.h"
#include "PIC32PortHAL.h"
#include "SpeedDialService.h"
#include "SharedData.h"

static uint8_t MyPriority;

static const uint32_t MAX_ANALOG_READING = 1023;
static const uint16_t MS_PER_READ = 100;
static uint32_t dialStepRate = 10;
static uint32_t maxStepRate = 0;

// Dial pin (RB2, pin 6) managed by AD read module
static const uint16_t DialAnalogNum = BIT4HI; // 1 << 4;

static void SetStepRateWithAnalog(uint32_t read);

/*  Allows client to set this service's max step rate, which is used
    as the 90% mark of the speed dial's speed range. */
void SetMaxStepRate(uint32_t r)
{
  maxStepRate = r;
}

uint32_t GetStepRateFromDial()
{
  return dialStepRate;
}

static void SetStepRateWithAnalog(uint32_t read)
{
  // maxStepRate is only 90% of the true max step rate
  uint32_t trueMaxStepRate = (10.0 / 9.0) * maxStepRate;
  float r = (1.0 * read) / MAX_ANALOG_READING * trueMaxStepRate;
  // printf("DialStepRate (f): %f\n\r", r);
  dialStepRate = r;
}

void StartDialReadTimer()
{
  ES_Timer_InitTimer(DIAL_READ_TIMER, MS_PER_READ);
  ES_Timer_StartTimer(DIAL_READ_TIMER);
}

bool InitSpeedDialService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;

  // Set up AD read library
  PortSetup_ConfigureAnalogInputs(_Port_B, _Pin_2);
  ADC_ConfigAutoScan(DialAnalogNum, 1);

  // Start read timer
  StartDialReadTimer();

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

bool PostSpeedDialService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunSpeedDialService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  if ((ES_TIMEOUT == ThisEvent.EventType) 
      && (DIAL_READ_TIMER == ThisEvent.EventParam))
  {
    uint32_t read[1];
    ADC_MultiRead(read);
    SetStepRateWithAnalog(read[0]);
    StartDialReadTimer();
  }

  return ReturnEvent;
}