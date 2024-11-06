/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int main()
{
   
    DigitalIn pb3(PB_4);

    DigitalOut pc1(PC_0);

    while(true) {
        if(pb3 == 0) {
            pc1 = true;
        }
        pc1 = false;
    }
}
