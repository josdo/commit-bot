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
#define NUMDrum 9 // LEDs in each drum strip
#define NUMClock 10 // LEDs in the timer
#define NumModules 4 // num of 8 bit words for each LED

#define LED_Start 0b11100000

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
static LED_t LeftDrum_Strip[NUMDrum];
static LED_t RightDrum_Strip[NUMDrum];
static LED_t BottomDrum_Strip[NUMDrum];
static LED_t Clock_Strip[NUMClock];

// pointers to the arrays above
static volatile LED_t * pLEDStrip; // pointer to the LED strip array
static volatile uint8_t NumLEDs; // pointer to the number of LEDs in the array
static volatile uint8_t Idx = 0; 

// this is the state variable for tracking init steps
static Clear_Steps_t CurrentInitStep =  LED_StartFrame;

// just zeros for clearing LEDs
static const uint32_t ZEROS = 0; // all 0's
uint32_t EndFrame = 0x11111111;

static LED_t ClearLEDs;

// not used right now
static uint8_t RightDrum_idx = 0;
static uint8_t LeftDrum_idx = 0;
static uint8_t BottomDrum_idx = 0;
static uint8_t Clock_idx = 0;

//------------------------------ Module Code ------------------------------*/


//****************************************************************************
bool Clear_Strip(LED_Types_t WhichStrip)
{
    bool returnVal = true;
    
    selectLEDStrip(WhichStrip); // get the proper LED array
    DefaultLED(); // create the default cleared LEDs
    
    for (uint8_t i=0; i < NumLEDs; i++){
        pLEDStrip[i].FullRow = ClearLEDs.FullRow;
    }
    
    return returnVal;
}
//****************************************************************************



//****************************************************************************
bool Set_Intensity(LED_Types_t WhichStrip, uint8_t intensity) {
    selectLEDStrip(WhichStrip);

    if (intensity < 0 || intensity > 31) { // make sure valid intensity value
        return false;
    }
    for (uint8_t i = 0; i < NumLEDs; i++) { // go through all the LEDs and set their brightness
        pLEDStrip[i].ByBytes[3] = (LED_Start | intensity);
    }

    return true;
}
// ****************************************************************************



// ****************************************************************************
bool Set_Single_Color(LED_Types_t WhichStrip, Colors_t WhichColor, uint8_t WhichLED) {
    bool ReturnVal = true;
    
    if (NoDrum_LEDs == WhichStrip){
        return false;
    }

    selectLEDStrip(WhichStrip);

    if (WhichLED > NumLEDs || WhichLED < 1) {
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
// ****************************************************************************



// ****************************************************************************
bool Set_All_Color(LED_Types_t WhichStrip, Colors_t WhichColor){
    bool ReturnVal = true;
    
    if (NoDrum_LEDs == WhichStrip){
        return false;
    }

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
// ****************************************************************************




//****************************************************************************

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
//      SPIOperate_SPI1_Send32Wait(ZEROS); // same as the start frame
      SPIOperate_SPI1_Send32Wait(EndFrame); // end frame is all 1s
      ReturnVal = true; // show we are done
      WhichLED = 0; // set up for next update
    }
    
    for (uint32_t i=0; i< 1000; i++){};
    
    return ReturnVal;
}
 // *************************************************************************



// PRIVATE FUNCTIONS
// *************************************************************************
static void selectLEDStrip(LED_Types_t WhichLED) {
    if (LeftDrum_LEDs == WhichLED) {
        pLEDStrip = LeftDrum_Strip;
        NumLEDs = NUMDrum;
        Idx = LeftDrum_idx;
    }
    
    else if (RightDrum_LEDs == WhichLED) {
        pLEDStrip = RightDrum_Strip;
        NumLEDs = NUMDrum;
        Idx = RightDrum_idx;
    }

    else if (BottomDrum_LEDs == WhichLED) {
        pLEDStrip = BottomDrum_Strip;
        NumLEDs = NUMDrum;
        Idx = BottomDrum_idx;
    }

    else if (Clock_LEDs == WhichLED) {
        pLEDStrip = Clock_Strip;
        NumLEDs = NUMClock;
        Idx = Clock_idx;
    }
}
// *************************************************************************

// *************************************************************************
static void DefaultLED(void){
    ClearLEDs.ByBytes[3] = 0b11100001;
    ClearLEDs.ByBytes[2] = 0;
    ClearLEDs.ByBytes[1] = 0;
    ClearLEDs.ByBytes[0] = 0;
}
// *************************************************************************
