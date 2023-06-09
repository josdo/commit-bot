#ifndef CalibrationSM_H
#define CalibrationSM_H

typedef enum {INIT_CALIBRATION, ROTATE_TO_ALIGN, BACK_UP} CalibrationSMState_t;

ES_Event_t RunCalibrationSM(ES_Event_t CurrentEvent);
void StartCalibrationSM( ES_Event_t CurrentEvent );
CalibrationSMState_t QueryCalibrationSM ( void );

#endif
