#include <xc.h>
#include <stdbool.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"

#include "../../Shared/EventOverSPI.h"
#include "ButtonService.h"
#include "BranchSwitch.h"

static bool LastButtonState;
static bool isGameStarted = false;

void InitButtonService(){
    puts("InitButtonStatus\r\n");
    TRISBbits.TRISB10 = 1;                  // RB10 input
    
    CNPDBSET = _CNPDB_CNPDB10_MASK;         // pull down resistor
    InitEventOverSPI(false);                // configure follower mode
    
    LastButtonState = PORTBbits.RB10; 
}

bool CheckButtonEvents(){
    bool returnVal = false;                  // default return false
    bool CurrentButtonState;            // current button state
//    BranchDist_t whichDist = GetDist();
    
    ES_Event_t ReturnEvent;             
    
    CurrentButtonState = PORTBbits.RB10;     // read button
    
    if( ((CurrentButtonState!=LastButtonState) && (CurrentButtonState == 0))  ){        // if new state
        returnVal = true;
        BranchType_t whichBranch = GetBranch();
        
        ReturnEvent.EventType = ES_BUTTON_PRESS;    // button press event
        ReturnEvent.EventParam = whichBranch;       // which branch to go to
        
        printf("ES_BUTTON_PRESS = %u\r\n", ES_BUTTON_PRESS);
        printf("\tevent param = %d\r\n", whichBranch);
        
        ES_PostAll(ReturnEvent);
        
        PostEventOverSPI(ReturnEvent);              // send event over SPI
        
        if (isGameStarted == false){
            ES_Event_t GameEvent = {ES_GAME_START, 0};
            ES_PostAll(GameEvent);
            isGameStarted = true;
        }
        
        
    }
    
    LastButtonState = CurrentButtonState;
    //printf("%b", returnVal);
    return returnVal;
}