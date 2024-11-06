/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "LCD.h"

void initTimer6();

void leaveIsr();
void entranceIsr();
void isrTimer6();

void display(int amount);

int countTimer = 0;
int delay = 10;         //Minuten (Timer macht Interrupt jede Sekunde (*60))

int spaces = 200;
int vehiclesEntered = 0;

lcd mylcd;

InterruptIn entrance(PA_1);
InterruptIn leave(PA_6);

int main()
{
    display(spaces);

    entrance.mode(PullDown);
    entrance.rise(&entranceIsr);
    entrance.enable_irq();

    leave.mode(PullDown);
    leave.rise(&leaveIsr);
    leave.enable_irq();

    while(true) {
        if(countTimer == 10) {
            
        }
    }
}

void entranceIsr() {
    if(spaces <= 0) return; 
    
    spaces--;
    vehiclesEntered++;
    display(spaces);
}

void leaveIsr() {
    if(spaces >= 200) return;

    spaces++;
    display(spaces);
}

void display(int amount) {
    mylcd.clear();
    mylcd.cursorpos(0);
    mylcd.printf("%d", spaces);
}

void isrTimer6() {
    TIM6 -> SR = 0;
    HAL_NVIC_ClearPendingIRQ(TIM6_IRQn);

    countTimer++;

    if(countTimer == delay) {
        countTimer = 0;
    }
}

void initTimer6() {
    RCC -> APB1ENR |= 0b10000;
    TIM6 -> PSC = 31999;
    TIM6 -> ARR = 1000;
    TIM6 -> CNT = 0;
    TIM6 -> SR = 0;
    TIM6 -> CR1 = 1;

    TIM6 -> DIER = 1;
    NVIC_SetVector(TIM6_IRQn, (uint32_t) &isrTimer6);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
}
 
