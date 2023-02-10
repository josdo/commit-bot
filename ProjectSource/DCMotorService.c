#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotorService.h"
#include "dbprintf.h"
#include "OptoSensorService.h"
#include "ButtonService.h"
#include <sys/attribs.h>

// ------------------------------- Module Defines ---------------------------
#define EN12 LATBbits.LATB11                            // Enable pin 1,2
#define EN34 LATBbits.LATB12                            // Enable pin 3,4

#define A2 LATBbits.LATB4                               // non PWM control pin
#define A4 LATAbits.LATA4                               // non PWM control pin

#define TIMER_DIV 4                                     // pre scalar on timer
#define PWM_FREQ 1500                                   // in Hz
#define TURN_90 1200
#define TURN_45 500

#define PBCLK_RATE 20000000L
// TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// ----------------------------------------------------------------------------

// ------------------------------- Module Variables ---------------------------
static uint8_t MyPriority;

uint16_t PWM_PERIOD;                                    // convert to ticks
static uint8_t DutyCycle = 0;
static Commands_t currentCommand;

const uint16_t TICKS_PER_uS = 5;
const uint32_t LOWER_THRESH = 685 * TICKS_PER_uS;       // 1460 Hz
const uint32_t HIGH_THRESH = 694 * TICKS_PER_uS;        // 1440 Hz

volatile uint32_t beaconPeriod = 0;
volatile uint8_t beaconCount = 0;
volatile uint16_t RO = 0;

typedef union{
    struct{
        uint16_t CapturedTime;
        uint16_t RollOver;
    } ByTime;
    
    uint32_t FullLength;
} TimeTracker;

static volatile TimeTracker CurrentTime;
static volatile TimeTracker PrevTime;

// ----------------------------------------------------------------------------


// ---------------------------- Private Functions ----------------------------
void setPWM(void);                      // set up PWM on motor pins with 0 DC
void decodeCommand(uint16_t command);   // decode the command
void initInputCapture(void);            // input capture on RB5 (pin 14)
void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_InputCapture(void);
void __ISR(_TIMER_2_VECTOR, IPL6SOFT) ISR_RollOver(void);
// ----------------------------------------------------------------------------



