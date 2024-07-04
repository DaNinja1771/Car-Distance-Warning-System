#include "main.h"
#include "lcd_i2c.h"
#include "i2c.h"
#include "timer.h"
#include "pwm.h"
#include "led.h"
#include "ultrasonic.h"

LCD_I2C lcd(0x3F);   //does not need to be global but incase we want to print from another file

int main(){

    pwm_init();
    delay_us(5);
    init_timer1();
    init_timer0();
    led_init();

    lcd.init();
    lcd.clear();
    lcd.backlight_on();
    lcd.home();
    lcd.set_cursor(0, 0);
    lcd.print("SETUP SUCCESS");
    delay_ms(10);
    lcd.clear();
    ULTRASONIC sensor(1);
    sei();

    float distance_ft = 0;

    int prev_safey = 0;
    int saftey = 3;
    int state_change = 0;

    while(1){

        delay_ms(5);

        distance_ft = sensor.get_distance();//gets distance in feet

        saftey = sensor.distance_check_ft(distance_ft);/*   based on distance, a raiting will be assigned to saftey from 0 to 3
                                                            0 means the person is 5 or more feet away from object
                                                            1 means the sensor is between 2 and 5 feet
                                                            2 means the sensor is 2 feet or closer
                                                        */
        state_change = saftey - prev_safey;             /*
                                                            To save on execution time we only want to print the state
                                                            message 1 time if the state has not changed, if the state
                                                            does change then we will reprint message
                                                        */

        //will not let me use math.h to do abs so this is fine.
        if((state_change < 0)){
            state_change *= -1;
        }
        if(state_change == 0){
            saftey = 10;
        }

        switch (saftey){

            case 0:
                //lcd.clear();
                lcd.set_cursor(0, 4);
                lcd.print(" ALL GOOD! ");//this is what is meant by state message
                lcd.set_cursor(1, 0);
                lcd.print("Distance: ");
                led_run(saftey);
                prev_safey = saftey;
                break;

            case 1:
                //lcd.clear();
                lcd.set_cursor(0, 4);
                lcd.print(" !WARNING! ");
                lcd.set_cursor(1, 0);
                lcd.print("Distance: ");
                led_run(saftey);
                prev_safey = saftey;
                break;

            case 2:
                //lcd.clear();
                lcd.set_cursor(0, 4);
                lcd.print("!EMERGENCY!");
                lcd.set_cursor(1, 0);
                lcd.print("Distance: ");
                led_run(saftey);
                prev_safey = saftey;
                break;

        }

        //displays distance constantly
        lcd.set_cursor(1, 10);
        lcd.print(distance_ft);                 //displays feet
        lcd.print(" ft ");
        lcd.set_cursor(2, 10);
        lcd.print((distance_ft*30.48)/100.0);   //displays meters
        lcd.print(" m  ");

    }

    return 0;
}
