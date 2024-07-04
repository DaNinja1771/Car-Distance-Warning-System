#ifndef PWM_H
#define PWM_H

#define PWM_DEFAULT_FREQUENCY 2500

#include "main.h"

void pwm_init();
void pwm_set_frequency(unsigned int frequency);

#endif