#include "mbed.h"
#include "uLCD_4DGL.h"

Serial pc( USBTX, USBRX );
uLCD_4DGL uLCD(D1, D0, D2);
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
DigitalIn Din(D3);

float f = 25.0, t; // frequency, =1/f, time
int sample = 100;
float AnaData, DiData;
float thre = 0.5;
float Vmax, Vmin;
float sin_p, freq, p_p_amp;
int high, low;

int main(){
    for( t=0; t<0.04*f; t+=0.04/sample*f ){ // genaerate 25 sine waves within 1s
        Aout=0.5+0.5*sin(2*3.14159*f*t);
        wait(1./sample);
        AnaData=Ain;
        DiData=Din.read();

        pc.printf("%1.3f\r\n", AnaData);
        pc.printf("%1.3f\r\n", DiData);
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

    sin_p = (1./sample)*(high+low)/25;       // period, also = samp_time*(2/0.05)
    freq = 1/sin_p;
    p_p_amp = 3.3*(Vmax-Vmin);

    uLCD.printf("Amplitude=%.3fV", p_p_amp);
    uLCD.locate(0,1);  
    uLCD.printf("Frequency=%.3fHz", freq);  
}