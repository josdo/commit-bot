#ifndef TopHSM_H
#define TopHSM_H

// State definitions for use with the query function
typedef enum { IDLE, CALIBRATION, GO_TO_BRANCH_ORIGIN, FOLLOW_TAPE, COME_BACK } MasterState_t ;

// Public Function Prototypes

ES_Event_t RunTopHSM( ES_Event_t CurrentEvent );
void StartTopHSM ( ES_Event_t CurrentEvent );
bool PostTopHSM( ES_Event_t ThisEvent );
bool InitTopHSM ( uint8_t Priority );

#endif /*TopHSMTemplate_H */
