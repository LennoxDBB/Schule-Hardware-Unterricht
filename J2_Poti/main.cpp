#include "mbed.h"
#include "LCD.h"

lcd myLcd;
AnalogIn poti(PA_0);
PortOut leds(PortC, 0xFF);

int led[] = {0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};

int main() {
    myLcd.clear();

    float voltage;
    int value;

    int index;

    while(true) {
        voltage = poti * 3.3;
        value = poti * 4095;
        index = poti * 8;

        leds = led[index];

        myLcd.cursorpos(0);
        myLcd.printf("Potiwert: %1.2f", voltage);
        myLcd.cursorpos(64);
        myLcd.printf("Wandelwert: %d", value);        
    }
}
