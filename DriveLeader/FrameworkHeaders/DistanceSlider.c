#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include "PIC32PortHAL.h"
#include "PIC32_AD_Lib.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "DistanceSlider.h"

uint32_t analog_signal[1];

static uint32_t AnalogValue = 0;
// max distance in cm
static uint32_t max_distance = 130; 

// ------------------- Constants for distance
static const uint16_t DIST_55_VAL = 855;
static const uint16_t DIST_70_VAL = 680;
static const uint16_t DIST_85_VAL = 513;
static const uint16_t DIST_100_VAL = 343;

void InitDistanceSlider()
{
    DB_printf("ES_INIT recieved in Distance Slider");
    
    ANSELBbits.ANSB13 = 1;
    TRISBbits.TRISB13 = 1;
    
    ADC_ConfigAutoScan(BIT11HI,1);
    
}

uint32_t getDistanceSliderValue(void)
{
    ADC_MultiRead(analog_signal);
    
    if (DIST_55_VAL - 10 < analog_signal[0] && 
            analog_signal[0] < DIST_55_VAL + 10){
        AnalogValue = 55 * max_distance /100;
    }
    else if (DIST_70_VAL - 10 < analog_signal[0] && 
            analog_signal[0] < DIST_70_VAL + 10){
        AnalogValue = 70 * max_distance /100;
    }
    
    else if (DIST_85_VAL - 10 < analog_signal[0] && 
            analog_signal[0] < DIST_85_VAL + 10){
        AnalogValue = 85 * max_distance /100;
    }
    
    else if (DIST_100_VAL - 10 < analog_signal[0] && 
            analog_signal[0] < DIST_100_VAL + 10){
        AnalogValue = 100 * max_distance /100;
    }
    return AnalogValue;
    
}

