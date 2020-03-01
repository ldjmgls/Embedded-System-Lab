#include "mbed.h"

DigitalIn  Dpin(D2);
PwmOut PWM1(D3);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);  
// K66F pins that connected to 7-seg in the order of A~G, dp
char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xBF};
// HEX for common cathode(陰), 0~9, 0. 
int high, low;
float ratio;
int dec1;

int main() {
    while (1) {
        PWM1.period(1);  // period=1s
        PWM1 = 0.5;      // =PWM1.write(), duty cycle=70%
        low = 0;
        high =0;
        while (Dpin.read()==0);  // make sure the signal is a
        while (Dpin.read());     // complete period
        while (Dpin.read()==0) low++;  // 1-->0, correctly count all 0s
        while (Dpin.read()) high++;    // 0-->1, all 1s
        ratio = (float) high/(high+low);
        
        display = table[10];
        wait(0.7);
        dec1 = ratio*10;
        display = table[dec1];
        wait(0.7);
        display = table[int (ratio*100-dec1*10)];
        wait(0.7);
    }
}