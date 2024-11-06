#include "mbed.h"
#include <string>
#include "LCD.h"

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

int index = 0;
int number = 0;

int code[3] = {0, 0, 0};

DigitalOut einerstelle(PC_11);

DigitalOut lock(PC_7);
PortOut show(PortC, 0xFF);

lcd mylcd;

InterruptIn change(PA_1);
InterruptIn takt(PA_6);

void info();

void init();
void checkCode();

void taktISR();
void changeISR();

int main() {
    init();

    while(true) {
        if(einerstelle == 1) {
            show = seg7[index];
        }

    }
}

void init() {
    einerstelle = 1;
    mylcd.clear();
    mylcd.cursorpos(0);

    change.mode(PullDown);
    takt.mode(PullDown);

    change.rise(&changeISR);
    takt.rise(&taktISR);

    change.enable_irq();
    takt.enable_irq();
}

void checkCode() {
    if(code[0] == 3 && code[1] == 1 && code[2] == 7) {
        einerstelle = 0; 
        lock = 1;
        mylcd.clear();
        mylcd.cursorpos(0);
        mylcd.printf("Schloss offen");
    } else {
        number = 0;
        for(int i = 0; i < 3; i++) {
            code[i] = 0;
        }

        info();
    }
}

void taktISR() {
    if(einerstelle == 0) return;

    if(number < 2) {
        code[number] = index;
        number++;
        info();
    } else {
        code[number] = index;
        info();
        checkCode();
    }
}

void changeISR() {
    if(einerstelle == 0) return;

    index--;
    if(index == -1) index = 9;
}

void info() {
    mylcd.cursorpos(0);
    mylcd.printf("%d", code[0]);
    mylcd.printf("%d", code[1]);
    mylcd.printf("%d", code[2]);
    mylcd.cursorpos(number);
}