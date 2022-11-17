/****************************************************************************
 Module
     DM_Display.c
 Description
     Source file for the Dot Matrix LED Hardware Abstraction Layer 
     used in ME218
 Notes
     This is the prototype. Students will re-create this functionality
 History
 When           Who     What/Why
 -------------- ---     --------
  10/03/21 12:32 jec    started coding
*****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
#include <xc.h>
#include <stdbool.h>
#include "PIC32_SPI_HAL.h"
#include "LED_Strip.h"

/*----------------------------- Module Defines ----------------------------*/
#define NUMDrum 27
#define NumIntensity 3
#define NumTimer 10
#define NumModules 4

#define LED_Start 0b11100000
uint32_t EndFrame = 0x11111111;


/*------------------------------ Module Types -----------------------------*/
// this union definition assumes that the display is made up of 4 modules
// 4 modules x 8 bits/module = 32 bits total
// this union allows us to easily scroll the whole buffer, using the uint32_t
// while picking out the individual bytes to send them to the controllers
typedef union{
    uint32_t FullRow;
    uint8_t ByBytes[NumModules];
} LED_t;

typedef enum { LED_StartFrame = 0, LED_Middle, LED_EndFrame
} Clear_Steps_t;

/*---------------------------- Module Functions ---------------------------*/

/*---------------------------- Module Variables ---------------------------*/
// We make the display buffer from an array of these unions, one for each 
// row in the display
static LED_t Drum_Strip[NUMDrum];
static LED_t Intensity_Strip[NumIntensity];
static LED_t Timer_Strip[NumTimer];

static volatile LED_t * pLEDStrip; // pointer to the LED strip array
static volatile uint8_t NumLEDs; // pointer to the number of LEDs in the array
static volatile uint8_t Idx = 0; 

// this is the state variable for tracking init steps
static Clear_Steps_t CurrentInitStep =  LED_StartFrame;

static const uint32_t ZEROS = 0; // all 0's

static LED_t ClearLEDs;

static uint8_t Drum_idx = 0;
static uint8_t Timer_idx = 0;
static uint8_t Intensity_idx = 0;

/*------------------------------ Module Code ------------------------------*/
void DefaultLED(void){
    ClearLEDs.ByBytes[3] = 0b11100000;
    ClearLEDs.ByBytes[2] = 0;
    ClearLEDs.ByBytes[1] = 0;
    ClearLEDs.ByBytes[0] = 0;
}

/****************************************************************************
 Function
  DM_TakeInitDisplayStep

  Description
  Initializes the MAX7219 4-module display performing 1 step for each call:
    First, bring put it in shutdown to disable all displays, return false
    Next fill the display RAM with Zeros to insure blanked, return false
    Then Disable Code B decoding for all digits, return false
    Then, enable scanning for all digits, return false
    The next setup step is to set the brightness to minimum, return false
    Copy our display buffer to the display, return false
    Finally, bring it out of shutdown and return true
****************************************************************************/
bool Clear_Strip(LED_Types_t WhichStrip)
{
    bool returnVal = true;
    
    selectLEDStrip(WhichStrip); // get the proper LED array
    DefaultLED(); // create the default cleared LEDs
    
    for (uint8_t i=0; i < NumLEDs; i++){
        pLEDStrip[i].FullRow = ClearLEDs.FullRow;
    }
    
    return returnVal;
//    static uint8_t LEDIndex = 1;
//    bool ReturnVal = false;
//
//    selectLEDStrip(WhichStrip);
//
//    switch (CurrentInitStep) {
//    case LED_StartFrame: // send the init frame
//        SPIOperate_SPI1_Send32(ZEROS);
//        CurrentInitStep++;
//        break;
//
//    case LED_Middle:
//        if (LEDIndex > 10) { // have cleared all the LEDs
//            CurrentInitStep++;
//        }
//
//        else {
//            SPIOperate_SPI1_Send32(ClearLEDs.FullRow);
//            LEDIndex++;
//        }
//        break;
//
//    case LED_EndFrame: // end frame is just another zero frame
//        SPIOperate_SPI1_Send32Wait(ZEROS);
//        CurrentInitStep = LED_StartFrame;
//        LEDIndex = 1;
//        ReturnVal = true;
//        break;
//    }
//    
//    for (uint32_t i = 0; i < 40000; i++) {}; // need small delay between sending data
//    return ReturnVal;
}

bool Set_Intensity(LED_Types_t WhichStrip, uint8_t intensity) {
    selectLEDStrip(WhichStrip);

    if (intensity < 0 || intensity > 31) { // make sure valid intensity value
        return false;
    }
    for (uint8_t i = 0; i < NumLEDs; i++) { // go through all the LEDs and set their brightness
        pLEDStrip[i].ByBytes[3] = (LED_Start | intensity);
//        pLEDStrip[i].ByBytes[3] = 0b11100001;
    }

    return true;
}

