#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "dbprintf.h"
#include "xc.h"
#include <sys/attribs.h>
#include "InitTimer2.h"

// ------------------------------- Module Defines ---------------------------
#define R2 LATBbits.LATB4                               // right direction pin
#define L2 LATAbits.LATA4                               // left direction pin

#define TIMER_DIV 4                                     // pre scalar on timer
#define PWM_FREQ 10000                                  // in Hz

#define PBCLK_RATE 20000000L

static const uint16_t PWM_PERIOD = 10000-1;

// TIMERx divisor for PWM, standard value is 8, to give maximum resolution
// ----------------------------------------------------------------------------


// ------------------------------- Module Variables ---------------------------

static volatile global_time Rcurr_time;         // IC1 current time (right)
static volatile global_time Rlast_time;            // IC1 prev time (right)

static volatile global_time Lcurr_time;         // IC3 current time (left)
static volatile global_time Llast_time;            // IC3 prev time (left)

static uint32_t Rperiod = 0;               // right wheel period  
static uint32_t Lperiod = 0;               // left wheel period

static const uint32_t ns_per_tick = 200;

static uint32_t Ldirection_desired = 0;
static uint32_t Rdirection_desired = 0;
static uint32_t Lspeed_desired = 0;
static uint32_t Rspeed_desired = 0;

extern volatile global_time gl;


// ---------------------------- Private Functions ----------------------------
void setPWM(void);                      // set up PWM on motor pins with 0 DC
void initEncoderISRs(void);                  // init encoder ISRs, IC1 on RA2, IC3 on RB5

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL7SOFT) ISR_RightEncoder(void);
void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_LeftEncoder(void);

void InitDCMotor()
{
  // ----------------------- Set up DC Motor pins ----------------------- 
  TRISACLR = _TRISA_TRISA4_MASK;                // set ra4 as output (L2)
  TRISBCLR = _TRISB_TRISB4_MASK;                // set rb4 as output (R2)
  
  R2 = 0;                                       // right direction
  L2 = 0;                                       // left direction

  
  // ------------------------------- PWM ----------------------------------
  setPWM();                                     // turn on PWM
  OC3RS = (uint16_t)(0);                        // initial speed is 0
  OC2RS = (uint16_t)(0);                        // initial speed is 0
  
  
  initEncoderISRs();                            // init encoder ISRs

  DB_printf("\rInitialized DC Motor, compiled at %s on %s\r\n", __TIME__, __DATE__);
}

void initPIController(void)
{
  // How frequently the controller updates
  static uint16_t ControllerUpdatePeriod = 40000;

  // Initialize timer 4
  // Turn off T4
  T4CONbits.w = 0;
  // Use PBCLK
  T4CONbits.TCS = 0;
  // Set prescale value to 1:1, which allows for 
  // (2^16-1 ticks) * 50ns/tick * 10^6ms/ns = 3.27ms of time measurement
  T4CONbits.TCKPS = 0;
  // Set PR4 to 2ms, which is 40,000 ticks
  PR4 = ControllerUpdatePeriod - 1;

  // Initialize interrupt vector
  __builtin_enable_interrupts(); // global enable
  INTCONbits.w = 0;
  INTCONbits.MVEC = 1; // use multi-vectored interrupts

  enablePIControl();
  IPC4bits.T4IP = 6; // Ensure lower priority than encoder interrupt's priority

  // Turn on T4 module
  T4CONbits.ON = 1;
}

void enablePIControl(void)
{
  IEC0SET = _IEC0_T4IE_MASK; // Enable timer 4 interrupts
  IFS0CLR = _IFS0_T4IF_MASK; // reset interrupt flag
}

void disablePIControl(void)
{
  IEC0CLR = _IEC0_T4IE_MASK; // Disable timer 4 interrupts
}

void setDesiredSpeed(Motors_t motor, Directions_t direction, uint32_t speed)
{
  if (motor == LEFT_MOTOR)
  {
    Lspeed_desired = speed;
    Ldirection_desired = direction;
  }
  else
  {
    Rspeed_desired = speed;
    Rdirection_desired = direction;
  }
}

