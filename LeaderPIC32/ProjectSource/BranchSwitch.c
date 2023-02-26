#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BranchSwitch.h"
#include "PIC32_AD_Lib.h"

// ###################### NOTES #####################
// SwitchReadings[0] is RB13 - Distance switch
// SwitchReadings[1] is RB12 - Branch switch

// ------------------------------- Module Vars -----------------------------
static uint32_t SwitchReadings[2];      // array for switch readings
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
    
}


BranchDist_t GetDist(void){
    ADC_MultiRead(SwitchReadings);                  // read the pins
}
