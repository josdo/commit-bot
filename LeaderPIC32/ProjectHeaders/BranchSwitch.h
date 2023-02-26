#ifndef BranchSwitch_H
#define BranchSwitch_H

#include "ES_Types.h"


typedef enum{
    Branch1 = 0,
    Branch2,
    Branch3
} BranchType_t;

typedef enum{
    Dist50 = 0,
    Dist66,
    Dist82,
    Dist100
}BranchDist_t;



// Initialize the branch choosing switch
void InitSwitches(void);


BranchType_t GetBranch(void);
BranchDist_t GetDist(void);

#endif /* TemplateService_H */

