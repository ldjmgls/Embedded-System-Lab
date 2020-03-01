// Ticker: calls a function repeatedly and at a specified rate
// This program switches the LED every 500 ms
#include "mbed.h"

Ticker time_up;
DigitalOut redLED(LED1);

void blink(){
    redLED = !redLED;
}

int main(){
    time_up.attach( &blink, 0.5 );
    while(1);
}