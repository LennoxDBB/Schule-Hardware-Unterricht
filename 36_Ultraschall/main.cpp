#include "mbed.h"
#include "LCD.h"

void initTimer();

void echoISRRise();
void echoISRFall();

DigitalOut trigger(PA_10);
InterruptIn echo(PC_8);

lcd mylcd;

long microseconds = 0;
int away = 0;

int main()
{
    initTimer();

    mylcd.clear();
    mylcd.cursorpos(0);

    echo.mode(PullDown);
    echo.rise(&echoISRRise);
    echo.fall(&echoISRFall);
    echo.enable_irq();

    while(true) {  

        trigger = 1;
        TIM6 -> CNT = 0;
        while(TIM6 -> CNT < 10);
        trigger = 0;

        if(microseconds != 0) {
            away = microseconds / 58;
        }


        if(TIM6 -> SR) {
            mylcd.clear();
            mylcd.printf("%d", away);
            TIM6 -> SR = 0
        }
    }

}

void echoISRRise() {
    TIM6 -> CNT = 0;
}

void echoISRFall() {
    microseconds = TIM6 -> CNT;
}

void initTimer() {
    RCC -> APB1ENR |= 0b10000;
    TIM6 -> PSC = 31;
    TIM6 -> ARR = 0xFFFF;
    TIM6 -> CNT = 0;
    TIM6 -> SR = 0;
    TIM6 -> CR1 = 1;
}