bool InitDCMotorService(uint8_t Priority)
{
  MyPriority = Priority;
  
  InitButtonService();
  initInputCapture();
  
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
      case ES_INIT:
      {
        puts("Service 02:");
        DB_printf("\rES_INIT received in Service %d\r\n", MyPriority);
      }
      break;
      case ES_TIMEOUT:{
          if (TURN_TIMER == ThisEvent.EventParam){
              A2 = 0;
              A4 = 0;
              OC3RS = 0;
              OC4RS = 0;
          }
          
          if (PERIOD_TIMER == ThisEvent.EventParam){
            //   DB_printf("Period = %d\r\n", beaconPeriod);
              
              ES_Timer_InitTimer(PERIOD_TIMER, 100);
          }
      }
      break;
      
      case ES_NEW_KEY:{
          if ('0' == ThisEvent.EventParam){
              puts("STOP command\r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x00};
              PostDCMotorService(NewEvent);
          }
          
          else if ('1' == ThisEvent.EventParam){
              puts("CW 90 command\r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x02};
              PostDCMotorService(NewEvent);
          }
          
          else if ('2' == ThisEvent.EventParam){
              puts("CW 45 command\r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x03};
              PostDCMotorService(NewEvent);
          }
          
          else if ('3' == ThisEvent.EventParam){
              puts("CCW 90 command\r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x04};
              PostDCMotorService(NewEvent);
          }
          
          else if ('4' == ThisEvent.EventParam){
              puts("FORWARDS FULL command \r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x09};
              PostDCMotorService(NewEvent);
          }
          
          else if ('5' == ThisEvent.EventParam){
              puts("BACKWARDS FULL command \r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x11};
              PostDCMotorService(NewEvent);
          }
          
          else if ('8' == ThisEvent.EventParam){
              puts("FIND BEACON command \r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x20};
              PostDCMotorService(NewEvent);
          }
          
          else if ('9' == ThisEvent.EventParam){
              puts("TAPE command \r\n");
              ES_Event_t NewEvent = {ES_NEW_COMMAND, 0x40};
              PostDCMotorService(NewEvent);
          }
      }
      break;
      
      case ES_NEW_COMMAND:{          
          decodeCommand(ThisEvent.EventParam);      // decode the command
          DB_printf("Current command = %x\r\n", ThisEvent.EventParam);
          switch(currentCommand){
              case STOP:{
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 0);
              }
              break;
              
              case CW_90:{
                  setMotorSpeed(RIGHT_MOTOR, BACKWARD, 100);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
                  ES_Timer_InitTimer(TURN_TIMER, TURN_90);
              }
              break;
              
              case CW_45:{
                  setMotorSpeed(RIGHT_MOTOR, BACKWARD, 100);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
                  ES_Timer_InitTimer(TURN_TIMER, TURN_45);
              }
              break;
              
              case CCW_90:{
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
                  setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
                  ES_Timer_InitTimer(TURN_TIMER, TURN_90);
              }
              break;
              
              case CCW_45:{
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
                  setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
                  ES_Timer_InitTimer(TURN_TIMER, TURN_45);
              }
              break;
              
              case FORWARD_HALF:{
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 50);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 50);
              }
              break;
              
              case FORWARD_FULL:{
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 99);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 100);
              }
              break;
              
              case BACKWARD_HALF:{
                  setMotorSpeed(RIGHT_MOTOR, BACKWARD, 50);
                  setMotorSpeed(LEFT_MOTOR, BACKWARD, 50);
              }
              break;
              
              case BACKWARD_FULL:{
                  setMotorSpeed(RIGHT_MOTOR, BACKWARD, 99);
                  setMotorSpeed(LEFT_MOTOR, BACKWARD, 100);
              }
              break;
              
              case BEACON:{
                  // TODO
                  IEC0SET = _IEC0_IC3IE_MASK;             // enable ic3 interrupt
                  ES_Timer_InitTimer(PERIOD_TIMER, 100);
                  
                  // turn CCW until beacon is found
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 70);
                  setMotorSpeed(LEFT_MOTOR, BACKWARD, 70);
              }
              break;
              
              case TAPE:{
                  ES_Event_t OptoEvent = {ES_READ_OPTO, 0};     
                  PostOptoSensorService(OptoEvent); // enable opto event checker
                  
                  setMotorSpeed(RIGHT_MOTOR, FORWARD, 100);
                  setMotorSpeed(LEFT_MOTOR, FORWARD, 97);
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
  PWM_PERIOD = PBCLK_RATE/TIMER_DIV/PWM_FREQ-1;
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
  OC3R = 0;
  // set the repeating cycle
  OC3RS = 0;
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
  OC4R = 0;
  // set the repeating cycle
  OC4RS = 0;
  // -------------------------------------------------------
  
  // mapping output compare channel to pins
  RPB10R = 0b0101;                          // pin 21
  RPB13R = 0b0101;                          // pin 24
  
  // switch on the output compare module
  OC3CONbits.ON = 1;
  // switch on the output compare module
  OC4CONbits.ON = 1;
  T3CONbits.ON = 1;
  // setting period on the timer
  
  PR3 = PWM_PERIOD;
          
  // turn on the timer 3
  
}

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

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle){       
    if (0 == dutyCycle){
       EN12 = 0;
       EN34 = 0;
       A2 = 0;
       A4 = 0;
       OC3RS = 0;
       OC4RS = 0;
    }
    
    else if (LEFT_MOTOR == whichMotor){
        EN34 = 1;
        A4 = whichDirection;
        
        if (FORWARD == whichDirection){
            OC4RS = (uint16_t)(PWM_PERIOD * (dutyCycle/100.0));
        }
        
        else {
            OC4RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle/100.0)));
        }
    }
    
    else if (RIGHT_MOTOR == whichMotor){
        EN12 = 1;
        A2 = whichDirection;
        
        if (FORWARD == whichDirection){
            OC3RS = (uint16_t)(PWM_PERIOD * (dutyCycle/100.0));
        }
        
        else {
            OC3RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle/100.0)));
        }
    }
}

