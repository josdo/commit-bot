#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "dbprintf.h"
#include <sys/attribs.h>

// ------------------------------- Module Defines ---------------------------
#define R2 LATBbits.LATB4                               // right direction pin
#define L2 LATAbits.LATA4                               // left direction pin
#define REncoder PORTBbits.RA2                          // right encoder pin
#define LEncoder PORTBbits.RB5                          // left encoder pin

#define TIMER_DIV 4                                     // pre scalar on timer
#define PWM_FREQ 10000                                  // in Hz

#define PBCLK_RATE 20000000L

const uint16_t PWM_PERIOD = 2000-1;

// TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// ----------------------------------------------------------------------------


// ------------------------------- Module Variables ---------------------------
typedef union{
    struct{
        uint16_t CapturedTime;
        uint16_t RollOver;
    } ByTime;
    
    uint32_t FullLength;
} TimeTracker;

static volatile uint16_t T3RO = 0;                  // total rollover timer 3

static volatile TimeTracker IC1CurrentTime;         // IC1 current time (right)
static volatile TimeTracker IC1PrevTime;            // IC1 prev time (right)

static volatile TimeTracker IC3CurrentTime;         // IC3 current time (left)
static volatile TimeTracker IC3PrevTime;            // IC3 prev time (left)

static volatile uint32_t Rperiod = 0;               // right wheel period  
static volatile uint32_t Lperiod = 0;               // left wheel period

static volatile uint32_t Lspeed = 0;                // left wheel speed
static volatile uint32_t Rspeed = 0;                // right wheel speed

static volatile float velError;                  // velocity error
// ----------------------------------------------------------------------------


// ---------------------------- Private Functions ----------------------------
void setPWM(void);                      // set up PWM on motor pins with 0 DC

void initRightEncoderISR(void);         // IC1 on RA2
void initLeftEncoderISR(void);          // IC3 on RB5

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL7SOFT) ISR_RightEncoder(void);
void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_LeftEncoder(void);
void __ISR(_TIMER_3_VECTOR, IPL6SOFT) ISR_Timer3RollOver(void);

void InitDCMotor()
{
  // ----------------------- Set up DC Motor pins ----------------------- 
  TRISACLR = _TRISA_TRISA4_MASK;                // set ra4 as output (L2)
  TRISBCLR = _TRISB_TRISB4_MASK;                // set rb4 as output (R2)
  
  R2 = 0;                                       // right direction
  L2 = 0;                                       // left direction
  // --------------------------------------------------------------------

  
  // ------------------------------- PWM ----------------------------------
  setPWM();                                     // turn on PWM
  OC3RS = (uint16_t)(0);                        // initial speed is 0
  OC2RS = (uint16_t)(0);                        // initial speed is 0
  // ----------------------------------------------------------------------
  
  
  // ---------------------------- Init IC for encoders ---------------------
//  initRightEncoderISR();         // IC1 on RA2
//  initLeftEncoderISR();          // IC3 on RB5
  // ----------------------------------------------------------------------
  DB_printf("\rES_INIT received in DC Motor  %d\r\n");
}

// ---------------------------- Private Functions -----------------------------
void setPWM(void){
    // -------------------- Set PWM pins as digital output ----------------
    TRISBbits.TRISB10 = 0;                  // RB10 is output R
    TRISBbits.TRISB11 = 0;                  // RB11 is output L
    // --------------------------------------------------------------------
    
    
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
  OC3R = 0;
  // set the repeating cycle
  OC3RS = 0;
  // -------------------------------------------------------
  
  // --------------------- Channel 2 --------------------- 
  // switching off the output compare module
  OC2CONbits.ON = 0;
  // selecting timer for the output compare mode
  OC2CONbits.OCTSEL = 1;
  // set PWM mode with no fault
  OC2CONbits.OCM = 0b110;
  // set the timer to 16 bits
  OC2CONbits.OC32 = 0;
  // set the initial cycle 
  OC2R = 0;
  // set the repeating cycle
  OC2RS = 0;
  // -------------------------------------------------------
  
  // mapping output compare channel to pins
  RPB10R = 0b0101;                          // RB10 (pin 21) to OC3 RIGHT
  RPB11R = 0b0101;                          // RB11 (pin 22) to OC2 LEFT
  
  // switch on the output compare module
  OC3CONbits.ON = 1;
  
  // switch on the output compare module
  OC2CONbits.ON = 1;
  
  // setting period on the timer
  PR3 = PWM_PERIOD;
  
  // turn on the timer 3
  T3CONbits.ON = 1; 
}



/* R2/L2 is the direction pin, low if forward, high if backward. */
void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle){       
    if (0 == dutyCycle){
       R2 = 0;
       L2 = 0;
       OC3RS = 0;
       OC2RS = 0;
    }
    
    else if (LEFT_MOTOR == whichMotor){
        L2 = whichDirection;
        
        if (FORWARD == whichDirection){
            OC2RS = (uint16_t)(PWM_PERIOD * (dutyCycle/100.0));
        }
        
        else {
            OC2RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle/100.0)));
        }
    }
    
    else if (RIGHT_MOTOR == whichMotor){
        R2 = whichDirection;
        
        if (FORWARD == whichDirection){
            OC3RS = (uint16_t)(PWM_PERIOD * (dutyCycle/100.0));
        }
        
        else {
            OC3RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle/100.0)));
        }
    }
}


