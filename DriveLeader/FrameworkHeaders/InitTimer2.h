#ifndef InitTimer2_H
#define InitTimer2_H

#include "ES_Types.h"

typedef union{
    uint32_t actual_time;
    struct{
        uint16_t local_time;
        uint16_t rollover;
    }time_var;
}global_time;

void updateGlobalTime(uint16_t capturedTime);
uint32_t T2_tick_to_ns(void);
uint32_t T2_actual_time(void);

void InitTimer2(void);
#endif 