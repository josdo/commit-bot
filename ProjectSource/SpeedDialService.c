#include "ES_Configure.h"
#include "ES_Framework.h"
#include "SpeedDialService.h"
#include "SharedData.h"

static uint8_t MyPriority;
static const uint32_t MAX_ANALOG_READING;
static const uint32_t MS_PER_READ = 20;
static uint32_t currStepRate = 10; // TODO set to 10
static uint32_t maxStepRate = 0;

void setMaxStepRate(uint32_t r)
{
    // check >= 0
    maxStepRate = r;
}

uint32_t getStepRateFromDial()
{
    return currStepRate;
}

bool InitSpeedDialService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;

  // Set up AD read library
  // Set max analog reading based on empirical testing with 2 phase on drive
  // Create and start pot read timer of MS_PER_READ

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

  // if ES_TIMEOUT
      // read analog pin
      // updaet currStepRate to reading / MAX_ANALOG_READING * MAX_STEP_RATE
      // restart timer

  return ReturnEvent;
}