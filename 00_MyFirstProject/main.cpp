/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms


int main()
{
    
/*
* state = 0 (off)
* state = 1 (red)
* state = 2 (green)
* state = 3 (yellow)
* state = 4 (red & green)
* state = 5 (green & yellow)
* state = 6 (yellow & red)
*/

    DigitalOut redLed(PC_0);    
    DigitalOut greenLed(PC_1);  
    DigitalOut yellowLed(PC_2);

    int state = 1;
    int check = 0;

    while (true) {
        switch(state) {
        case 0:
            redLed = false;
            yellowLed = false;
            greenLed = false;
            state = check == 0 ? 0 : 4;
            break;
        case 1:
            redLed = true;
            check = 4;
            break;
        case 2:
            greenLed = true;
            break;
        case 3:
            yellowLed = true;
            state = 0;
            break;
        case 4:
            redLed = true;
            greenLed = true;
            check = 0;
            break;
        case 5:
            greenLed = true;
            yellowLed = true;
            break;
        case 6:
            yellowLed = true;
            redLed = true;
            break;
        }

        ThisThread::sleep_for(BLINKING_RATE);
        redLed = false;
        greenLed = false;
        yellowLed = false;
        state++;
    }
}
