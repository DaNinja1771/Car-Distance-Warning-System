#include "lcd_i2c.h"

LCD_I2C::LCD_I2C(uint8_t lcd_addr){
    address = lcd_addr;                 //address of lcd screen
    cols = 20;                          //number of columns
    rows = 4;                           //number of rows 
    backlight_val = LCD_NOBACKLIGHT;    //initialize backlight to off
    
}

void LCD_I2C::init(){
    i2c_init();

    display_function = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;      //display_function hold the values of what type of lcd screen we want to initialize
    display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF; //display_control holds the values of how we want the board to look initialized
    display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;         //display_mode holds the values of the direction of text

    delay_ms(50);

    transmit(LCD_NOBACKLIGHT);

    delay_ms(1000);

    transmit(0x03 << 4);
	delay_ms(45); 

	write4bits(0x03 << 4);
	delay_ms(45);

	write4bits(0x03 << 4);
	delay_ms(2);

	write4bits(0x02 << 4);

    command(LCD_FUNCTIONSET | display_function);

	display_on();

	clear();

	command(LCD_ENTRYMODESET | display_mode);

	home();

}

//overload print function to account for string, floats and unsigned ints
void LCD_I2C::print(const char* data){
    
    for(int i = 0; data[i] != '\0'; i++){
        send(data[i], Rs);
    }
}

void LCD_I2C::print(double data){

    char data_s[50];

    dtostrf(data, 3, 2, data_s);

    print(data_s);

}

void LCD_I2C::print(unsigned int data){

    char data_s[100];

    utoa(data, data_s, 100);

    print(data_s);

}

void LCD_I2C::clear(){
	command(LCD_CLEARDISPLAY);
	delay_ms(2); 
    set_cursor(0, 0);
}

void LCD_I2C::home(){
	command(LCD_RETURNHOME);  
	delay_ms(2); 
}

void LCD_I2C::set_cursor(uint8_t row, uint8_t col){
	uint8_t row_offsets[4] = { 0x00, 0x40, 0x14, 0x54 };
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_I2C::backlight_on(void) {
	backlight_val=LCD_BACKLIGHT;
}

void LCD_I2C::backlight_off(void) {
	backlight_val=LCD_NOBACKLIGHT;
}

void LCD_I2C::display_on() {
	display_control |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | display_control);
}

void LCD_I2C::display_off() {
	display_control &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | display_control);
}

void LCD_I2C::cursor_on() {
	display_control |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | display_control);
}

void LCD_I2C::cursor_off() {
	display_control &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | display_control);
}

void LCD_I2C::blink_on() {
	display_control |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | display_control);
}

void LCD_I2C::blink_off() {
	display_control &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | display_control);
}

/////////////////////////////////////////////////////////////////////
void LCD_I2C::command(uint8_t command){
    send(command, 0);
}

void LCD_I2C::send(uint8_t data, uint8_t mode){
    uint8_t hb = data & 0xF0;
    uint8_t lb = (data<<4) & 0xF0;
    write4bits(hb | mode);//mode is either high or low
    write4bits(lb | mode);
}

void LCD_I2C::write4bits(uint8_t data){
    transmit(data);
    pulseEN(data);
}

/*
Pulse the enable pin to send data to lcd
*/
void LCD_I2C::pulseEN(uint8_t data){
    transmit(data | En);
    delay_us(1);

    transmit(data & ~En);
    delay_us(30);
}
/*
sends data to the lcd with i2c
*/
void LCD_I2C::transmit(uint8_t value){

    i2c_send_byte(address, value | backlight_val);

}