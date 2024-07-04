#include "led.h"

void led_init(){
    DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2);

    GREEN_PORT  |= (1 << GREEN_PIN);    //Green LED
    YELLOW_PORT |= (1 << YELLOW_PIN);   //Yellow LED
    RED_PORT    |= (1 << RED_PIN);      //Red LED

}

/*
This function turns the LEDs and buzzer on or off depending on the state of saftey in main
*/
void led_run(uint8_t led_num){

    switch (led_num){

        case 0:
            buzzer_off();
            GREEN_PORT  |= (1 << GREEN_PIN);    //Green
            YELLOW_PORT &= ~(1 << YELLOW_PIN);  //Yellow
            RED_PORT    &= ~(1 << RED_PIN);     //Red
            break;

        case 1:
            buzzer_off();
            GREEN_PORT  &= ~(1 << GREEN_PIN);   //Green
            YELLOW_PORT |= (1 << YELLOW_PIN);   //Yellow
            RED_PORT    &= ~(1 << RED_PIN);     //Red
            break;

        case 2:
            buzzer_on();
            GREEN_PORT  &= ~(1 << GREEN_PIN);   //Green
            YELLOW_PORT &= ~(1 << YELLOW_PIN);  //Yellow
            RED_PORT    |= (1 << RED_PIN);      //Red
            break;
    }
}
