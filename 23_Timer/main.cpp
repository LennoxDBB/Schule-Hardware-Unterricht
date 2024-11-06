#include "mbed.h"
#include "LCD.h"

void initTimer();
bool isOneMinute(int seconds);
bool isOneHour(int minutes);
string getFinalTimeString(int hours, int minutes, int seconds);

DigitalOut led(PC_0);
lcd mylcd;

int seconds;
int minutes;
int hours;

int main()
{
    initTimer();

    seconds = 0;
    minutes = 0;
    hours = 0;

    mylcd.cursorpos(0);

    while(true) {

        if(TIM6 -> SR != 0) {
            TIM6 -> SR = 0;

            mylcd.clear();
            seconds++;

            if(isOneHour(minutes)) {
                minutes = 0;
                hours++;
            }

            if(isOneMinute(seconds)) {
                seconds = 0;
                minutes++;
            }

            mylcd.printf("%d", minutes);
            mylcd.printf(":");
            mylcd.printf("%d", seconds);
        }
    }
}



string getFinalTimeString(int hours, int minutes, int seconds) {
    string finalHours = "";
    string finalMinutes = "";
    string finalSeconds = "";

    if(hours < 10) finalHours = finalHours + 0;
    if(minutes < 10) finalMinutes = finalMinutes + 0;
    if(seconds < 10) finalSeconds = finalSeconds + 0;

    finalHours = finalHours + hours;
    finalMinutes = finalMinutes + minutes;
    finalSeconds = finalSeconds + seconds;
    
    string finalString = finalHours + ":" + finalMinutes + ":" + finalSeconds;

    return finalString;
}

bool isOneMinute(int seconds) {
    if(seconds == 60) {
        return true;
    }

    return false;
}

bool isOneHour(int minutes) {
    if(minutes == 60) {
        return true;
    }

    return false;
}

void initTimer() {
    RCC -> APB1ENR |= 0b10000;
    TIM6 -> PSC = 31999;
    TIM6 -> ARR = 999;
    TIM6 -> CNT = 0;
    TIM6 -> SR = 0;
    TIM6 -> CR1 = 1;
}
