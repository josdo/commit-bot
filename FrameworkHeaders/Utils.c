#include "Utils.h"

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ControllerFSM.h"



// MUX defines
#define MUX_A_PIN LATBbits.LATB8
#define MUX_B_PIN LATBbits.LATB9

#define MUX_A_TRIS TRISBbits.TRISB8
#define MUX_B_TRIS TRISBbits.TRISB9

void InitMUXPins(void){
 // Set up the MUX outputs from the PIC
  MUX_A_TRIS = 0;
  MUX_B_TRIS = 0;
}

void SetMuxOutput(LED_MUX_t WhichOutput){
    switch(WhichOutput){
        case Drums: { // 0
            MUX_A_PIN = 0;
            MUX_B_PIN = 0;
        }
        break;
        
        case Timer: { // 1
            MUX_A_PIN = 1;
            MUX_B_PIN = 0;
        }
        break;
        
        case Intensity: { // 2
            MUX_A_PIN = 0;
            MUX_B_PIN = 1;
        }
        break;
        
        case None: { // 3
            MUX_A_PIN = 1;
            MUX_B_PIN = 1;
        }
        break;
    }
}