void initInputCapture(void){
    // ------------------------ Set Up Input Capture 3 -------------------------
    __builtin_disable_interrupts();         // turn off global interrupts
    IC3CONbits.ON = 0;                      // turn of IC3
    INTCONbits.MVEC = 1;                    // enable multivector mode
    IC3R = 0b0001;                          // map IC3 to RB5
    TRISBbits.TRISB5 = 1;                   // set RB5 as input
    // -----------------------------------------------------------------------
    
    
    // ------------------------ Set Up Timer 2 -------------------------
    T2CONbits.ON = 0;                       // turn off timer 2
    T2CONbits.TCS = 0;                      // source clock is PBCLK
    T2CONbits.TGATE = 0;                    // turn off gated mode
    T2CONbits.TCKPS = 0b010;                // prescale of 4
    T2CONbits.TSIDL = 0;                    // active in idle mode
    T2CONbits.T32 = 0;                      // 16 bit mode
    TMR2 = 0;                               // clear timer
    PR2 = 0xFFFF;                           // max period
    T2CONbits.ON = 1;                       // turn on timer 2
    // -----------------------------------------------------------------------
    
    
    // ------------------------ Set Up Input Capture 3 -------------------------
    IPC3bits.IC3IP = 7;                     // priority 7
    IC3CONbits.SIDL = 0;                    // active in idle mode
    IFS0CLR = _IFS0_IC3IF_MASK;             // clear pending interrupts
    IC3CONbits.ICTMR = 1;                   // timer 2 is time base
    IC3CONbits.ICM = 0b011;                 // every rising edge
    IC3CONbits.FEDGE = 1;
    IC3CONbits.C32 = 0;                     // 16 bit mode
    // -----------------------------------------------------------------------
    
    
    // ------------------------ Set Up Timer 2 Interrupt -----------------------
    IPC2bits.T2IP = 6;                      // timer interrupt priority is 6
    IFS0CLR = _IFS0_T2IF_MASK;              // clear pending interrupts
    // -----------------------------------------------------------------------
    
    
    // ------------------------ Enable Interrupts -----------------------
    IC3CONbits.ON = 1;                      // turn on IC3 interrupt
    IEC0SET = _IEC0_T2IE_MASK;              // enable timer 2 interrupt
    __builtin_enable_interrupts();          // enable global interrupts
    // ----------------------------------------------------------------------- 
}

void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_InputCapture(void){
    static uint16_t thisTime = 0;            // current timer value
    
    
    
    do {
        thisTime = (uint16_t)IC3BUF;        // read from buffer
        
        // if pending rollover flag AND captured time after rollover
        if ((1 == IFS0bits.T2IF) && (thisTime < 0x8000)){
            RO++;                           // increment rollover counter
            IFS0CLR = _IFS0_T2IF_MASK;      // clear timer 2 interrupt flag
        }
        CurrentTime.ByTime.RollOver = RO;   // update rollover field
        CurrentTime.ByTime.CapturedTime = thisTime; // store captured time

        beaconPeriod = CurrentTime.FullLength - PrevTime.FullLength;  // get period
        PrevTime.FullLength = CurrentTime.FullLength;   // update prev time
    } while(IC3CONbits.ICBNE != 0);         // loop while not empty
    
    IFS0CLR = _IFS0_IC3IF_MASK;             // clear IC3 interrupt flag
    
    // see if beacon period is in bounds
    if ((LOWER_THRESH < beaconPeriod) && (beaconPeriod < HIGH_THRESH)){
        beaconCount++;                      // increment valid beacon counter
    }
    else {
        beaconCount = 0;                    // reset to 0 if not a valid beacon
    }
    
    if (beaconCount >= 2){                  // if we have 2 valid beacon counts
        beaconCount = 0;                            // reset count
        
        setMotorSpeed(RIGHT_MOTOR, FORWARD, 0);     // stop moving
        setMotorSpeed(LEFT_MOTOR, FORWARD, 0);      // stop moving
        IEC0CLR = _IEC0_IC3IE_MASK;                 // disable ic3 interrupt
    }
    
}

void __ISR(_TIMER_2_VECTOR, IPL6SOFT) ISR_RollOver(void){
    __builtin_disable_interrupts();         // disable global interrupts
    
    if (1 == IFS0bits.T2IF){
        RO++;                               // increment rollover
        IFS0CLR = _IFS0_T2IF_MASK;          // clear timer 2 interrupt flag
    }
    CurrentTime.ByTime.RollOver = RO;       // store new rollover
    
    __builtin_enable_interrupts();          // enable global interrupts
}