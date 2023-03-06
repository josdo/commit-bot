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

#define THRESHOLD 700
uint32_t analog_signal[3];
//static uint16_t LastAnalogValueLeft = 0;
static uint16_t CurrentAnalogValueLeft = 0;
static uint16_t CurrentAnalogValueMiddle = 0;
static uint16_t CurrentAnalogValueRight = 0;

void InitTapeSensor()
{
    DB_printf("ES_INIT received in Tape Sensor Service %d\r\n");
    // pins setup
    // left tape sensor
    ANSELBbits.ANSB12 = 1;
    TRISBbits.TRISB12 = 1;
    
    // Middle tape sensor
    ANSELBbits.ANSB13 = 1;
    TRISBbits.TRISB13 = 1;
    
    // Right tape sensor
    ANSELBbits.ANSB15 = 1;
    TRISBbits.TRISB15 = 1;
    
    ADC_ConfigAutoScan(BIT12HI | BIT11HI | BIT9HI, 3);
}

uint16_t getTapeValue(TapeSensor_t WhichTapeSensor)
{
    ADC_MultiRead(analog_signal);
    CurrentAnalogValueLeft = analog_signal[2];
    CurrentAnalogValueMiddle = analog_signal[1];
    CurrentAnalogValueRight = analog_signal[0];
    
    switch (WhichTapeSensor) {
        case LeftTapeSensor:
        {
            return CurrentAnalogValueLeft;
       
        }
        break;
        case MiddleTapeSensor:
        {
            return CurrentAnalogValueMiddle;
        }
        break;
        case RightTapeSensor:
        {
            return CurrentAnalogValueRight;
        }
    }  
}

bool isOnTape(TapeSensor_t WhichTapeSensor){
    ADC_MultiRead(analog_signal);
    CurrentAnalogValueLeft = analog_signal[2];
    CurrentAnalogValueMiddle = analog_signal[1];
    CurrentAnalogValueRight = analog_signal[0];
    
    switch (WhichTapeSensor) {
        case LeftTapeSensor:
        {
            if (CurrentAnalogValueLeft > THRESHOLD){
                return true;
            }
            else {
                return false;
            }
            }
        break;
        case MiddleTapeSensor:
        {
            if (CurrentAnalogValueMiddle > THRESHOLD){
                return true;
            }
            else{
                return false;
            }
        }
        break;
        case RightTapeSensor:
        {
            if (CurrentAnalogValueRight > THRESHOLD){
                return true;
            }
            else{
                return false;
            }
        }
    }  
}