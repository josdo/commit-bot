#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DistanceSensorService.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>


static uint8_t MyPriority;
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define TWO_SEC (ONE_SEC * 2)
#define FIVE_SEC (ONE_SEC * 5)
#define HUND_SEC (ONE_SEC / 100)

static void InitTimer(void);
static void InitIC(void);
static void Period2Distance(void);

volatile static uint32_t distance_period;
static uint32_t distance;
typedef union{
    uint32_t actual_time;
    struct{
        uint16_t local_time;
        uint16_t rollover;
    }time_var;
}global_time;

volatile static global_time gl;

bool InitDistanceSensorService(uint8_t Priority)
{
    ES_Event_t ThisEvent;
    
    MyPriority = Priority;
  /********************************************
   in here you write your initialization code
   *******************************************/
  // post the initial transition event
    
    // B9 is the distance sensor
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_9);
    // Initialize the timer
    InitTimer();
    // Initialize the IC
    InitIC();
    // Starting time from 0
    gl.time_var.rollover = 0;
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

bool PostDistanceSensorService(ES_Event_t ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event_t RunDistanceSensorService(ES_Event_t ThisEvent)
{
    ES_Event_t ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    /********************************************
     in here you write your service code
     ***********************s********************/
    switch(ThisEvent.EventType){
        case ES_INIT:
        {
            DB_printf("\rES_INIT received in Distance Sensor Service %d\r\n", MyPriority);
        }
        break; 
    }
    return ReturnEvent;
}

void InitTimer(){
    // INPUT CAPTURE
    //switching the timer off
    T2CONbits.ON = 0;
    //selecting timer source
    T2CONbits.TCS = 0;
    // gated accumulation is off
    T2CONbits.TGATE = 0;
    // selecting a prescaler 2 for the timer
    T2CONbits.TCKPS = 0b001;
    // set the period on the timer    
    PR2 = 0xFFFF;
    // clear the timer flag
    IFS0CLR = _IFS0_T2IF_MASK;
    // enable the timer interrupts
    IEC0SET = _IEC0_T2IE_MASK;
    // setting timer priority
    IPC2bits.INT2IP = 6;
    // starting from 0
    TMR2 = 0;
    // turn on the timer 2
    T2CONbits.ON = 1;

}


void InitIC(){
    // disable interrupts
    __builtin_disable_interrupts();         
    // switch off the input capture module
    IC2CONbits.ON = 0;
    // continue in idle mode 
    IC2CONbits.SIDL = 0;
    // clearing the IC interrupt flag
    IFS0CLR = _IFS0_IC2IF_MASK;
    // enable the IC interrupts
    IEC0SET = _IEC0_IC2IE_MASK;

    // 16 bit capture
    IC2CONbits.C32 = 0;
    // First edge captured in rising
    // IC1CONbits.FEDGE = 1;
    // Select timer 2
    IC2CONbits.ICTMR = 1;
    // interrupt on every capture
    IC2CONbits.ICI = 0b00;
    // set mode on input capture to every rising edge
    IC2CONbits.ICM = 0b001;
    // set priority
    IPC2bits.IC2IP = 7;
    // multivector is enabled
    INTCONbits.MVEC = 1;
    // pin B9 as input capture
    IC2R = 0b0100;
    //switch on the IC module
    IC2CONbits.ON = 1;
    // global enable interrupts
    __builtin_enable_interrupts();
}



void Period2Distance(){
    distance = (uint32_t)(4 * ((0.1 * distance_period) - 1000));
}

uint32_t getDistance(){
    return distance;
}

static uint32_t lastTime;

// Function ISR to get the period out of the distance sensor and convert it into
// actual distance
void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL7SOFT) DistanceSensor(void){
    static uint16_t thisTime;
    do{
        thisTime = (uint16_t)IC2BUF;
        
        if(IFS0bits.T2IF == 1 && thisTime < 0x8000){
            ++(gl.time_var.rollover);
            IFS0CLR = _IFS0_T2IF_MASK;
        }
        gl.time_var.local_time = thisTime;
        distance_period = (gl.actual_time - lastTime);
        lastTime = gl.actual_time;
        
    }while(IC2CONbits.ICBNE != 0);
    Period2Distance();
    IFS0CLR = _IFS0_IC2IF_MASK;
}

void __ISR(_TIMER_2_VECTOR, IPL6SOFT) CountRollOver(void){
    __builtin_disable_interrupts();
    if(IFS0bits.T2IF == 1){
        ++(gl.time_var.rollover);
        IFS0CLR = _IFS0_T2IF_MASK;
    }
    __builtin_enable_interrupts();
}