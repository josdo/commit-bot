#ifndef TapeSensor_H
#define TapeSensor_H

#include "ES_Types.h"

void InitTapeSensor();

typedef enum {
    MiddleTapeSensor = 0,  //B13
    RightTapeSensor,       //B15
    LeftTapeSensor         //B12
} TapeSensor_t;

bool isOnTape(TapeSensor_t);

#endif /* TemplateService_H */
