#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
float samp_time= 0.001;
float f = 25.0, t; // frequency, =1/f, time
float thre = 0.5;
float Vmax, Vmin;
float sin_p, freq, p_p_amp;
int high, low;

int main(){
    while(1){
        high=0;
        low=0;
        Vmax = 0.5;
        Vmin = 0.5;
        for( t=0; t<0.04; t+=0.001 ){           // generate sine wave
            Aout=sin(2*3.14159*f*t);
            wait(samp_time);
            if (Ain>=thre) {
                high++;
                if (Ain>=Vmax) Vmax=Ain;
                else Vmax=Vmax;
            } 
            else {
                low++;
                if (Ain<=Vmin) Vmin=Ain;
                else Vmin=Vmin;
            }
        }
        sin_p = samp_time*(high+low);       // period, also = samp_time*(2/0.05)
        freq = 1/sin_p;
        p_p_amp = 3.3*(Vmax-Vmin);

        uLCD.printf("Amplitude=%.3fV\n", p_p_amp);
        uLCD.printf("Frequency=%.3fHz\n", freq);
        uLCD.locate(0,0);      
    }
}