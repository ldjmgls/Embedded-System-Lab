#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
 */

//Use the RPC enabled wrapped class  - see RpcClasses.h for more info
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
Serial pc(USBTX, USBRX);
char no;

int blink(char i) {
    myled1.write(1);
    myled2.write(1);
    myled3.write(1);
    
    while (i=='1') {
        myled1.write(1);
        wait (0.2);
        myled1.write(0);
        wait (0.2);
    }
    while (i=='2') {
        myled2.write(1);
        wait (0.2);
        myled2.write(0);
        wait (0.2);
    }
    while (i=='3') {
        myled3.write(1);
        wait (0.2);
        myled3.write(0);
        wait (0.2);
    }

}

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class

    // receive commands, and send back the responses
    char buf[256], outbuf[256];
    while(1) {
        memset(buf, 0, 256);      // clear buffer

        for(int i=0; ; i++) {
            char recv = pc.getc();
            if ( recv == '\r' ) {
                pc.printf("\r\n");
                break;
            }
            buf[i] = pc.putc(recv);
        }
        //Call the static call method on the RPC class
        //RPC::call(buf, outbuf);
        //pc.printf("%s\r\n", outbuf);
        if (buf[8]=='b' && buf[9]=='l' && buf[10]=='i' && buf[11]=='n' && buf[12]=='k')
        {
            no=buf[6];
            blink(no);
        }    
    }
}