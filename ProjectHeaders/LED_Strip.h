/* 
 * File:   DM_Display.h
 * Author: Vishal
 *
 * Created on Nov 11, 2022
 */

#ifndef LED_Strip_H
#define	LED_Strip_H

// ################# Module Vars #################
typedef enum {
    Drum_LEDs = 0, Timer_LEDs, Intensity_LEDs
} LED_Types_t;

typedef enum {
    Red = 1, Green, Blue, Purple, White, Yellow, Turquoise, Pink
} Colors_t;

/****************************************************************************
 Function
  Clear_Strip

 Parameter
  None

 Returns
  bool: true when there are no more LEDs to clear; false
        while there still more LEDs

 Description
  
   
Example
   while ( false == Clear_LEDs() )
   {} // note this example is for non-event-driven code
****************************************************************************/
bool Clear_Strip( LED_Types_t WhichStrip);

bool Set_Intensity(LED_Types_t WhichStrip, uint8_t intensity);
void DefaultLED(void);


/****************************************************************************
 Function
  Set_Single_Color

 Parameter
  LED_Types_t: Which LED strip to set the color of
  Colors_t: One of the predefined colors
  WhichLED: Which LED in the strip

 Returns
  bool: true if successful, else false

 Description
   Sets the value of a single LED in the chosen strip to a predefined color

Example
   
****************************************************************************/
bool Set_Single_Color(LED_Types_t WhichStrip, Colors_t WhichColor, uint8_t WhichLED);


/****************************************************************************
 Function
  Set_All_Color

 Parameter
  LED_Types_t: Which LED strip to set the color of
  Colors_t: One of the predefined colors

 Returns
  bool: true if successful, else false

 Description
   Sets all the LEDs in the chosen strup to a predefined color

Example

****************************************************************************/
bool Set_All_Color(LED_Types_t WhichStrip, Colors_t WhichColor);

/****************************************************************************
 Function
  Write_Buffer_To_Strip

 Parameter
  LED_Types_t: Which LED strip to write

 Description
   Writes the contents of the buffer to the input LED strip

Example

****************************************************************************/
bool TakeDisplayUpdateStep(LED_Types_t WhichStrip);

void selectLEDStrip(LED_Types_t WhichLED);

#endif	/* DM_DISPLAY_H */

