#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DistanceSensor.h"
#include "TapeSensor.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "TestHarnessService0.h"
#include "BeaconSensor.h"
#include "DCMotor.h"

/*----------------------------- Module Defines ----------------------------*/
// these times assume a 10.000mS/tick timing
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

bool InitTestHarnessService0(uint8_t Priority)
{
  clrScrn();
  ES_Event_t ThisEvent;

  MyPriority = Priority;

  // initialising everything
  InitDistanceSensor();
  InitTapeSensor();
  InitBeaconSensor();
  InitDCMotor();
  disablePIControl();

  DB_printf("Initialized TestHarnessService0, compiled at %s on %s\r\n", __TIME__, __DATE__);
  
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


bool PostTestHarnessService0(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunTestHarnessService0(ES_Event_t ThisEvent)
{
  static uint32_t dc = 0;
  static uint32_t desired_speed = 0;
  static bool print_motor_metrics = false;
  static bool pi_control_on = false;
  static uint16_t motor_timer_period = 500;
  static uint32_t last_rollover_time = 0;
  static uint16_t encoder_timer_period = 2;

  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
        DB_printf("\rES_INIT received in Test Service %d\r\n", MyPriority);
        ES_Timer_InitTimer(SERVICE0_TIMER, HALF_SEC);
    }
    break;
    
    case ES_TIMEOUT:
    {
        if(ThisEvent.EventParam == SERVICE0_TIMER){
//            DB_printf("Distance Period is: %d\r\n", getDistance());
//            DB_printf("Middle Is it on tape: %d\r\n", isOnTape(MiddleTapeSensor));
//            DB_printf("Right Is it on tape: %d\r\n", isOnTape(RightTapeSensor));
//            DB_printf("Short Range Freq: %d\r\n", getBeconSensorFreq(ShortRangeBeaconSensor));
            ES_Timer_InitTimer(SERVICE0_TIMER, HALF_SEC);
        }
        else if (ThisEvent.EventParam == PRINT_MOTOR_TIMER)
        {
          float rspeed = getMotorSpeed(RIGHT_MOTOR);
          // DB_printf("Rspeed is %u.%u\r\n", (uint32_t) rspeed, (rspeed - (uint32_t) rspeed)* 10000000000);
          // DB_printf("Rspeed is %u\r\n", (uint32_t) rspeed);
          ES_Timer_InitTimer(PRINT_MOTOR_TIMER, motor_timer_period);
        }
        else if (ThisEvent.EventParam == PRINT_ENCODER_TIMER)
        {
          uint32_t curr_rollover_time = getRolloverTime();
          // in us
          uint32_t delta = (last_rollover_time - curr_rollover_time) / 1000;
          DB_printf("Rollover time (us): %d\r\n", delta);
          last_rollover_time = curr_rollover_time;
          ES_Timer_InitTimer(PRINT_ENCODER_TIMER, encoder_timer_period);
        }
    }
    break;

    case ES_NEW_KEY:
    {
      DB_printf("Key -> %c <- pressed\r\n", ThisEvent.EventParam);

      /* Set duty cycle. */
      if ('k' == ThisEvent.EventParam)
      {
        dc = dc == 100 ? 100 : dc + 10;
        setMotorSpeed(RIGHT_MOTOR, FORWARD, dc);
        DB_printf("Increase PWM to %u\r\n", dc);
      }
      else if ('j' == ThisEvent.EventParam)
      {
        dc = dc == 0 ? 0 : dc - 10;
        setMotorSpeed(RIGHT_MOTOR, FORWARD, dc);
        DB_printf("Decrease PWM to %u\r\n", dc);
      }

      /* Set desired speed. */
      else if ('o' == ThisEvent.EventParam)
      {
        // Turn off PI control if currently on.
        if (pi_control_on)
        {
          pi_control_on = false;
          disablePIControl();
          DB_printf("Turned off PI control\r\n");
        }
        else
        {
          pi_control_on = true;
          enablePIControl();
          DB_printf("Turned on PI control\r\n");
        }
      }
      else if ('i' == ThisEvent.EventParam)
      {
        // desired_speed = desired_speed == 100 ? 100 : desired_speed + 10;
        desired_speed += 10;
        setDesiredSpeed(LEFT_MOTOR, FORWARD, desired_speed);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, desired_speed);
        DB_printf("Increase desired speed to %u\r\n", desired_speed);
      }
      else if ('u' == ThisEvent.EventParam)
      {
        desired_speed = desired_speed == 0 ? 0 : desired_speed - 10;
        setDesiredSpeed(LEFT_MOTOR, FORWARD, desired_speed);
        setDesiredSpeed(RIGHT_MOTOR, FORWARD, desired_speed);
        DB_printf("Decrease desired speed to %u\r\n", desired_speed);
      }

      /* Print motor metrics. */
      else if ('m' == ThisEvent.EventParam)
      {
        if (print_motor_metrics)
        {
          print_motor_metrics = false;
          // ES_Timer_StopTimer(PRINT_MOTOR_TIMER);
          ES_Timer_StopTimer(PRINT_ENCODER_TIMER);
          DB_printf("Stopped printing motor metrics\r\n");
        }
        else
        {
          print_motor_metrics = true;
          // ES_Timer_InitTimer(PRINT_MOTOR_TIMER, motor_timer_period);
          ES_Timer_InitTimer(PRINT_ENCODER_TIMER, encoder_timer_period);
          DB_printf("Start printing motor metrics\r\n");
        }
      }
    }
  }

  return ReturnEvent;
}
