/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define WAITING_TIME 500ms

void ba1(PortOut pc) {
    pc = pc << 1;
    if(pc == 0) pc = 0b0001;
}

void ba2(PortOut pc) {
    pc = pc << 1;
    if(pc == 0b1000) {
        pc = 0b1001;
        ThisThread::sleep_for(WAITING_TIME);
    }
    if(pc == 0b1001) pc = 0b0011;
}

void ba3(PortOut pc) {
    pc = pc >> 1;
    if(pc == 0) pc = 0b1000;
    
}

int main()
{

    PortOut pc(PortC, 0b1111);
    
    DigitalIn pb0(PB_0);
    pb0.mode(PullDown);

    DigitalIn pb7(PB_7);
    pb7.mode(PullDown);

    pc = 0b0001;

    bool entry1 = true;
    bool entry2 = true;
    bool entry3 = true;

    while(true) {
       
        if(pb0 == 0 && pb7 == 0) {
            if(entry1) pc = 0b0001;
            entry1 = false;
            entry2 = true;
            entry3 = true;
            ba1(pc);
        } else if(pb7 == 0 && pb0 == 1) {
            if(entry2) pc = 0b0011;
            entry1 = true;
            entry2 = false;
            entry3 = true;
            ba2(pc);
        } else if(pb0 == 0 && pb7 == 1) {
            if(entry3) pc = 0b0001;
            entry1 = true;
            entry2 = true;
            entry3 = false;
            ba3(pc);
        } else {
            pc = 0b0000;
        }

        ThisThread::sleep_for(WAITING_TIME);

    }

}
