#ifndef GoToBranchOriginSM_H
#define GoToBranchOriginSM_H

typedef enum {  BRANCH_ONE,
                BRANCH_TWO,
                BRANCH_THREE} GoToBranchOriginState_t;

ES_Event_t RunGoToBranchOriginSM(ES_Event_t CurrentEvent);
void StartGoToBranchOriginSM( ES_Event_t CurrentEvent );
GoToBranchOriginState_t QueryGoToBranchOriginSM ( void );

bool check4MiddleBranch(void);
bool Check4ThirdBranch(void);
#endif