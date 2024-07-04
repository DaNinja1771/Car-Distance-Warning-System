#include "ultrasonic.h"
#include "timer.h"

//used because this-> does not work with ISR functions
ULTRASONIC* ULTRASONIC::ULTRASONIC_ptr;

ULTRASONIC::ULTRASONIC(uint8_t nothing){
	ULTRASONIC_ptr = this;
	
	ECHO_DDR    &= ~(1 << ECHO_PIN);
	TRIGGER_DDR |=  (1 << TRIGGER_PIN);
	init_timer();
}

void ULTRASONIC::init_timer(){

    init_timer4();

    ULTRASONIC::us_per_tick = 4; // 16MHz / 64 = 250 000 counts/second => 1/250 000 = 4 
}

float ULTRASONIC::get_distance(void){
	return distance/30.48; //return feet
}

int ULTRASONIC::distance_check_ft(float distance_ft){
    
    //distance is in feet
    if((distance_ft <.002) && (distance_ft > -.002)){
        return 0;
    }
    if (distance_ft > 5.00){
        return 0;        
    }
    else if((distance_ft < 5.00) && (distance_ft > 2.00)){
        return 1;
    }
    else if(distance_ft < 2.00){
        return 2;
    }
    return 9;//does not matter. This was to make the compiler happy
}

ISR(TIMER4_COMPA_vect){
    TRIGGER_PORT |=  (1 << TRIGGER_PIN);
	delay_us(10);
	TRIGGER_PORT &= ~(1 << TRIGGER_PIN);
}

ISR(TIMER4_CAPT_vect){
    if(TCCR4B & (1<<ICES4)){        // On rising edge
        TCCR4B &= ~(1<<ICES4);      // Next time detect falling edge
        ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::rising_edge = ICR4;         // Save current count
    }
    else{                           // On falling edge
        TCCR4B |= (1<<ICES4);       // Next time detect rising edge
        ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::falling_edge = ICR4;        // Save current count
        //distance = ((# of ticks between rising and falling edge) * the time taken per tick)/ (1/distance per microsecond)) (58 for cm) (148 for in) 
        ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::distance = (((unsigned int)ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::falling_edge - (unsigned int)ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::rising_edge) * ULTRASONIC::ULTRASONIC_ptr->ULTRASONIC::us_per_tick ) / 58;
	    TCNT4 = 0;
    }
}
