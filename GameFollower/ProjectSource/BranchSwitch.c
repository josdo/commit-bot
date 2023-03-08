#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BranchSwitch.h"
#include "PIC32_AD_Lib.h"

// ###################### NOTES #####################
// SwitchReadings[0] is RB12 = AN12 - Branch switch

// ------------------------------- Module Vars -----------------------------
static uint32_t SwitchReadings[1];      // array for switch readings

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
    
    TRISBbits.TRISB12 = 1;              // RB12 is input
    // ---------------------------------------------------------------
    
    
    // ---------------------------- Set Up Analog Read -----------------------
    ADC_ConfigAutoScan(BIT12HI, 1);       // configure the analog read
    // -----------------------------------------------------------------------

    
    puts("\tBranch switch pin has been init\r\n");
}

BranchType_t GetBranch(void){
    ADC_MultiRead(SwitchReadings);                  // read the pins
    
    printf("\tBranch analog reading = %d\r\n", SwitchReadings[0]);
    
    BranchType_t WhichBranch = BranchErr;
    
    if (BRANCH_1_VAL - 50 < SwitchReadings[0] && 
            SwitchReadings[0] < BRANCH_1_VAL + 50){
        WhichBranch = Branch1;
    }
    
    else if (BRANCH_2_VAL - 50 < SwitchReadings[0] && 
            SwitchReadings[0] < BRANCH_2_VAL + 50){
        WhichBranch = Branch2;
    }
    
    else if (BRANCH_3_VAL - 50 < SwitchReadings[0] && 
            SwitchReadings[0] < BRANCH_3_VAL + 50){
        WhichBranch = Branch3;
    }
    
    return WhichBranch;
}
