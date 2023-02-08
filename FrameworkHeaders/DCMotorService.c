#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotorService.h"

// ------------------------------- Module Defines ---------------------------
#define EN12 LATBbits.LATB11                            // Enable pin 1,2
#define EN34 LATBbits.LATB12                            // Enable pin 3,4

#define A2 LATBbits.LATB4                               // non PWM control pin
#define A4 LATAbits.LATA4                               // non PWM control pin

#define TIMER_DIV 4                                     // pre scalar on timer
#define PWM_FREQ 1000                                   // in Hz
#define PWM_PERIOD 20*1000000/TIMER_DIV/PWM_FREQ-1      // convert to ticks

#define PBCLK_RATE 20000000L
// TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// ----------------------------------------------------------------------------

// ------------------------------- Module Variables ---------------------------
static uint8_t MyPriority;

static uint8_t DutyCycle = 0;
static Commands_t currentCommand;
// ----------------------------------------------------------------------------


// ---------------------------- Private Functions ----------------------------
void setPWM(void);                      // set up PWM on motor pins with 0 DC
void decodeCommand(uint16_t command);   // decod the command
// ----------------------------------------------------------------------------



bool InitDCMotorService(uint8_t Priority)
{
  MyPriority = Priority;
  
  // ----------------------- Set up DC Motor pins ----------------------- 
  TRISBCLR = _TRISB_TRISB11_MASK;               // set RB11 as output (EN12)
  
  ANSELBCLR = _ANSELB_ANSB12_MASK;              // set rb12 as digital (EN 34)
  TRISBCLR = _TRISB_TRISB12_MASK;               // set rb12 as output (EN 34)
  
  TRISACLR = _TRISA_TRISA4_MASK;                // set ra4 as output (4A)
  
  TRISBCLR = _TRISB_TRISB4_MASK;                // set rb4 as output (2A)
  
  EN12 = 1;                                     // enable the first motor
  EN34 = 1;                                     // enable the second motor
  A2 = 0;
  A4 = 0;
  // --------------------------------------------------------------------

  setPWM();                                     // turn on PWM
  
  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostDCMotorService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunDCMotorService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code
  switch(ThisEvent.EventType){
      case ES_TIMEOUT:{
          
      }
      break;
      
      case ES_NEW_COMMAND:{
          decodeCommand(ThisEvent.EventParam);      // decode the command
          
          switch(currentCommand){
              case STOP:{
                  OC3RS = 0;
                  OC4RS = 0;
              }
              break;
              
              case CW_90:{
                  
              }
              break;
              
              case CW_45:{
                  
              }
              break;
              
              case CCW_90:{
                  
              }
              break;
              
              case CCW_45:{
                  
              }
              break;
              
              case FORWARD_HALF:{
                  A2 = 0;
                  A4 = 0;
                  OC3RS = PWM_PERIOD/2;
                  OC4RS = PWM_PERIOD/2;
              }
              break;
              
              case FORWARD_FULL:{
                  OC3RS = PWM_PERIOD;
                  OC4RS = PWM_PERIOD;
              }
              break;
              
              case BACKWARD_HALF:{
                  A2 = 1;
                  A4 = 1;
                  OC3RS = PWM_PERIOD/2;
                  OC4RS = PWM_PERIOD/2;
              }
              break;
              
              case BACKWARD_FULL:{
                  A2 = 1;
                  A4 = 1;
                  OC3RS = 0;
                  OC4RS = 0;
              }
              break;
          }
      }
      break;
  }

  return ReturnEvent;
}

// ---------------------------- Private Functions -----------------------------
void setPWM(){
    // --------------------- Timer 3 --------------------- 
  //switching the timer 3 off
  T3CONbits.ON = 0;
  //selecting timer source 
  T3CONbits.TCS = 0;
  // selecting a prescaler for the timer - 4
  T3CONbits.TCKPS = 0b010;
  // clear the timer register
  TMR3 = 0;
  // -------------------------------------------------------
  
  // --------------------- Channel 3 --------------------- 
  // switching off the output compare module
  OC3CONbits.ON = 0;
  // selecting timer for the output compare mode
  OC3CONbits.OCTSEL = 1;
  // set PWM mode with no fault
  OC3CONbits.OCM = 0b110;
  // set the timer to 16 bits
  OC3CONbits.OC32 = 0;
  // set the inital cycle
  OC3R = (uint16_t)(PWM_PERIOD / 2);
  // set the repeating cycle
  OC3RS = (uint16_t)(PWM_PERIOD / 2);
  // -------------------------------------------------------
  
  // --------------------- Channel 4 --------------------- 
  // switching off the output compare module
  OC4CONbits.ON = 0;
  // selecting timer for the output compare mode
  OC4CONbits.OCTSEL = 1;
  // set PWM mode with no fault
  OC4CONbits.OCM = 0b110;
  // set the timer to 16 bits
  OC4CONbits.OC32 = 0;
  // set the initial cycle 
  OC4R = (uint16_t)(PWM_PERIOD / 2);
  // set the repeating cycle
  OC4RS = (uint16_t)(PWM_PERIOD / 2);
  // -------------------------------------------------------
  
  // mapping output compare channel to pins
  RPB10R = 0b0101;                          // pin 21
  RPB13R = 0b0101;                          // pin 24
  
  // switch on the output compare module
  OC3CONbits.ON = 1;
  // switch on the output compare module
  OC4CONbits.ON = 1;
  
  // setting period on the timer
  PR3 = PWM_PERIOD;
          
  // turn on the timer 3
  T3CONbits.ON = 1;
}
\
void decodeCommand(uint16_t command){
    if (0x00 == command){
        currentCommand = STOP;              
    }
          
    else if (0x02 == command){
        currentCommand = CW_90;    
    }
          
    else if (0x03 == command){
        currentCommand = CW_45;      
    }
    
    else if (0x04 == command){
        currentCommand = CCW_90;      
    }
    
    else if (0x05 == command){
        currentCommand = CCW_45;      
    }
    
    else if (0x08 == command){
        currentCommand = FORWARD_HALF;      
    }
    else if (0x09 == command){
        currentCommand = FORWARD_FULL;      
    }
    else if (0x10 == command){
        currentCommand = BACKWARD_HALF;      
    }
    else if (0x11 == command){
        currentCommand = BACKWARD_FULL;      
    }
    else if (0x20 == command){
        currentCommand = BEACON;      
    }
    else if (0x40 == command){
        currentCommand = TAPE;      
    }
    else{
        currentCommand = NA;
    }
}