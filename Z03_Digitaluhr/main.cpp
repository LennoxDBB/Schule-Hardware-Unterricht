#include "mbed.h"
#include "LCD.h"

#define Anzeigen 0
#define Stunde_einstellen 1
#define Minute_einstellen 2
#define Sekunde_einstellen 3

lcd mylcd;

InterruptIn MODE(PA_1);
InterruptIn TV(PA_6);
InterruptIn TR(PA_10);

int zustand = Anzeigen;

int hours = 0;
int minutes = 0;
int seconds = 0;

void init();
void anzeigen();
void zeittakt();
void mode();
void tv();
void tr();

int main() {
    init();

    while(true) {
        switch(zustand) {
        case Anzeigen:
        case Stunde_einstellen:
        case Minute_einstellen:
        case Sekunde_einstellen:
            anzeigen();
            break;
        }
    }
}

void init() {
    RCC -> APB1ENR |= 0b10000;
    TIM6 -> PSC = 31999;
    TIM6 -> ARR = 1000;
    TIM6 -> SR = 0;
    TIM6 -> CR1 = 1;
    TIM6 -> DIER = 1;
    NVIC_SetVector(TIM6_IRQn, (uint32_t) &zeittakt);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);

    MODE.mode(PullDown);
    TV.mode(PullDown);
    TR.mode(PullDown);
    MODE.rise(&mode);
    TV.rise(&tv);
    TR.rise(&tr);

    mylcd.clear();
    mylcd.cursorpos(0);
}

void anzeigen() {    
    mylcd.cursorpos(0);

    if(hours < 10) mylcd.cursorpos(1);

    mylcd.printf("%d:", hours);
    mylcd.cursorpos(3);

    if(minutes < 10) mylcd.cursorpos(4);

    mylcd.printf("%d:", minutes);
    mylcd.cursorpos(6);

    if(seconds < 10) mylcd.cursorpos(7);

    mylcd.printf("%d", seconds);
}

void zeittakt() {
    seconds++;

    if(seconds >= 60) {
        seconds = seconds - 60;
        minutes++;
    }

    if(minutes >= 60) {
        minutes = minutes - 60;
        hours++;
    }

    if(hours >= 24) {
        hours = hours - 24;
    }

    TIM6 -> SR = 0;
    HAL_NVIC_ClearPendingIRQ(TIM6_IRQn);
}

void mode() {
    switch(zustand) {
    case Anzeigen:
        zustand = Stunde_einstellen;
        break;
    case Stunde_einstellen:
        zustand = Minute_einstellen;
        break; 
    case Minute_einstellen:
        zustand = Sekunde_einstellen;
        break;
    }
}

void tv() {
    switch(zustand) {
    case Stunde_einstellen:
        hours = hours + 1;
        if(hours >= 24) hours = hours - 24;
        break;
    case Minute_einstellen:
        minutes = minutes + 1;
        if(minutes >= 60) minutes = minutes - 60;
        break;
    case Sekunde_einstellen:
        zustand = Anzeigen;
        break;
    }
}

void tr() {
    switch(zustand) {
    case Stunde_einstellen:
        hours = hours - 1;
        if(hours <= -1) hours = hours + 24;
        break;
    case Minute_einstellen:
        minutes = minutes - 1;
        if(minutes <= -1) minutes = minutes + 60;
        break;
    }
}