#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "PIC32PortHAL.h"
#include "DisplayEncoderService.h"
#include "Measure.h"


static uint8_t MyPriority;
// Wait between refreshing display with new encoder hi pulse
static uint16_t refreshWait = 500;

static void StartNextDisplayTimer();
static void LightLEDBars(uint32_t numToLight);
static void B15ToHi();
static void B15ToLo();

// Port B pins corresponding to the 1st to 8th LED bars, in order
static const uint32_t const LEDBarPinMasks[8] = {1 << 4, 1 << 5, 1 << 8, 
                                                 1 << 9, 1 << 11, 1 << 12,
                                                 1 << 13, 1 << 14};
static const uint32_t numBars = 8;

bool InitDisplayEncoderService(uint8_t Priority)
{
  MyPriority = Priority;
  // Configure pin B10 for 5V input capture
  InitMeasureEncoder();

  // Configure LED bar pins and B15 time profiling pin
  PortSetup_ConfigureDigitalOutputs(_Port_B, 
                                    _Pin_4|_Pin_5|_Pin_8|_Pin_9|_Pin_11|_Pin_12|_Pin_13|_Pin_14|_Pin_15);
  LightLEDBars(0);
  B15ToLo();

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
        LightLEDBars(GetEncoderPeriodBin());
        uint32_t currRPM = GetEncoderRPM();
        B15ToHi();
        printf("RPM %u\n\r", currRPM);
        B15ToLo();
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

static void LightLEDBars(uint32_t numToLight)
{
  for (uint32_t i = 0; i < numBars; i++)
  {
    if (i < numToLight)
      LATBSET = LEDBarPinMasks[i];
    else
      LATBCLR = LEDBarPinMasks[i];
  }
}

static void B15ToHi()
{
  LATBSET = BIT15HI;
}

static void B15ToLo()
{
  LATBCLR = BIT15HI;
}