#ifndef CalibrationSM_H
#define CalibrationSM_H

typedef enum {ROTATE_TO_ALIGN, STOP,
        BACK_UP, FORWARD_UNTIL_BEACON} CalibrationSMState_t;

ES_Event_t RunCalibrationSM(ES_Event_t CurrentEvent);
void StartCalibrationSM( ES_Event_t CurrentEvent );
CalibrationSMState_t QueryCalibrationSM ( void );
bool Check4CornerBeacons(void);
bool check4Tape(void);
#endif
