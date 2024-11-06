/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define MASK 0xFF

void anzeigen(PortOut seg7, char bytes[], int anzahl) {
    seg7 = bytes[anzahl];
    return;
}

int main()
{
    char bytes[10] {
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

    DigitalIn eingang(PA_1);
    eingang.mode(PullDown);

    DigitalIn ausgang(PA_6);
    ausgang.mode(PullDown);

    /*  Zusatz: Wunsch von Simon
    *   Wenn das Parkhaus schließt werden alle Autos, die noch
    *   im Parkhaus sind, abgeschleppt.
    */

    DigitalIn reset(PA_10);
    reset.mode(PullDown);

    PortOut seg7(PortC, MASK);

    DigitalOut einerstelle(PC_11);
    einerstelle = 1;

    seg7 = bytes[9];

    int anzahl = 9;

    while(true) {
        if(eingang == true) {
            if(anzahl <= 0) continue;
            anzahl--;
            anzeigen(seg7, bytes, anzahl);
            while(eingang) {}
        }

        if(ausgang == true) {
            if(anzahl >= 9) continue;
            anzahl++;
            anzeigen(seg7, bytes, anzahl);
            while(ausgang) {}
        }

        if(reset == true) {
            anzahl = 9;
            anzeigen(seg7, bytes, anzahl);
            while(reset){}
        }
    }

}