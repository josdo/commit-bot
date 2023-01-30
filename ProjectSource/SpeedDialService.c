#include "ES_Configure.h"
#include "ES_Framework.h"
#include "PIC32_AD_Lib.h"
#include "PIC32PortHAL.h"
#include "SpeedDialService.h"
#include "SharedData.h"

static uint8_t MyPriority;

static const uint32_t MAX_READING = 1023;
static const uint32_t MAX_PWM = 100;
static const uint16_t MS_PER_READ = 100;
static uint32_t dialReading;
static const uint16_t DialAnalogNum = BIT4HI; // RB2 is AN4

// Initialize pin B2 for reading from the potentiometer dial
bool InitSpeedDialService(uint8_t Priority)
{
  MyPriority = Priority;
  PortSetup_ConfigureAnalogInputs(_Port_B, _Pin_2);
  ADC_ConfigAutoScan(DialAnalogNum, 1);

  // Start read timer
  StartDialReadTimer();

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
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
    uint32_t read;
    ADC_MultiRead(&read);
    dialReading = read;
    // printf("Dial duty cycle: %u\n\r", DialDutyCycle());
    StartDialReadTimer();
  }

  return ReturnEvent;
}

uint32_t DialDutyCycle()
{
  return MAX_PWM * dialReading / MAX_READING;
}

void StartDialReadTimer()
{
  ES_Timer_InitTimer(DIAL_READ_TIMER, MS_PER_READ);
  ES_Timer_StartTimer(DIAL_READ_TIMER);
}
