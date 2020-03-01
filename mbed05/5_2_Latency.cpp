// Latency: 延遲
#include "mbed.h"

InterruptIn din(D3);
DigitalOut dout(D4);

void pulse(){
    dout = 1;
    wait(0.01);
    dout = 0;
}

int main(){
    din.rise(&pulse);
    while(1);
}