void initRightEncoderISR(void){
    // -------------------------- IC 1 -----------------------------------
    __builtin_disable_interrupts();         // disable global interrupts
    IC1CONbits.ON = 0;                      // turn of IC1
    INTCONbits.MVEC = 1;                    // enable multivector mode
    IC1R = 0b0000;                          // map IC1 to RA2
    TRISAbits.TRISA4 = 1;                   // set RA2 as input
    IPC1bits.IC1IP = 7;                     // priority 7
    IC1CONbits.SIDL = 0;                    // active in idle mode
    IFS0CLR = _IFS0_IC1IF_MASK;             // clear pending interrupts
    IC1CONbits.ICTMR = 0;                   // timer 3 is time base
    IC1CONbits.ICM = 0b011;                 // every rising edge
    IC1CONbits.FEDGE = 1;                   // first edge is rising
    IC1CONbits.C32 = 0;                     // 16 bit mode
    IC1CONbits.ON = 1;                      // turn on IC1 interrupt
    IEC0SET = _IEC0_IC1IE_MASK;             // enable IC1 interrupt
    __builtin_enable_interrupts();          // enable global interrupts
    // -------------------------------------------------------------------
}

void initLeftEncoderISR(void){
    // -------------------------- IC 3 -----------------------------------
    __builtin_disable_interrupts();         // disable global interrupts
    IC3CONbits.ON = 0;                      // turn of IC3
    INTCONbits.MVEC = 1;                    // enable multivector mode
    IC3R = 0b0001;                          // map IC3 to RB5
    TRISBbits.TRISB5 = 1;                   // set RA2 as input
    IPC3bits.IC3IP = 7;                     // priority 7
    IC3CONbits.SIDL = 0;                    // active in idle mode
    IFS0CLR = _IFS0_IC3IF_MASK;             // clear pending interrupts
    IC3CONbits.ICTMR = 0;                   // timer 3 is time base
    IC3CONbits.ICM = 0b011;                 // every rising edge
    IC3CONbits.FEDGE = 1;                   // first edge is rising
    IC3CONbits.C32 = 0;                     // 16 bit mode
    IC3CONbits.ON = 1;                      // turn on IC3 interrupt
    IEC0SET = _IEC0_IC3IE_MASK;             // enable IC3 interrupt
    __builtin_enable_interrupts();          // enable global interrupts
    // -------------------------------------------------------------------
}

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL7SOFT) ISR_RightEncoder(void){
    static uint16_t thisTime = 0;           // current timer value
    
    do {
        thisTime = (uint16_t)IC1BUF;        // read the buffer
        
        if ((1 == IFS0bits.T1IF) && (thisTime < 0x8000)){
            T3RO++;                         // increment rollover counter
            IFS0CLR = _IFS0_T1IF_MASK;      // clear rollover mask
        }
        IC1CurrentTime.ByTime.RollOver = T3RO;          // update rollover
        IC1CurrentTime.ByTime.CapturedTime = thisTime;  // store captured time
        
        // find period of right encoder pulse
        Rperiod = IC1CurrentTime.FullLength - IC1PrevTime.FullLength;      
        
        // update prev time with current value
        IC1PrevTime.FullLength = IC1CurrentTime.FullLength;
        
    } while(IC1CONbits.ICBNE != 0);
}

void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_LeftEncoder(void){
    static uint16_t thisTime = 0;           // current timer value
    
    do {
        thisTime = (uint16_t)IC3BUF;        // read the buffer
        
        if ((1 == IFS0bits.T3IF) && (thisTime < 0x8000)){
            T3RO++;                         // increment rollover counter
            IFS0CLR = _IFS0_T3IF_MASK;      // clear rollover mask
        }
        IC3CurrentTime.ByTime.RollOver = T3RO;          // update rollover
        IC3CurrentTime.ByTime.CapturedTime = thisTime;  // store captured time
        
        // find period of left encoder pulse
        Lperiod = IC3CurrentTime.FullLength - IC3PrevTime.FullLength;      
        
        // update prev time with current value
        IC3PrevTime.FullLength = IC3CurrentTime.FullLength;
        
    } while(IC3CONbits.ICBNE != 0);
}

void __ISR(_TIMER_3_VECTOR, IPL6SOFT) ISR_Timer3RollOver(void){
    __builtin_disable_interrupts();         // disable global interrupts
    
    if (1 == IFS0bits.T3IF){
        T3RO++;                             // increment rollover
        IFS0CLR = _IFS0_T3IF_MASK;          // clear timer 2 interrupt flag
    }
    IC1CurrentTime.ByTime.RollOver = T3RO;          // update rollover
    IC3CurrentTime.ByTime.RollOver = T3RO;          // update rollover
    
    __builtin_enable_interrupts();          // enable global interrupts
}

