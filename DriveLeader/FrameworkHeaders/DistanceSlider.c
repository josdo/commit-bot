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

static uint32_t analog_signal[1];

// Length of branch in cm.
static uint32_t max_distance = 143; 

/* Percentages down the branch to travel. */
// analog 850
static const uint16_t percent1 = 60;
// analog 670
static const uint16_t percent2 = 70;
// analog 510
static const uint16_t percent3 = 85;
// analog 340
static const uint16_t percent4 = 100;

static const uint16_t threshold1_2 = 750;
static const uint16_t threshold2_3 = 600;
static const uint16_t threshold3_4 = 400;

void InitDistanceSlider()
{
    DB_printf("ES_INIT recieved in Distance Slider");
    
    ANSELBbits.ANSB13 = 1;
    TRISBbits.TRISB13 = 1;
    
    ADC_ConfigAutoScan(BIT11HI,1);
}

/* Returns desired branch distance to travel in cm.
   Higher voltage is lower on the toggle switch. */
uint32_t getDesiredBranchDistance(void)
{
    ADC_MultiRead(analog_signal);

    uint32_t desired_distance;
    if (analog_signal[0] > threshold1_2){
        desired_distance = percent1 * max_distance /100;
    }
    else if (analog_signal[0] > threshold2_3){
        desired_distance = percent2 * max_distance /100;
    }
    else if (analog_signal[0] > threshold3_4){
        desired_distance = percent3 * max_distance /100;
    }
    else {
        desired_distance = percent4 * max_distance /100;
    }
    
    DB_printf("DistanceSlider: read desired branch distance of %d cm\r\n", desired_distance);
    return desired_distance;
}

