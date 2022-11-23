#ifndef communication_pwm_service_H
#define communication_pwm_service_H

#include <stdint.h>
#include <stdbool.h>

#include "ES_Events.h"
#include "ES_Port.h"                // needed for definition of REENTRANT
// Public Function Prototypes

bool Initcommunication_pwm_service(uint8_t Priority);
bool Postcommunication_pwm_service(ES_Event_t ThisEvent);
ES_Event_t Runcommunication_pwm_service(ES_Event_t ThisEvent);

#endif /* ServTemplate_H */