/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define MASK 0xFF

int main()
{
    char bytes[] {
        0b00111111,
        0b00000110,
        0b01011011,
        0b01001111,
        0b01100110,
        0b01101101,
        0b01111101,
        0b00000111,
        0b01111111,
        0b01101111
    };

    DigitalIn pa10(PA_10);
    pa10.mode(PullDown);

    PortOut pc(PortC, MASK);

    DigitalOut einerstelle(PC_11);
    einerstelle = 1;

    int count = 0;

    while(true) {
        pc = bytes[count];
        if(pa10) {
            count++;
            while(pa10){}
        }
        if(count > 9) count = 0;
    }
}
