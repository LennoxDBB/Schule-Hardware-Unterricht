/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define MASK 0b11111111
#define START_VALUE 0b00000001
#define WAITING_TIME 500ms

int main()
{
    PortOut pc(PortC, MASK);
    pc = START_VALUE;

    while(true) {
       pc = pc << 1;
       ThisThread::sleep_for(WAITING_TIME);
       if(pc == 0b10000000) {
           pc = START_VALUE;
           ThisThread::sleep_for(WAITING_TIME);
       }

    }

}
