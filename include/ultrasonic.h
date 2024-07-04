#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "main.h"
#include "timer.h"

#define TRIGGER_DDR		DDRC
#define ECHO_DDR		DDRL
#define TRIGGER_PIN		PINC4
#define ECHO_PIN		PINL0
#define TRIGGER_PORT	PORTC

class ULTRASONIC{

	private:
		
	public:
        ULTRASONIC(uint8_t nothing);                    //the nothing variable does nothing, the compiler was not having it if nothing was there
		float           get_distance(void);
        void            init_timer(void);
        int             distance_check_ft(float distance_ft);

        static ULTRASONIC*      ULTRASONIC_ptr;

        volatile unsigned int   rising_edge;
		volatile unsigned int   falling_edge;
		volatile unsigned int   distance;
		unsigned char           us_per_tick;
};

#endif