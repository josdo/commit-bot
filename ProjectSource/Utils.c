#include "Utils.h"

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Controller.h"



// MUX defines
#define MUX_A_PIN LATAbits.LATA2
#define MUX_B_PIN LATBbits.LATB9

#define MUX_A_TRIS TRISAbits.TRISA2
#define MUX_B_TRIS TRISBbits.TRISB9

void InitMUXPins(void){
 // Set up the MUX outputs from the PIC
  MUX_A_TRIS = 0;
  MUX_B_TRIS = 0;
}

void SetMuxOutput(LED_Types_t WhichOutput){
    switch(WhichOutput){
        case LeftDrum_LEDs: { // 0
            MUX_A_PIN = 0;
            MUX_B_PIN = 0;
        }
        break;
        
        case RightDrum_LEDs: { // 1
            MUX_A_PIN = 1;
            MUX_B_PIN = 0;
        }
        break;
        
        case BottomDrum_LEDs: { // 2
            MUX_A_PIN = 0;
            MUX_B_PIN = 1;
        }
        break;
        
        case Clock_LEDs: { // 3
            MUX_A_PIN = 1;
            MUX_B_PIN = 1;
        }
        break;
    }
}