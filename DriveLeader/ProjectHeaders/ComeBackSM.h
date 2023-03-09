/****************************************************************************
 Template header file for Hierarchical Sate Machines AKA StateCharts
 02/08/12 adjsutments for use with the Events and Services Framework Gen2
 3/17/09  Fixed prototpyes to use Event_t
 ****************************************************************************/

#ifndef ComeBackSM_H
#define ComeBackSM_H


// typedefs for the states
// State definitions for use with the query function
typedef enum { 
  STOP_COME_BACK,
  REVERSE1_TO_WALL,
  REVERSE2_TO_WALL,
  REVERSELAST_TO_WALL,
        MOVE_FORWARD_A_BIT,
        ROTATE_IN_REPO, 
} ComeBackState_t ;


// Public Function Prototypes

ES_Event_t RunComeBackSM( ES_Event_t CurrentEvent );
void StartComeBackSM ( ES_Event_t CurrentEvent );
ComeBackState_t QueryComeBackSM ( void );
bool Check4Wall(void);
#endif /*SHMTemplate_H */

