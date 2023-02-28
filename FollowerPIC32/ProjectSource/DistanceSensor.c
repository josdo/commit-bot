#include "ES_Configure.h"
#include "ES_Framework.h"
#include "DistanceSensor.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "InitTimer2.h"

static void InitIC2(void);
static void Period2Distance(void);

volatile static uint32_t distance_period;
static uint32_t distance;
volatile extern global_time gl;


void InitDistanceSensor()
{  
    // B9 is the distance sensor
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_9);
    // Initialize the timer 2
    InitTimer2();
    // Initialize the IC
    InitIC2();
    
    DB_printf("\rES_INIT received in Distance Sensor Service %d\r\n");
}


void InitIC2(){
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
    IC2CONbits.FEDGE = 1;
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

volatile static uint32_t lastTime;
volatile static uint32_t temp;
volatile static bool isRising = 1;
// Function ISR to get the period out of the distance sensor and convert it into
// actual distance
void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL7SOFT) DistanceSensor(void){
    volatile static uint16_t thisTime;
    isRising = !isRising;
    do{
        thisTime = (uint16_t)IC2BUF;
        temp = lastTime;
        if((IFS0bits.T2IF == 1) && (thisTime < 0x8000)){
            ++(gl.time_var.rollover);
            IFS0CLR = _IFS0_T2IF_MASK;
        }
        gl.time_var.local_time = thisTime;
        if (isRising % 2){
            distance_period = (gl.actual_time - lastTime);
        }
        
        lastTime = gl.actual_time;
        
    }while(IC2CONbits.ICBNE != 0);
    if (isRising % 2){
        Period2Distance();
    }
    IFS0CLR = _IFS0_IC2IF_MASK;
}

