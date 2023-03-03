#include <xc.h>


#include "ES_Configure.h"
#include "ES_Framework.h"
#include "LEDService.h"

static uint8_t MyPriority;

bool InitLEDService(uint8_t Priority)
{
  MyPriority = Priority;
  
  puts("Init LED service\r\n");
  printf("ES_FOUND_BEACON_C = %u\r\n", ES_FOUND_BEACON_C);
  puts("fkjkldasf\r\n");
  
  TRISAbits.TRISA2 = 0;             // RA2 output - BLUE
  TRISAbits.TRISA3 = 0;             // RA3 output - RED
  
  LATACLR = _LATA_LATA2_MASK;       // turn off
  LATACLR = _LATA_LATA3_MASK;       // turn off

  // Post successful initialization
  ES_Event_t ThisEvent = {ES_INIT};
  return ES_PostToService(MyPriority, ThisEvent);
}

bool PostLEDService(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event_t RunLEDService(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  // TODO write service code
  switch(ThisEvent.EventType){
      case ES_FOUND_BEACON_B: {
          puts("LED found beacon B\r\n");
//          RED = 0;
//          BLUE = 1;
          
          LATASET = _LATA_LATA3_MASK;
          LATACLR = _LATA_LATA2_MASK;
      }
      break;
      
      case ES_FOUND_BEACON_C: {
          puts("LED found beacon C\r\n");
//          RED = 1;
//          BLUE = 0;
          
          LATACLR = _LATA_LATA3_MASK;
          LATASET = _LATA_LATA2_MASK;
      }
      break;
      
      case ES_GAME_START: {
          puts("game start in LED\r\n");
          LATACLR = _LATA_LATA2_MASK;       // turn off
          LATACLR = _LATA_LATA3_MASK;       // turn off
      }
      break;
      
      case ES_GAME_END: {
          puts("game end in LED\r\n");
          LATACLR = _LATA_LATA2_MASK;       // turn off
          LATACLR = _LATA_LATA3_MASK;       // turn off
      }
      break;
  }

  return ReturnEvent;
}