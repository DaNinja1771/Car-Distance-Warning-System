#ifndef BUZZER_H
#define BUZZER_H

#include "main.h"
#include "pwm.h"

#define BUZZER_PORT DDRE
#define BUZZER_PIN DDE5

void buzzer_on();
void buzzer_off();

#endif