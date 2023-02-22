#include "ES_Configure.h"
#include "ES_Framework.h"
//#include "TapeSensor.h"
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
volatile static uint32_t short_range_freq;
volatile static uint32_t long_range_freq;

extern volatile global_time gl;

// --------------------------------- VISHALS CODE --------------------------------
const uint8_t NUM_VALID_BEACON_PULSE = 2;     // num of valid beacon pulses
static uint8_t numBeaconB = 0;                // num valid beacon B pulses
static uint8_t numBeaconC = 0;                // num valid beacon C pulses

const uint16_t BEACON_B_TICKS = 5000;           // ticks for beacon b
const uint16_t BEACON_C_TICKS = 6793;           // ticks for beacon c
// -----------------------------------------------------------------------------

void Period2Freq(BeaconSensor_t);


void InitBeaconSensor(void){
    // Short range
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_2);
    // Long Range
    PortSetup_ConfigureDigitalInputs(_Port_B, _Pin_3);
    // Initialize the timer 2
    InitTimer2();
    InitIC5();
    InitIC4();
    DB_printf("\rES_INIT received in Beacon Sensor Service %d\r\n");
}

//void InitShortBeaconTimeout(void){
//    // -------------------------- Timer 1 -------------------------------
//    T1CONbits.ON = 0;                   // turn off timer 1
//    T1CONbits.TCS = 0;                  // PBCLK source
//    T1CONbits.SIDL = 0;                 // active in idle mode
//    T1CONbits.TGATE = 0;                // turn off gated mode
//    T1CONbits.TSYNC = 0;                // turn of sync mode
//    T1CONbits.TCKPS = 0b010;            // pre-scale of 4
//    TMR1 = 0;                           // clear the timer
//    PR1 = 5000;                         // 1 ms timeout
//    // --------------------------------------------------------------------
//    
//    
//    // ----------------------- Set Up Interrupt ------------------------------
//    __builtin_disable_interrupts();      // disable global interrupts
//    IPC1bits.T1IP = 4;                  // timer 1 priority is 4
//    IFS0CLR = _IFS0_T1IF_MASK;          // clear pending flag
//    // -----------------------------------------------------------------------
//    
//}

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

    // VISHAL CODE
    // enable the IC interrupts
    // IEC0SET = _IEC0_IC5IE_MASK;

    // 16 bit capture
    IC5CONbits.C32 = 0;
    // First edge captured in rising
    // IC1CONbits.FEDGE = 1;
    // Select timer 2
    IC5CONbits.ICTMR = 1;
    // interrupt on every capture
    IC5CONbits.ICI = 0b00;
    // set mode on input capture to every rising edge
//    IC5CONbits.ICM = 0b001;
    IC5CONbits.ICM = 0b011;
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

uint32_t getBeaconSensorTick(BeaconSensor_t whichSensor){
    if (whichSensor == ShortRangeBeaconSensor){
        return short_range_period;
    }
    else if (whichSensor == LongRangeBeaconSensor){
        return long_range_period;
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
//        DB_printf("short range period = %d\r\n", short_range_period);
    }while(IC5CONbits.ICBNE != 0);
    // VISHALS CODE
    // Period2Freq(ShortRangeBeaconSensor);
    IFS0CLR = _IFS0_IC5IF_MASK;

    // ------------------ VISHALS CODE --------------------------------
    // if within 10% of beacon b increment counter
    if ((uint16_t)(0.9*BEACON_B_TICKS) < short_range_period && 
        short_range_period < (uint16_t)(1.1*BEACON_B_TICKS)){
          numBeaconB++;  
        }

    // if within 10% of beacon c increment counter
    else if ((uint16_t)(0.9*BEACON_C_TICKS) < short_range_period && 
        short_range_period < (uint16_t)(1.1*BEACON_C_TICKS)){
            numBeaconC++;
    }

    // if neither signal then reset both beacon counters
    else {
        numBeaconB = 0;
        numBeaconC = 0;
    }

    // if we have a few beacon b pulses
    if (numBeaconB > NUM_VALID_BEACON_PULSE){
        numBeaconB = 0;                     // reset beacon b counter
        numBeaconC = 0;                     // reset beacon c counter

        // tell leader FSM which beacon was found
        ES_Event_t BeaconBEvent = {ES_FOUND_BEACON_B};
        ES_PostAll(BeaconBEvent);

        IEC0CLR = _IEC0_IC5IE_MASK;         // turn off ic5 isr
    }

    else if (numBeaconC > NUM_VALID_BEACON_PULSE){
        numBeaconB = 0;                     // reset beacon b counter
        numBeaconC = 0;                     // reset beacon c counter

        // tell leader FSM which beacon was found
        ES_Event_t BeaconCEvent = {ES_FOUND_BEACON_C};
        ES_PostAll(BeaconCEvent);

        IEC0CLR = _IEC0_IC5IE_MASK;         // turn off ic5 isr
    }
    // ----------------------------------------------------------------
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
