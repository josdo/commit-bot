#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "PIC32PortHAL.h"
#include "DisplayEncoderService.h"
#include "Measure.h"


static uint8_t MyPriority;
// Wait between refreshing display with new encoder hi pulse
static uint16_t refreshWait = 1000;

static void StartNextDisplayTimer();

bool InitDisplayEncoderService(uint8_t Priority)
{
  MyPriority = Priority;
  // Configure pin B10 for 5V input capture
  InitMeasureEncoder();

  StartNextDisplayTimer();

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostDisplayEncoderService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunDisplayEncoderService(ES_Event_t ThisEvent)
{
  // Keep track of forward and reverse steps
  static uint16_t netStepsForward = 0;

  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_TIMEOUT:
    {
      if (NEXT_DISPLAY_TIMER == ThisEvent.EventParam)
      {
        // TODO: Display
        printf("Encoder hi pulse: %u\n\r", getEncoderHiPulse());

        StartNextDisplayTimer();
      }
    }
    break;
  }
  return ReturnEvent;
}

static void StartNextDisplayTimer()
{
  ES_Timer_InitTimer(NEXT_DISPLAY_TIMER, refreshWait);
  ES_Timer_StartTimer(NEXT_DISPLAY_TIMER);
}