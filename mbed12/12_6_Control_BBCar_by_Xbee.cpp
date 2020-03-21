#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
Serial pc(USBTX, USBRX);
BBCar car(pin8, pin9, servo_ticker);

int main() {

    int i;
    char buf[256], outbuf[256];
    
    while (1) {
        for( int i=0; ;i++ ) {
            buf[i] = xbee.getc();
            if(buf[i] == '\n') break;
        }
        pc.printf("Get: %s\r\n", buf);
        wait(0.1);

        RPC::call(buf, outbuf);
        pc.printf("out: %s\r\n", outbuf);
        xbee.printf("%s\r\n", outbuf);
        wait(0.1);

        i = 0;
        while(buf[i] != '\0'){
            buf[i] = 0;
            i++;
        }
    }
}