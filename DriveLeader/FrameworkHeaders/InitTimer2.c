#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Port.h"
#include "terminal.h"
#include <xc.h>            
#include <sys/attribs.h>
#include "InitTimer2.h"

volatile global_time gl;

void InitTimer2(){
    gl.time_var.rollover = 0;
    
    // INPUT CAPTURE
    //switching the timer off
    T2CONbits.ON = 0;
    //selecting timer source
    T2CONbits.TCS = 0;
    // gated accumulation is off
    T2CONbits.TGATE = 0;
    // selecting a prescaler 2 for the timer
    T2CONbits.TCKPS = 0b001;
    // set the period on the timer    
    PR2 = 0xFFFF;
    // clear the timer flag
    IFS0CLR = _IFS0_T2IF_MASK;
    // enable the timer interrupts
    IEC0SET = _IEC0_T2IE_MASK;
    // setting timer priority
    IPC2bits.INT2IP = 6;
    // starting from 0
    TMR2 = 0;
    // turn on the timer 2
    T2CONbits.ON = 1;

}


void __ISR(_TIMER_2_VECTOR, IPL6SOFT) CountRollOver(void){
    __builtin_disable_interrupts();
    if(IFS0bits.T2IF == 1){
        ++(gl.time_var.rollover);
        IFS0CLR = _IFS0_T2IF_MASK;
    }
    __builtin_enable_interrupts();
}