// Updates velocity control, i.e. duty cycle applied
void __ISR(_TIMER_4_VECTOR, IPL6SOFT) PIControllerISR(void)
{
  static float kP = 1;
  static float kI = 1;
  static float Lcurr_sum_e = 0;
  static float Llast_sum_e = 0;
  static float Rcurr_sum_e = 0;
  static float Rlast_sum_e = 0;

  float Le = Lspeed_desired - getWheelSpeed(LEFT_MOTOR);
  Llast_sum_e = Lcurr_sum_e;
  Lcurr_sum_e += Le;

  float Re = Rspeed_desired - getWheelSpeed(RIGHT_MOTOR);
  Rlast_sum_e = Rcurr_sum_e;
  Rcurr_sum_e += Re;

  // Clamp cumulative error if it drives the commanded duty cycle out of valid range
  if (IFS0bits.T4IF)
  {
    // Left motor
    float Lcandidate_dc = kP * Le + kI * Lcurr_sum_e;
    uint32_t Lfinal_dc;
    if (Lcandidate_dc > 100 || Lcandidate_dc < 0)
    {
      Lcurr_sum_e = Llast_sum_e;
      Lfinal_dc = (Lcandidate_dc > 100) ? 100 : 0;
    }
    else
    {
      Lfinal_dc = round(Lcandidate_dc);
    }
    setMotorSpeed(LEFT_MOTOR, Ldirection_desired, Lfinal_dc);

    // Right motor
    float Rcandidate_dc = kP * Re + kI * Rcurr_sum_e;
    uint32_t Rfinal_dc;
    if (Rcandidate_dc > 100 || Rcandidate_dc < 0)
    {
      Rcurr_sum_e = Rlast_sum_e;
      Rfinal_dc = (Rcandidate_dc > 100) ? 100 : 0;
    }
    else
    {
      Rfinal_dc = round(Rcandidate_dc);
    }
    setMotorSpeed(RIGHT_MOTOR, Rdirection_desired, Rfinal_dc);

    IFS0CLR = _IFS0_T4IF_MASK;
  }
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

  // // Enable rollover counter ISR interrupts
  // IEC0SET = _IEC0_T3IE_MASK;
  // IPC3bits.T3IP = 6;
  // IFS0CLR = _IFS0_T3IF_MASK;
  // -------------------------------------------------------
  
  
  // --------------------- Channel 3, Right --------------------- 
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
  
  // --------------------- Channel 2, Left --------------------- 
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

float periodToMotorSpeed(uint32_t period)
{
  // period = 0 means no ticks, so no speed 
  if (period == 0)
  {
    return 0;
  }
  // ns per min = 60 * 1000 * 1000 * 1000
  // ns per tick = 200
  // gear = 50x slowdown
  // period = ticks per revolution
  // result = ns per min / (50 * period * ns per tick)
  // result = k / period, where
  // k = ns per min / (50 * ns per tick) = 60 * 1000 * 100
  const uint32_t k = 6000000;
  return 1.0 * k / period;
}

float getMotorSpeed(Motors_t whichMotor)
{
  // TODO use 12
  uint32_t periods_per_rev = 12;
  uint32_t period;
  if (whichMotor == LEFT_MOTOR)
  {
    // DB_printf("%x > %x\r\n", Llast_time.actual_time, Lcurr_time.actual_time);
    period = Lperiod;
    DB_printf("Lperiod (ticks) = %u\r\n", period * T2_tick_to_ns() / 1000 / 1000);
  }
  else
  {
    // DB_printf("%x > %x\r\n", Rlast_time.actual_time, Rcurr_time.actual_time);
    period = Rperiod;
    DB_printf("Rperiod (ticks) = %u\r\n", period * T2_tick_to_ns() / 1000 / 1000);
  }
  // DB_printf("period (ms) = %u\r\n", period * T2_tick_to_ns() / 1000 / 1000);
  return periodToMotorSpeed(period);
}

float getWheelSpeed(Motors_t whichMotor)
{
  // 3:1 gear ratio
  return getMotorSpeed(whichMotor) * 3;
}

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


void initEncoderISRs(void){
  __builtin_disable_interrupts();
  // Map pin A2 to IC 1, right
  IC1R = 0;
  // Setup IC 1 module
  IC1CONbits.w = 0;       // Turn off and set to defaults
  IC1CONbits.ICM = 0b011; // every rising edge
  IC1CONbits.ICTMR = 1;   // Use Timer2
  IC1CONbits.FEDGE = 1;   // Capture rising edge first
  // Enable interrupts
  IFS0CLR = _IFS0_IC1IF_MASK;
  // Reset interrupt flag
  IEC0SET = _IEC0_IC1IE_MASK;
  // Set interrupt priority
  IPC1bits.IC1IP = 7;

  // Map pin B5 to IC 3
  IC3R = 0b0001;
  // Setup IC 3 module
  IC3CONbits.w = 0;       // Turn off and set to defaults
  IC3CONbits.ICM = 0b011; // every rising edge
  IC3CONbits.ICTMR = 1;   // Use Timer2
  IC3CONbits.FEDGE = 1;   // Capture rising edge first
  // Enable interrupts
  IFS0CLR = _IFS0_IC3IF_MASK;
  // Reset interrupt flag
  IEC0SET = _IEC0_IC3IE_MASK;
  // Set interrupt priority
  IPC3bits.IC3IP = 7;

  // Use multi-vectored interrupts
  INTCONbits.w = 0;
  INTCONbits.MVEC = 1;

  // Turn on
  IC1CONbits.ON = 1;
  IC3CONbits.ON = 1;

  __builtin_enable_interrupts();
}

// Rolled over time at this point.
uint32_t getRolloverTicks(void)
{
  // 200ns per tick
  return gl.time_var.rollover * 0xFFFF;
}


void rotate90CW(void)
{
  return;
}

void rotate90CCW(void)
{
  return;
}

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL7SOFT) ISR_RightEncoder(void){
    static uint16_t thisTime = 0;           // current timer value
    do {
        thisTime = (uint16_t)IC1BUF;        // read the buffer
        updateGlobalTime(thisTime);
        Rcurr_time = gl;
        bool out_of_order = Rcurr_time.actual_time < Rlast_time.actual_time;
        bool too_small = Rcurr_time.actual_time - Rlast_time.actual_time < 2000;
        if (!out_of_order && !too_small)
          Rperiod = Rcurr_time.actual_time - Rlast_time.actual_time; 
        Rlast_time = Rcurr_time;
    } while(IC1CONbits.ICBNE != 0);
    IFS0CLR = _IFS0_IC1IF_MASK;
}

void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_LeftEncoder(void){
    static uint16_t thisTime = 0;           // current timer value
    do {
        thisTime = (uint16_t)IC3BUF;        // read the buffer
        updateGlobalTime(thisTime);
        Lcurr_time = gl;
        bool out_of_order = Lcurr_time.actual_time < Llast_time.actual_time;
        bool too_small = Lcurr_time.actual_time - Llast_time.actual_time < 2000;
        if (!out_of_order && !too_small)
          Lperiod = Lcurr_time.actual_time - Llast_time.actual_time; 
        Llast_time = Lcurr_time;
    } while(IC3CONbits.ICBNE != 0);
    IFS0CLR = _IFS0_IC3IF_MASK;
}