# Car-Distance-Warning-System

This an AVR implementation of a car front warning sensor using the ATMega2560 Arduino microcontroller.
This was built using platform.io, the AVR framework, and C/C++.

## 5 main components of the system:
- ATMega2560 Arduino
- Piezo Active Buzzer
- Ultra Sonic Sensor
- Red, Yellow Green Indicator LEDs
- LCD

## Wiring Notes:
Ultrasonic Sensor:

- trig ------> pin 33
- echo ------> pin 49
- VCC  ------> 5V Rail
- GND  ------> Ground Rail

######################################################################
BUZZER:

- positive ------> pin 3
- ground   ------> Ground Rail

######################################################################
LEDS:

Red:    
- positive ------>  pin 24
- negative ------>  Ground Rail( with 220 ohm res.)
Yellow:
- positive ------>  pin 23
- negative ------>  Ground Rail( with 220 ohm res.)
Green:
- positive ------>  pin 22
- negative ------>  Ground Rail( with 220 ohm res.)

######################################################################
LCD:

- sda ------> sda(pin 20)
- scl ------> scl (pin 21)
- VCC ------> 5V Rail
- GND ------> Ground Rail
