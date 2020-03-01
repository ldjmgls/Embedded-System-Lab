#include "mbed.h"
Timer t;
Serial pc( USBTX, USBRX );

int main(){
    t.start();  // Start the timer
    pc.printf("Hello from the other side\n");
    t.stop();   // Stop the timer
    pc.printf("The time taken was %f seconds\n", t.read());
                // read(): Get the time passed in milliseconds
}