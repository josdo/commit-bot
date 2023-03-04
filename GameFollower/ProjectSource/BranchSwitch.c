#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BranchSwitch.h"
#include "PIC32_AD_Lib.h"

// ###################### NOTES #####################
// SwitchReadings[0] is RB13 = AN11 - Distance switch
// SwitchReadings[1] is RB12 = AN12 - Branch switch

// ------------------------------- Module Vars -----------------------------
static uint32_t SwitchReadings[2];      // array for switch readings

// -------------------  Constants for which branch
static const uint16_t BRANCH_1_VAL = 855;
static const uint16_t BRANCH_2_VAL = 680;
static const uint16_t BRANCH_3_VAL = 513;

// ------------------- Constants for distance
static const uint16_t DIST_50_VAL = 855;
static const uint16_t DIST_66_VAL = 680;
static const uint16_t DIST_82_VAL = 513;
static const uint16_t DIST_100_VAL = 343;
// ----------------------------------------------------------------------------

void InitSwitches(void)
{
    // ---------------------------- Init Pins --------------------------
    ANSELBbits.ANSB12 = 1;              // RB12 is analog
    ANSELBbits.ANSB13 = 1;              // R13 is analog
    
    TRISBbits.TRISB12 = 1;              // RB12 is input
    TRISBbits.TRISB13 = 1;              // RB13 is input
    // ---------------------------------------------------------------
    
    
    // ---------------------------- Set Up Analog Read -----------------------
    ADC_ConfigAutoScan(BIT12HI | BIT11HI, 2);       // configure the analog read
    // -----------------------------------------------------------------------

    
    puts("\tBranch switch pin has been init\r\n");
}

BranchType_t GetBranch(void){
    ADC_MultiRead(SwitchReadings);                  // read the pins
    
    printf("\tBranch analog reading = %d\r\n", SwitchReadings[1]);
    
    BranchType_t WhichBranch = BranchErr;
    
    if (BRANCH_1_VAL - 10 < SwitchReadings[1] && 
            SwitchReadings[1] < BRANCH_1_VAL + 10){
        WhichBranch = Branch1;
    }
    
    else if (BRANCH_2_VAL - 10 < SwitchReadings[1] && 
            SwitchReadings[1] < BRANCH_2_VAL + 10){
        WhichBranch = Branch2;
    }
    
    else if (BRANCH_3_VAL - 10 < SwitchReadings[1] && 
            SwitchReadings[1] < BRANCH_3_VAL + 10){
        WhichBranch = Branch3;
    }
    
    return WhichBranch;
}


BranchDist_t GetDist(void){
    ADC_MultiRead(SwitchReadings);                  // read the pins
    
    printf("Distance analog reading = %d\r\n", SwitchReadings[0]);
    
    BranchDist_t WhichDist = DistErr;
    
    if (DIST_50_VAL - 10 < SwitchReadings[0] && 
            SwitchReadings[0] < DIST_50_VAL + 10){
        WhichDist = Dist50;
    }
    
    else if (DIST_66_VAL - 10 < SwitchReadings[0] && 
            SwitchReadings[0] < DIST_66_VAL + 10){
        WhichDist = Dist66;
    }
    
    else if (DIST_82_VAL - 10 < SwitchReadings[0] && 
            SwitchReadings[0] < DIST_82_VAL + 10){
        WhichDist = Dist82;
    }
    
    else if (DIST_100_VAL - 10 < SwitchReadings[0] && 
            SwitchReadings[0] < DIST_100_VAL + 10){
        WhichDist = Dist100;
    }
    
    return WhichDist;
}
