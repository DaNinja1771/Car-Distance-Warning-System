#include "pwm.h"
#include "buzzer.h"

// use timer 3 for calculatons of variable freq
void pwm_init(){
    //table 17-2, we need fast PWM, mode 15 for variable frequency
    TCCR3A |= (1<<WGM30) | (1<<WGM31);
    TCCR3B |= (1<<WGM32) | (1<<WGM33);
    // table 17-4, Fast PWM non-inverting mode
    TCCR3A &= ~(1<<COM3C0);
    TCCR3A |=  (1<<COM3C1);
    //table 17-6, set prescaler to 1
    TCCR3B |= (1<<CS30);
    //Set Pin 3 on board to output, which is OC3C, PORTE5, PWM
    BUZZER_PORT |= (1<<BUZZER_PIN); 

    pwm_set_frequency(PWM_DEFAULT_FREQUENCY);
}

/*
Used for setting frequency with unsigned int frequency
frequency does not matter since an active buzzer is used
*/
void pwm_set_frequency(unsigned int frequency){
    OCR3A = 16000000 / frequency;
    OCR3AH = OCR3A >> 8;
    OCR3AL = OCR3A;
    OCR3CH = OCR3AH >> 1;
    OCR3CL = OCR3AL >> 1;
}
