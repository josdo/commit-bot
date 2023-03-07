#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Port.h"
#include "terminal.h"
#include "dbprintf.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "TopHSM.h"
#include "../../Shared/EventOverSPI.h"
#include "Timer5.h"

// Number of rollovers for 2 min 18 sec
static const uint32_t total_rollover = 164;
static uint32_t rollover = 0;
void InitTimer5(void)
{
    T5CONbits.ON = 0;
    //selecting timer source
    T5CONbits.TCS = 0;
    // gated accumulation is off
    T5CONbits.TGATE = 0;
    // selecting a prescaler 4 for the timer
    T5CONbits.TCKPS = 0b111;
    // set the period on the timer    
    PR5 = 0xFFFF;
    // clear the timer flag
    IFS0CLR = _IFS0_T5IF_MASK;
    // setting timer priority
    IPC5bits.T5IP = 6;
    // starting from 0
    TMR5 = 0;
}

void startGameTimer(void)
{
    // enable the timer interrupts
    IEC0SET = _IEC0_T5IE_MASK;
    // turn on the timer 2
    T5CONbits.ON = 1;
    DB_printf("Timer5: Game timer started\r\n");
}

void __ISR(_TIMER_5_VECTOR, IPL6SOFT) gameTimer(void)
{
    __builtin_disable_interrupts();
    ++rollover;
    __builtin_enable_interrupts();
    IFS0CLR = _IFS0_T5IF_MASK;
}

/* Checks if game time reached and turns of timer if so. */
bool check4GameTimer(void)
{
    bool returnVal = false;
    if (rollover >= total_rollover){
        T5CONbits.ON = 0;
        ES_Event_t GameOverEvent = {ES_GAME_END, 0};

        DB_printf("Timer5: Game over\r\n");
        PostEventOverSPI(GameOverEvent);
        PostTopHSM(GameOverEvent);

        returnVal = true;
    }

    return returnVal;
}

