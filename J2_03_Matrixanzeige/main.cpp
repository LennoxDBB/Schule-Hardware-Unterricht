#include "mbed.h"

PortOut rows(PortC, 0xFF);
PortOut columns(PortB, 0xFF);
Ticker ticker;

int muster[8] = {0xFF, 0xC3, 0xA5, 0x99, 0x99, 0xA5, 0xC3, 0xFF};
int index = 0;

void display();

int main()
{
    ticker.attach(&display, 0.001);
    while(true) {}
}

void display() {
    columns = 1 << index;
    rows = ~muster[index];
    index = (index + 1) % 8;
}
