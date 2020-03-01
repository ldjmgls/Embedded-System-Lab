#include "mbed.h"

Timeout tout;
DigitalIn button(SW2);
DigitalOut redLED(LED1);

void blink(){
    redLED = 0;
    wait(0.5);
    redLED = 1;
}

int main(){
    for( redLED=1; ; ){
        if(button==0){  // button pressed
            tout.attach( &blink, 2.0);
            // Attach a function to be called, specifying the interval in seconds
            // pointer to the function to be called
            // time between calls in seconds
        }
        wait(0.2);
    }
} 

/*#include "mbed.h"
 
Timeout flipper;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
 
void flip() {
    led2 = !led2;
}
 
int main() {
    led2 = 1;
    flipper.attach(&flip, 2.0); // setup flipper to call flip after 2 seconds
 
    // spin in a main loop. flipper will interrupt it to call flip
    while(1) {
        led1 = !led1;
        wait(0.2);
    }
} */