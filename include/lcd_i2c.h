#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "main.h"
#include "i2c.h"
#include "timer.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00

#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit

class LCD_I2C{

    private:
        uint8_t address;
        uint8_t cols;
        uint8_t rows;
        uint8_t display_function;
        uint8_t backlight_val;
        uint8_t display_control;
	    uint8_t display_mode;

    public:
        LCD_I2C(uint8_t lcd_addr);
        void init();
        void clear();
        void home();
        void set_cursor(uint8_t col, uint8_t row);
        void display_on();
        void display_off();
        void cursor_on();
        void cursor_off();
        void blink_on();
        void blink_off();
        void backlight_on();
        void backlight_off();
        ///////////////////////////////////
        void command(uint8_t command);
        void send(uint8_t data, uint8_t mode);
        void write4bits(uint8_t data);
        void pulseEN(uint8_t data);
        void print(const char* data);
        void print(double data);
        void print(unsigned int data);
        void transmit(uint8_t value);
};


extern LCD_I2C lcd;

#endif