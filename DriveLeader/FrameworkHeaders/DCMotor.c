#include <math.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DCMotor.h"
#include "dbprintf.h"
#include "xc.h"
#include <sys/attribs.h>
#include "InitTimer2.h"
#include "PIC32PortHAL.h"
#include "TopHSM.h"

extern volatile global_time gl;

#define R2 LATBbits.LATB4 // right direction pin
#define L2 LATAbits.LATA4 // left direction pin

/* PWM */
static const uint16_t PWM_PERIOD = 10000 - 1;

/* Encoder */
static volatile global_time Rcurr_time; // IC1 current time (right)
static volatile global_time Rlast_time; // IC1 prev time (right)

static volatile global_time Lcurr_time; // IC3 current time (left)
static volatile global_time Llast_time; // IC3 prev time (left)

static uint32_t Rperiod = 0; // right wheel period
static uint32_t Lperiod = 0; // left wheel period

static const uint32_t ns_per_tick = 200;

/* PI control */
static uint32_t Ldirection_desired = 0;
static uint32_t Rdirection_desired = 0;
static uint32_t Lspeed_desired = 0;
static uint32_t Rspeed_desired = 0;

/* Rotation and translation */
static uint32_t Lpulses_desired = 0;
static uint32_t Rpulses_desired = 0;
static uint32_t Lpulses_curr = 0;
static uint32_t Rpulses_curr = 0;
static bool counting_Lpulses = false;
static bool counting_Rpulses = false;
static bool reached_Lpulses = false;
static bool reached_Rpulses = false;
static ES_EventType_t reached_event = ES_NO_EVENT;

static void initEncoderISRs(void);
static void setPWM(void);
static void initPIController(void);

void InitDCMotor(bool enablePI)
{
  // DC motor pins
  TRISACLR = _TRISA_TRISA4_MASK; // set ra4 as output (L2)
  TRISBCLR = _TRISB_TRISB4_MASK; // set rb4 as output (R2)
  R2 = 0;                        // right direction
  L2 = 0;                        // left direction

  // PWM
  setPWM();              // turn on PWM
  OC3RS = (uint16_t)(0); // initial speed is 0
  OC2RS = (uint16_t)(0); // initial speed is 0

  // Encoders
  initEncoderISRs(); // init encoder ISRs

  // PI control
  initPIController();
  if (enablePI)
    enablePIControl();
  else
    disablePIControl();

  DB_printf("\rInitialized DC Motor, compiled at %s on %s\r\n", __TIME__, __DATE__);
}

static void initEncoderISRs(void)
{
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

static void setPWM(void)
{
  // -------------------- Set PWM pins as digital output ----------------
  TRISBbits.TRISB10 = 0; // RB10 is output R
  TRISBbits.TRISB11 = 0; // RB11 is output L

  // --------------------- Timer 3 ---------------------
  // switching the timer 3 off
  T3CONbits.ON = 0;
  // selecting timer source
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
  RPB10R = 0b0101; // RB10 (pin 21) to OC3 RIGHT
  RPB11R = 0b0101; // RB11 (pin 22) to OC2 LEFT

  // switch on the output compare module
  OC3CONbits.ON = 1;

  // switch on the output compare module
  OC2CONbits.ON = 1;

  // setting period on the timer
  PR3 = PWM_PERIOD;

  // turn on the timer 3
  T3CONbits.ON = 1;
}

static void initPIController(void)
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
  // TODO: stop motors or don't?
  setMotorSpeed(LEFT_MOTOR, Ldirection_desired, 0);
  setMotorSpeed(RIGHT_MOTOR, Rdirection_desired, 0);
}

void disablePIControl(void)
{
  IEC0CLR = _IEC0_T4IE_MASK; // Disable timer 4 interrupts
  // TODO: stop motors or don't?
  setMotorSpeed(LEFT_MOTOR, Ldirection_desired, 0);
  setMotorSpeed(RIGHT_MOTOR, Rdirection_desired, 0);
}

/* Chooses the speed setpoint for the given motor. If speed == 0, stops
   immediately by disabling PI control, which would gradually go to 0 rpm,
   and directly setting the motor duty cycle to 0. */
