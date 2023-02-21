#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeSensor.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "InitTimer2.h"
#include "BeaconSensor.h"

void InitIC5(void);
void InitIC4(void);

volatile static uint32_t short_range_period;
volatile static uint32_t long_range_period;
static uint32_t short_range_freq;
static uint32_t long_range_freq;

extern volatile global_time gl;

void Period2Freq(BeaconSensor_t);


void InitBeaconSensor(){
    // Short range
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_2);
    // Long Range
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_3);
    // Initialize the timer 2
    InitTimer2();
    InitIC5();
    InitIC4();
    
}

// IC for Short Range IR connected to B2
void InitIC5(){
    // disable interrupts
    __builtin_disable_interrupts();         
    // switch off the input capture module
    IC5CONbits.ON = 0;
    // continue in idle mode 
    IC5CONbits.SIDL = 0;
    // clearing the IC interrupt flag
    IFS0CLR = _IFS0_IC5IF_MASK;
    // enable the IC interrupts
    IEC0SET = _IEC0_IC5IE_MASK;

    // 16 bit capture
    IC5CONbits.C32 = 0;
    // First edge captured in rising
    // IC1CONbits.FEDGE = 1;
    // Select timer 2
    IC5CONbits.ICTMR = 1;
    // interrupt on every capture
    IC5CONbits.ICI = 0b00;
    // set mode on input capture to every rising edge
    IC5CONbits.ICM = 0b001;
    // set priority
    IPC5bits.IC5IP = 7;
    // multivector is enabled
    INTCONbits.MVEC = 1;
    // pin B2 as input capture
    IC5R = 0b0100;
    //switch on the IC module
    IC5CONbits.ON = 1;
    // global enable interrupts
    __builtin_enable_interrupts();
    
}

// IC for Long Range IR connected to B3
void InitIC4(){
    // disable interrupts
    __builtin_disable_interrupts();         
    // switch off the input capture module
    IC4CONbits.ON = 0;
    // continue in idle mode 
    IC4CONbits.SIDL = 0;
    // clearing the IC interrupt flag
    IFS0CLR = _IFS0_IC4IF_MASK;
    // enable the IC interrupts
    IEC0SET = _IEC0_IC4IE_MASK;

    // 16 bit capture
    IC4CONbits.C32 = 0;
    // First edge captured in rising
    // IC1CONbits.FEDGE = 1;
    // Select timer 2
    IC4CONbits.ICTMR = 1;
    // interrupt on every capture
    IC4CONbits.ICI = 0b00;
    // set mode on input capture to every rising edge
    IC4CONbits.ICM = 0b001;
    // set priority
    IPC4bits.IC4IP = 7;
    // multivector is enabled
    INTCONbits.MVEC = 1;
    // pin B3 as input capture
    IC4R = 0b0001;
    //switch on the IC module
    IC4CONbits.ON = 1;
    // global enable interrupts
    __builtin_enable_interrupts();
    
}

static uint32_t lastTimeShort;
static uint32_t lastTimeLong;

uint32_t getBeconSensorFreq(BeaconSensor_t whichSensor){
    if (whichSensor == ShortRangeBeaconSensor){
        return short_range_freq;
    }
    else if (whichSensor == LongRangeBeaconSensor){
        return long_range_freq;
    }
}

void Period2Freq(BeaconSensor_t whichSensor){
    if (whichSensor == ShortRangeBeaconSensor){
        short_range_freq = (uint32_t)(0.2 * short_range_period);
    }
    else if(whichSensor == LongRangeBeaconSensor){
        long_range_freq = (uint32_t)(0.2 * long_range_period);
    }
} 

// ISR for short range sensor
void __ISR(_INPUT_CAPTURE_5_VECTOR, IPL7SOFT) ShortRangeIRSensor(void){
    volatile static uint16_t thisTime;
    do{
        thisTime = (uint16_t)IC5BUF;
        
        if(IFS0bits.T2IF == 1 && thisTime < 0x8000){
            ++(gl.time_var.rollover);
            IFS0CLR = _IFS0_T2IF_MASK;
        }
        gl.time_var.local_time = thisTime;
        short_range_period = (gl.actual_time - lastTimeShort);
        lastTimeShort = gl.actual_time;
    }while(IC5CONbits.ICBNE != 0);
    Period2Freq(ShortRangeBeaconSensor);
    IFS0CLR = _IFS0_IC5IF_MASK;
}

// ISR for long range
void __ISR(_INPUT_CAPTURE_4_VECTOR, IPL7SOFT) LongRangeIRSensor(void){
    volatile static uint16_t thisTime;
    do{
        thisTime = (uint16_t)IC4BUF;
        
        if(IFS0bits.T2IF == 1 && thisTime < 0x8000){
            ++(gl.time_var.rollover);
            IFS0CLR = _IFS0_T2IF_MASK;
        }
        gl.time_var.local_time = thisTime;
        long_range_period = (gl.actual_time - lastTimeLong);
        lastTimeLong = gl.actual_time;
    }while(IC4CONbits.ICBNE != 0);
    Period2Freq(LongRangeBeaconSensor);
    IFS0CLR = _IFS0_IC4IF_MASK;
}
