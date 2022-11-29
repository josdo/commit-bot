/* 
 * File:   DM_Display.h
 * Author: Vishal
 *
 * Created on Nov 11, 2022
 */

#ifndef LED_Strip_H
#define	LED_Strip_H

#include "Utils.h"

// ################# Module Vars #################
typedef enum {
    Red = 1, Green, Blue, Purple, White, Yellow, Turquoise, Pink, Gold
} Colors_t;

//****************************************************************************
// Sets all the colors to 0 in the chosen LEDs array, intensity is set to 1
//****************************************************************************/
bool Clear_Strip( LED_Types_t WhichStrip);


// ****************************************************************************
// Set the intensity values of all LEDs in the chosen strip
// Intensity must be between 0 - 31 (i.e. 5 bit number)
// ****************************************************************************
bool Set_Intensity(LED_Types_t WhichStrip, uint8_t intensity);



//****************************************************************************
// Set a single LED in a chosen strip to a certain color
//****************************************************************************/
bool Set_Single_Color(LED_Types_t WhichStrip, Colors_t WhichColor, uint8_t WhichLED);



//****************************************************************************
// Set all the LEDs in a certain LED strip to a certain color
//****************************************************************************/
bool Set_All_Color(LED_Types_t WhichStrip, Colors_t WhichColor);



//****************************************************************************
//Copies the contents of the display buffer to the LED strip 1 LED per call.
//****************************************************************************/
bool TakeDisplayUpdateStep(LED_Types_t WhichStrip);


// PRIVATE FUNCTIONS
// ****************************************************************************
// Helper function used to set pointers to the chosen LED strip
// ****************************************************************************
static void selectLEDStrip(LED_Types_t WhichLED);


// ****************************************************************************
// Helper function used to create the default blank LED array
// ****************************************************************************
static void DefaultLED(void);

#endif

