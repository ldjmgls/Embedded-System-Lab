#include "mbed.h"

AnalogOut Aout(DAC0_OUT);
DigitalIn Din(D2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[20] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                  0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF };
                  // 0~9, 0.~9.
float samp_time= 0.001;
float i;
float sin_p, freq;
int high;
int low;
int ten, one, dec1, dec2;
// 2/0.05=40, 40*0.001=0.04, 1/0.04=25

int main(){
    while(1){
        high = 0;
        low = 0;
        for( i=0; i<2; i+=0.05 ){           // generate sine wave
            Aout = 0.5 + 0.5*sin(i*3.14159);
            wait(samp_time);
            if (Din.read()) high++;
            else low++;
        }

        sin_p = samp_time*(high+low);       // period, also = samp_time*(2/0.05)
        freq = 1/sin_p;

        ten = freq/10;                      // displaying freq
        display = table[ten];
        wait(1);
        one = freq-ten*10;
        display = table[one+10];
        wait(1);
        dec1 = freq*10-(ten*100+one*10);
        display = table[dec1];
        wait(1);
        dec2 = freq*100-(ten*1000+one*100+dec1*10);
        display = table[dec2];
        wait(1);
    }
}