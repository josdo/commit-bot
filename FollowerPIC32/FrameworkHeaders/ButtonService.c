#include <xc.h>
#include <stdbool.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "FollowerService.h"
#include "ButtonService.h"

uint16_t LastButtonState;

void InitButtonService(){
    puts("InitButtonStatus\r\n");
    TRISBbits.TRISB9 = 1;
    LastButtonState = PORTBbits.RB9;    
}

bool CheckButtonEvents(){
    bool returnVal = false;
    uint16_t CurrentButtonState;
    ES_Event_t ReturnEvent;
    CurrentButtonState = PORTBbits.RB9;
    if(CurrentButtonState!=LastButtonState){
        returnVal = true;
        if(CurrentButtonState == 0){
            ReturnEvent.EventType = ES_ButtonDown;
            PostFollowerService(ReturnEvent);
        }
        else{
            ReturnEvent.EventType = ES_ButtonUp;
            PostFollowerService(ReturnEvent);
        }
    }
    
    LastButtonState = CurrentButtonState;
    //printf("%b", returnVal);
    return returnVal;
}