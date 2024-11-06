/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int seg7[10] = {0b00111111,
                0b00000110,
                0b01011011,
                0b01001111,
                0b01100110,
                0b01101101,
                0b01111101,
                0b00000111,
                0b01111111,
                0b01101111};

AnalogIn poti(PA_0);

int number = 0;

void getIntegerNumber(float voltage);
void setNumbers(int first, int second);

int main()
{
    while(true) {
        number = getIntegerNumber(poti);
    }
}

int getIntegerNumber(float voltage) {
    return voltage * 10;
}