#include "mbed.h"
#include "LCD.h"

#define PORT_MASK 0xFF
#define WAITING_TIME 250ms

InterruptIn button(PA_1);
PortOut pc(PortC, PORT_MASK);
lcd myLcd;

int score = 0;
int exponent = 0;
int direction = 1;

void buttonISR(void);
void writeScore();
void countExponentUp();

int main() {

    myLcd.clear();
    myLcd.printf("Druecke wenn");
    myLcd.cursorpos(64);
    myLcd.printf("PC_3 leuchtet");

    button.mode(PullDown);
    button.rise(&buttonISR);
    button.enable_irq();

    while(true) {
        if(pc == 0b01000000) {
            direction = -1;
        } else if(pc == 0b00000010) {
            direction = 1;
        }
        pc = pow(2, exponent);
        countExponentUp();
        ThisThread::sleep_for(WAITING_TIME);
    }

}

void buttonISR(void) {
    if(pc == pow(2, 3)) {
        if(score >= pow(2, 31)) return;
        score = score + 1; 
    } else {
        if(score <= 0) return;
        score = score - 1;
    }

    writeScore();
}

void writeScore() {
    myLcd.clear();
    myLcd.cursorpos(0);
    myLcd.printf("%d", score);
}

void countExponentUp() {
    exponent = exponent + direction;
}