void setDesiredSpeed(Motors_t motor, Directions_t direction, uint32_t speed)
{
  // To stop immediately, disable PI control. Clear Lperiod and Rperiod since
  // the PIControllerISR will be off and won't be able to.
  if (speed == 0)
  {
    disablePIControl(); // also stops the motors
  }
  // Otherwise, enable PI control so the desired speed can be reached.
  else
  {
    enablePIControl(); // also stops the motors
  }

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

/* Returns revs per minute, which is
    external revs per internal rev (1/50) *
    internal revs per period (1/12) *
    periods per tick (1 / period) *
    ticks per ns (1 / 200) *
    ns per min (60 * 1000 * 1000 * 1000)
*/
float periodToMotorSpeed(uint32_t period)
{
  // 60*1000*1000*1000 / (50*12*200)
  // = 500*1000
  // TODO: debug where the correction comes from
  // static const uint32_t correction = 60;
  static const uint32_t correction = 5;
  static const float k = 500 * 1000 * correction;

  // period = 0 means no ticks, so no speed
  if (period == 0)
    return 0;

  float rpm = k / period;
  return rpm;
}

float getMotorSpeed(Motors_t whichMotor)
{
  uint32_t period;
  if (whichMotor == LEFT_MOTOR)
  {
    period = Lperiod;
  }
  else
  {
    period = Rperiod;
  }
  // DB_printf("period (us) = %u\r\n", period * T2_tick_to_ns() / 1000);
  // DB_printf("period (ticks) = %u\r\n", period);
  return periodToMotorSpeed(period);
}

void setMotorSpeed(Motors_t whichMotor, Directions_t whichDirection, uint16_t dutyCycle)
{
  if (LEFT_MOTOR == whichMotor)
  {
    L2 = whichDirection;

    if (FORWARD == whichDirection)
    {
      OC2RS = (uint16_t)(PWM_PERIOD * (dutyCycle / 100.0));
    }

    else if (BACKWARD == whichDirection)
    {
      OC2RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle / 100.0)));
    }
  }

  else if (RIGHT_MOTOR == whichMotor)
  {
    R2 = whichDirection;

    if (FORWARD == whichDirection)
    {
      OC3RS = (uint16_t)(PWM_PERIOD * (dutyCycle / 100.0));
    }

    else if (BACKWARD == whichDirection)
    {
      OC3RS = (uint16_t)(PWM_PERIOD * (1 - (dutyCycle / 100.0)));
    }
  }
}

// Rolled over time at this point.
uint32_t getRolloverTicks(void)
{
  // 200ns per tick
  return gl.time_var.rollover * 0xFFFF;
}

/* Drive until event checkers stop both motors. Sets the counting_L/Rpulses bools,
   which the event checkers are responsible for disabling. (With these bools enabled,
   any commanded duty cycle or speed will be ignored and the motors will stop after
   the desired number of pulses is reached.) */
void drive(Directions_t direction, uint32_t dist_cm)
{
  // TODO: tune pulses per cm
  static const uint32_t pulses_per_cm = 6;
  static const uint32_t speed = 100;

  uint32_t num_pulses = pulses_per_cm * dist_cm;

  __builtin_disable_interrupts();
  Lpulses_desired = num_pulses;
  Rpulses_desired = num_pulses;
  Lpulses_curr = 0;
  Rpulses_curr = 0;
  __builtin_enable_interrupts();

  if (CW == direction)
  {
    setDesiredSpeed(LEFT_MOTOR, FORWARD, speed);
    setDesiredSpeed(RIGHT_MOTOR, BACKWARD, speed);
    reached_event = ES_ROTATED;
  }
  else if (CCW == direction)
  {
    setDesiredSpeed(LEFT_MOTOR, BACKWARD, speed);
    setDesiredSpeed(RIGHT_MOTOR, FORWARD, speed);
    reached_event = ES_ROTATED;
  }
  else if (FORWARD == direction)
  {
    setDesiredSpeed(LEFT_MOTOR, FORWARD, speed);
    setDesiredSpeed(RIGHT_MOTOR, FORWARD, speed);
    reached_event = ES_TRANSLATED;
  }
  else if (BACKWARD == direction)
  {
    setDesiredSpeed(LEFT_MOTOR, BACKWARD, speed);
    setDesiredSpeed(RIGHT_MOTOR, BACKWARD, speed);
    reached_event = ES_TRANSLATED;
  }
  else
  {
    DB_printf("DCMotor drive(): Invalid direction\r\n");
  }
  counting_Lpulses = true;
  counting_Rpulses = true;
  reached_Lpulses = false;
  reached_Rpulses = false;
}

/* Rotate 90 degrees. */
void rotate90(Directions_t direction)
{
  // Assuming 76cm circumference, 90 degrees is 19cm.
  drive(direction, 19);
}

/* Return true if this classifies as a noisy interrupt. */
static bool isNoise(uint32_t curr32, uint32_t last32)
{
  static const uint32_t minimum_valid_period = 2000;

  bool out_of_order = curr32 < last32;
  bool too_small = curr32 - last32 < minimum_valid_period;
  return out_of_order || too_small;
}

/* Return true if this classifies as a stopped motor. */
static bool isStopped(uint32_t lastEncoderTime32)
{
  static const uint32_t maximum_valid_period = 390000;

  return gl.actual_time - lastEncoderTime32 >= maximum_valid_period;
}

