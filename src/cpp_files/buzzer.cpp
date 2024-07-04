#include "buzzer.h"

void buzzer_on(){

    BUZZER_PORT |= (1 << BUZZER_PIN);

}

void buzzer_off(){

    BUZZER_PORT &= ~(1 << BUZZER_PIN);

}