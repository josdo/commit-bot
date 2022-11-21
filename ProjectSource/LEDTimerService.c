/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LEDTimerService.h"

#include "LED_Strip.h"
#include "PIC32_SPI_HAL.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

// keep track of LED intensity
static uint8_t LEDIntensity = 1;

// next color in welcoming state
Colors_t NextWelcomingColor;

/*------------------------------ Module Code ------------------------------*/
bool InitLEDTimerService(uint8_t Priority)
{
  // Init module level variables
  MyPriority = Priority;
  
  // set SPI up for LEDs
  SPISetup_BasicConfig(SPI_SPI1);
  SPISetup_SetLeader(SPI_SPI1, SPI_SMP_MID); // make pic332 leader  
  SPISetup_SetBitTime(SPI_SPI1, 10000); // 1000 kHz clock
  SPISetup_MapSSOutput(SPI_SPI1, SPI_RPA0); // set SS to pin 2
  SPISetup_MapSDOutput(SPI_SPI1, SPI_RPA1); // set SDO to pin 3
  SPISetup_SetXferWidth(SPI_SPI1, SPI_32BIT); // 16 bit datawidth
  SPISetup_SetClockIdleState(SPI_SPI1, SPI_CLK_HI); // active high
  SPISetup_SetActiveEdge(SPI_SPI1, SPI_SECOND_EDGE); // second edge
  SPISetEnhancedBuffer(SPI_SPI1, true); // enable enhanced buffer
  SPISetup_EnableSPI(SPI_SPI1); // turn on the SPI module
  IFS0CLR = _IFS0_INT4IF_MASK;
  
    // Set the drum LED strip
  Clear_Strip(Drum_LEDs); // clear the LEDs
  Set_Intensity(Drum_LEDs, LEDIntensity); // min intensity
  
  // set the next color
  NextWelcomingColor = Turquoise;
  
  
  // Post successful initialization
  ES_Event_t ThisEvent;
  ThisEvent.EventType = ES_INIT;
  if (ES_PostToService(MyPriority, ThisEvent) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PostLEDTimerService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunLEDTimerService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch(ThisEvent.EventType){
      case ES_INIT: {
          
      }
      break;
      
      case ES_TIMEOUT: {
          
      }
      break;
  }

  return ReturnEvent;
}

/***************************************************************************
 private functions
 ***************************************************************************/

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/

