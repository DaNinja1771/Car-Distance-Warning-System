#include "timer.h"
/*
Used for delay_ms()
ctc mode
*/
void init_timer0(){

    TCCR0A &= ~(1 << WGM00);
    TCCR0A |=  (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);
}

/*
Used for delay_us()
ctc mode
*/
void init_timer1(){

    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |=  (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
    
}
/*
Used for ultrasonic sensor
ctc mode
*/
void init_timer4(){

    //ctc mode
    TCCR4A &= ~(1 << WGM40);
    TCCR4A &= ~(1 << WGM41);
    TCCR4B |=  (1 << WGM42);
    TCCR4B &= ~(1 << WGM43);

    // prescaler 64
    TCCR4B |=  (1 << CS40); 
    TCCR4B |=  (1 << CS41); 
    TCCR4B &= ~(1 << CS42); 

    //Input Capture Noise Canceler
    TCCR4B |=  (1 << ICNC4);  

    // Input capture on rising edge
    TCCR4B |= 1 << ICES4; 


    TIMSK4 |= (1 << OCIE4A);
    TIMSK4 |= (1 << ICIE4);

    //16000000/64 = 250000 counts per second. 250000/10 = 250, just want to be over 60ms to get better sample rates
    OCR4A = 17500;

}

/* 
This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delay_us(unsigned int delay){

    unsigned int delayCount = 0;

    //pre-scaler 8
    TCCR1B &= ~(1 << CS10);
    TCCR1B |=  (1 << CS11);
    TCCR1B &= ~(1 << CS12);

    OCR1AH = 0;
    OCR1AL = 1;

    TCNT1 = 0;              //Starts timer at 0
    TIFR1 |= (1 << OCF1A);  //set compare flag to start the timer

    while (delayCount < delay){

        if(TIFR1 & (1 << OCF1A)){   //increment only while flag is set
            delayCount++;
            TIFR1 |= (1 << OCF1A);  //restart timer. Will go to 0 before reaching if statement
        }
    }
}

void delay_ms(unsigned int delay){
    unsigned int count = 0;

    //pre-scaler 64
    TCCR0B |= (1 << CS00);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS02);

    TCNT0 = 0;

    OCR0A = 249;//((1 * 16000)/64) - 1;

    TIFR0 |= (1 << OCF0A);

    while(count < delay){
        if(TIFR0 & (1 << OCF0A)){
            count++;
            TIFR0 |= (1 << OCF0A);
        }
    }
}