/* Stop motor, clear current and desired pulse count, and return true
   if current count exceeds desired count.
   Strict inequality important so that curr and desired may both be
   reset to 0 without triggering this event checker to be true.

   Only works when desired pulses mode is enabled.
*/
bool reachedDesiredLPulses(void)
{
  if (!counting_Lpulses)
  {
    return false;
  }
  __builtin_disable_interrupts();
  uint32_t curr = Lpulses_curr;
  uint32_t desired = Lpulses_desired;
  __builtin_enable_interrupts();

  bool hasReached = curr > desired;
  if (hasReached)
  {
    setDesiredSpeed(LEFT_MOTOR, Ldirection_desired, 0);
    counting_Lpulses = false;
    reached_Lpulses = true;
    DB_printf("Desired %u Lpulses, stopped at %u Lpulses\r\n", desired, curr);

    __builtin_disable_interrupts();
    Lpulses_curr = 0;
    Lpulses_desired = 0;
    __builtin_enable_interrupts();

  }
  return hasReached;
}

bool reachedDesiredRPulses(void)
{
  if (!counting_Rpulses)
  {
    return false;
  }
  __builtin_disable_interrupts();
  uint32_t curr = Rpulses_curr;
  uint32_t desired = Rpulses_desired;
  __builtin_enable_interrupts();

  bool hasReached = curr > desired;
  if (hasReached)
  {
    setDesiredSpeed(RIGHT_MOTOR, Rdirection_desired, 0);
    counting_Rpulses = false;
    reached_Rpulses = true;
    DB_printf("Desired %u Rpulses, stopped at %u Rpulses\r\n", desired, curr);

    __builtin_disable_interrupts();
    Rpulses_curr = 0;
    Rpulses_desired = 0;
    __builtin_enable_interrupts();
  }
  return hasReached;
}

bool reachedBothDesiredPulses(void)
{
  if (reached_Lpulses && reached_Rpulses)
  {
    reached_Lpulses = false;
    reached_Rpulses = false;
    DB_printf("Reached both desired pulses\r\n");
    DB_printf("Reached event is %d\r\n", reached_event);
    ES_Event_t ThisEvent = {reached_event};
    PostTopHSM(ThisEvent);
    reached_event = ES_NO_EVENT;
    return true;
  }
  return false;
}

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL7SOFT) ISR_RightEncoder(void)
{
  static uint16_t thisTime = 0; // current timer value
  do
  {
    thisTime = (uint16_t)IC1BUF; // read the buffer
    updateGlobalTime(thisTime);
    Rcurr_time = gl;

    if (!isNoise(Rcurr_time.actual_time, Rlast_time.actual_time))
      Rperiod = Rcurr_time.actual_time - Rlast_time.actual_time;

    Rlast_time = Rcurr_time;
  } while (IC1CONbits.ICBNE != 0);

  if (counting_Rpulses)
  {
    __builtin_disable_interrupts();
    Rpulses_curr++;
    __builtin_enable_interrupts();
  }

  IFS0CLR = _IFS0_IC1IF_MASK;
}

void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL7SOFT) ISR_LeftEncoder(void)
{
  static uint16_t thisTime = 0; // current timer value
  do
  {
    thisTime = (uint16_t)IC3BUF; // read the buffer
    updateGlobalTime(thisTime);
    Lcurr_time = gl;

    if (!isNoise(Lcurr_time.actual_time, Llast_time.actual_time))
      Lperiod = Lcurr_time.actual_time - Llast_time.actual_time;

    Llast_time = Lcurr_time;
  } while (IC3CONbits.ICBNE != 0);

  if (counting_Lpulses)
  {
    __builtin_disable_interrupts();
    Lpulses_curr++;
    __builtin_enable_interrupts();
  }

  IFS0CLR = _IFS0_IC3IF_MASK;
}

// Updates velocity control, i.e. duty cycle applied
void __ISR(_TIMER_4_VECTOR, IPL6SOFT) PIControllerISR(void)
{
  static float kP = .1;
  static float kI = 0.005; // 100ms ramp to +20rpm, more variation
  // static float kI = 0.001; // 500ms ramp to +20rpm
  static float Lcurr_sum_e = 0;
  static float Llast_sum_e = 0;
  static float Rcurr_sum_e = 0;
  static float Rlast_sum_e = 0;

  float Le = Lspeed_desired - getMotorSpeed(LEFT_MOTOR);
  Llast_sum_e = Lcurr_sum_e;
  Lcurr_sum_e += Le;

  float Re = Rspeed_desired - getMotorSpeed(RIGHT_MOTOR);
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

void __ISR(_TIMER_2_VECTOR, IPL6SOFT) CountRollOver(void)
{
  updateGlobalTime(0);

  // Update the period to 0 if the motor is stopped
  if (isStopped(Rlast_time.actual_time))
    Rperiod = 0;

  if (isStopped(Llast_time.actual_time))
    Lperiod = 0;
}