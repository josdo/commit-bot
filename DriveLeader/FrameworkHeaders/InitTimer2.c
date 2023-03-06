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
    // selecting a prescaler 4 for the timer
    T2CONbits.TCKPS = 0b010;
    // set the period on the timer    
    PR2 = 0xFFFF;
    // enable the timer interrupts
    IEC0SET = _IEC0_T2IE_MASK;
    // clear the timer flag
    IFS0CLR = _IFS0_T2IF_MASK;
    // setting timer priority
    IPC2bits.T2IP = 6;
    // starting from 0
    TMR2 = 0;
    // turn on the timer 2
    T2CONbits.ON = 1;
}

// Prescale of 4
uint32_t T2_tick_to_ns(void)
{
  return 200;
}

uint32_t T2_actual_time(void)
{
  return gl.actual_time;
}

/* Updates if the interrupt flag is set. */
void updateGlobalTime(uint16_t capturedTime){
    __builtin_disable_interrupts();
    if(IFS0bits.T2IF == 1 && capturedTime < 0x8000){
        ++(gl.time_var.rollover);
        IFS0CLR = _IFS0_T2IF_MASK;
    }
    gl.time_var.local_time = capturedTime;
    __builtin_enable_interrupts();
}
