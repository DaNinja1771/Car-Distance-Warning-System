#ifndef LED_H
#define LED_H

#include "main.h"
#include "buzzer.h"

#define GREEN_PORT  PORTA
#define YELLOW_PORT PORTA
#define RED_PORT    PORTA

#define GREEN_PIN   PORTA0
#define YELLOW_PIN  PORTA1
#define RED_PIN     PORTA2

void led_init();
void led_run(uint8_t led_num);

#endif