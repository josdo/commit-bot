#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ServoService.h"

#define PRESCALE 4              
#define PBCLK 20000000

static uint8_t MyPriority;

void InitServoPWM(void);

bool InitServoService(uint8_t Priority)
{
    puts("Init Servo service\r\n");
  MyPriority = Priority;
  
  InitServoPWM();

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostServoService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunServoService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code
  
  switch(ThisEvent.EventType){
      case ES_INIT: {
        OC1RS = PBCLK/PRESCALE*1/1000;
      }
      break;
      
      case ES_GAME_START: {
          puts("Game start in servo");
          OC1RS = PBCLK/PRESCALE*2/1000;
      }
      break;
      
      case ES_GAME_END: {
          OC1RS = PBCLK/PRESCALE*1/1000;
      }
      break;
  }

  return ReturnEvent;
}

void InitServoPWM(void){
    // --------------------------- Timer 3 -------------------------------
    T3CONbits.ON = 0;                   // turn of T3
    T3CONbits.SIDL = 0;                 // on in idle mode
    T3CONbits.TCS = 0;                  // use PBCLK
    T3CONbits.TCKPS = 0b010;            // prescale of 4
    T3CONbits.TGATE = 0;                // turn off gated mode
    TMR3 = 0;                           // clear T3
    PR3 = PBCLK/PRESCALE*20/1000 - 1;    // 20 ms period
//    printf("PR3 = %u\r\n", PBCLK/PRESCALE*2/1000 - 1);
    // -------------------------------------------------------------------
    
    
    // ---------------------------- OC 1 ---------------------------------
    OC1CONbits.ON = 0;                  // turn off OC1
    TRISBbits.TRISB15 = 0;              // RB15 output
    ANSELBbits.ANSB15 = 0;              // RB15 digital
    OC1CONbits.OCTSEL = 1;              // timer 3 timebase
    OC1CONbits.OC32 = 0;                // 16 bit mode
    OC1CONbits.OCM = 0b110;               // PWM non-fault mode
    RPB15R = 0b0101;                    // map OC1 to RPB15
    OC1RS = PBCLK/PRESCALE*1/1000;
    OC1R = PBCLK/PRESCALE*1/1000;
    OC1CONbits.OCM = 0b110;               // PWM non-fault mode
    // -------------------------------------------------------------------
    
    T3CONbits.ON = 1;                     // turn on T3  
    OC1CONbits.ON = 1;                    // Turn on OC1
}