bool Set_Single_Color(LED_Types_t WhichStrip, Colors_t WhichColor, uint8_t WhichLED) {
    bool ReturnVal = true;

    selectLEDStrip(WhichStrip);

    if (WhichLED > NumLEDs) {
        ReturnVal = false;
    }

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
    
    switch (WhichColor) {
    case Red:
        red = 255;   // R
        green = 0;     // G
        blue = 0;     // B
        break;

    case Green:
        red = 0;     // R
        green = 255;   // G
        blue = 0;     // B
        break;

    case Blue:
        red = 0;     // R
        green = 0;     // G
        blue = 255;   // B
        break;

    case Purple:
        red = 255;   // R
        green = 0;   // G
        blue = 255;     // B
        break;

    case White:
        red = 255;   // R
        green = 255;   // G
        blue = 255;   // B
        break;

    case Yellow:
        red = 255;   // R
        green = 105;   // G
        blue = 0;     // B
        break;

    case Turquoise:
        red = 127;   // R
        green = 255;   // G
        blue = 170;   // B
        break;
        
    case Pink:
        red = 255;
        green = 25;
        blue = 25;
        break;
        
    default:
        red = 0;
        green = 0;
        blue = 0;
        break;
    }
    
    pLEDStrip[WhichLED - 1].ByBytes[0] = red;   // R
    pLEDStrip[WhichLED - 1].ByBytes[1] = green;   // G
    pLEDStrip[WhichLED - 1].ByBytes[2] = blue;   // B
    
    return ReturnVal;
}

bool Set_All_Color(LED_Types_t WhichStrip, Colors_t WhichColor){
    bool ReturnVal = true;

    selectLEDStrip(WhichStrip);
    
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
    switch (WhichColor) {
    case Red:
        red = 255;   // R
        green = 0;     // G
        blue = 0;     // B
        break;

    case Green:
        red = 0;     // R
        green = 255;   // G
        blue = 0;     // B
        break;

    case Blue:
        red = 0;     // R
        green = 0;     // G
        blue = 255;   // B
        break;

    case Purple:
        red = 255;  // R
        green = 0;    // G
        blue = 255;  // B
        break;

    case White:
        red = 255;   // R
        green = 255;   // G
        blue = 255;   // B
        break;

    case Yellow:
        red = 255;   // R
        green = 105;   // G
        blue = 0;     // B
        break;

    case Turquoise:
        red = 127;   // R
        green = 255;   // G
        blue = 170;   // B
        break;
        
    case Pink:
        red = 255;
        green = 25;
        blue = 50;
        break;
        
    default:
        red = 0;
        green = 0;
        blue = 0;
        break;
    }
    
    for (uint8_t i = 0; i < NumLEDs; i++){
        pLEDStrip[i].ByBytes[0] = red;       // R
        pLEDStrip[i].ByBytes[1] = green;     // G
        pLEDStrip[i].ByBytes[2] = blue;      // B
    }
    
    return ReturnVal;
}
 // *************************************************************************
void selectLEDStrip(LED_Types_t WhichLED) {
    if (Drum_LEDs == WhichLED) {
        pLEDStrip = Drum_Strip;
        NumLEDs = NUMDrum;
        Idx = Drum_idx;
    }

    else if (Timer_LEDs == WhichLED) {
        pLEDStrip = Timer_Strip;
        NumLEDs = NumTimer;
        Idx = Timer_idx;
    }

    else if (Intensity_LEDs == WhichLED) {
        pLEDStrip = Intensity_Strip;
        NumLEDs = NumIntensity;
        Idx = Intensity_idx;
    }
}


// *************************************************************************

/****************************************************************************
 Function
  DM_TakeDisplayUpdateStep

 Description
  Copies the contents of the display buffer to the MAX7219 controllers 1 row
  per call.
****************************************************************************/
bool TakeDisplayUpdateStep(LED_Types_t WhichStrip)
{
    bool ReturnVal = false;
    static int8_t WhichLED = 0;

    selectLEDStrip(WhichStrip);

    if (0 == WhichLED) { // always start with the zero frame
        SPIOperate_SPI1_Send32(ZEROS);
    }
    
    SPIOperate_SPI1_Send32(pLEDStrip[WhichLED].FullRow);
    WhichLED++;

    // your code  to check when we are done sending rows goes here 
    if (NumLEDs == WhichLED)
    {
//      SPIOperate_SPI1_Send32(ZEROS);
      SPIOperate_SPI1_Send32Wait(EndFrame);
//      SPIOperate_SPI1_Send32Wait(EndFrame); // end frame is also all 0's
      ReturnVal = true; // show we are done
      WhichLED = 0; // set up for next update
    }
    
    for (uint32_t i=0; i< 500; i++){};
    
    return ReturnVal;
}





