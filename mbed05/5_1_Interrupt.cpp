/* #include "mbed.h"
 
InterruptIn button(SW2);
DigitalOut led(LED1);   // red
DigitalOut flash(LED2); // green
 
void flip() {
    led = !led;
}
 
int main() {
    button.rise(&flip);  // attach the address of the flip function to the rising edge
    while(1) {           // wait around, interrupts will trigger this event!
        flash = !flash;
        wait(0.25);
    }
} */
#include "mbed.h"

//Ticker t;
Serial pc(USBTX, USBRX);
BusOut data(D0, D1, D2, D3, D4, D5, D6, D7);
char table[16] = {0x45, 0x45, 0x20, 0x4E, 0x54, 0x48, 0x55, 0x31, 0x30, 0x36, 0x30, 0x36, 0x31, 0x32, 0x32, 0x34};
DigitalOut dout(D8);
volatile int i = 0;

int main(){
    //dout = 0; 
    while(1) {
        dout = 0;
        wait(1);
        dout = 1;
        if (dout==1) {
            data = table[i];
            pc.printf("%c\r\n", table[i]);
            i++;
        }
        if (i==16) i=0;   
        //wait (0.5);
    }
}