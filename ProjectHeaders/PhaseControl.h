/*  Control three parts of stepping: 
    * where is magnetic pull
    * how strong is the pull
    * how quickly does the pull move around the circumference
*/

#include "PWM_PIC32.h"
#include "PIC32PortHAL.h"

void InitPhaseControl();