#ifndef I2C_H
#define I2C_H

#include "main.h"

#define wait_for_completion while( !(TWCR & (1<<TWINT)) )

#define DEFAULT_FREQ_I2C 200000UL
#define I2C_WRITE 0x00
#define I2C_READ 0x01

void i2c_init();
void i2c_start(uint8_t address, uint8_t mode);
void i2c_stop();
void i2c_write(uint8_t data);
void i2c_send_byte(uint8_t address, uint8_t data);

#endif