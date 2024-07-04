#include "i2c.h"

void i2c_init(){

    PRR0 &= ~(1 << PRTWI);

	TWSR = 0;
	TWBR = (uint8_t)((((F_CPU / DEFAULT_FREQ_I2C)) - 16 ) / 2);
}

void i2c_start(uint8_t address, uint8_t mode){

	TWCR = 0;//reset TWCR
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);//send start trans

	wait_for_completion;

	TWDR = (address << 1) | mode;

	TWCR = (1<<TWINT) | (1<<TWEN);

	wait_for_completion;

}

//master writes the data to slave
void i2c_write(uint8_t data){
	
	TWDR = data;

	TWCR = (1<<TWINT) | (1<<TWEN);

	wait_for_completion;
	
}

//master sends 1 byte of data to slave
void i2c_send_byte(uint8_t address, uint8_t data){

    i2c_start(address, 0);
	
	i2c_write(data);

	i2c_stop();
	
}

void i2c_stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}