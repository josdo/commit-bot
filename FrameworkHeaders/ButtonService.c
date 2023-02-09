#include <xc.h>
#include <stdbool.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "LeaderService.h"
#include "ButtonService.h"

uint16_t LastButtonState;

void InitButtonService(){
    //puts("InitButtonStatus\r");
    TRISBbits.TRISB5 = 1;
    LastButtonState = PORTBbits.RB5;    
}

bool CheckButtonEvents(){
    bool returnVal = false;
    uint16_t CurrentButtonState;
    ES_Event_t ReturnEvent;
    CurrentButtonState = PORTBbits.RB5;
    if(CurrentButtonState!=LastButtonState){
        returnVal = true;
        if(CurrentButtonState == 0){
            ReturnEvent.EventType = ES_ButtonDown;
            PostLeaderService(ReturnEvent);
        }
        else{
            ReturnEvent.EventType = ES_ButtonUp;
            PostLeaderService(ReturnEvent);
        }
    }
    LastButtonState = CurrentButtonState;
    //printf("%b", returnVal);
    return returnVal;
}