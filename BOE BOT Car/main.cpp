#include "mbed.h"
#include "bbcar.h"

DigitalOut led1(LED1);
PwmOut pin9(D9), pin8(D8);
DigitalInOut pin10(D10);
Ticker servo_ticker;

BBCar car(pin8, pin9, servo_ticker);
int flag = 0;

int main() {

    parallax_ping  ping1(pin10);

    led1 = 1;   // led off
    car.turn(30, 0.2); // turn left 90 degrees
    wait(3.5);
    car.stop();
    wait(0.5);
    car.goStraight(200);
    wait(1.2);
    car.turn(30, -0.2);  // turn right 90 degrees
    wait(3.8);  
    car.stop();
    wait(0.25);

    while(1){

        if((float)ping1>90) {
            flag++;
            car.goStraight(-60);
            wait(1);
            car.stop();
            wait(0.25);
		    car.turn(30, 0.2); // turn left 90 degrees
    		wait(3.45);
    		car.stop();
    		wait(0.5);
    		car.goStraight(200);
    		wait(1.05);
    		car.turn(30, -0.2);  // turn right 90 degrees
    		wait(3.57);    
    		car.stop();
    		wait(0.3);     
        }          
        
        else{
            while ((float)ping1>=20) {
                car.goStraight(150);
                wait(0.5);
            }
            // find obstacle
            car.goStraight(-25);
            wait(1.2);             
            car.stop();
            wait(0.25);
            led1 = 0;   // led on
            wait(0.5);
            led1 = 1;           
            car.turn(30, 0.2);  // turn left 90 degrees
            wait(3.2);
            car.stop();
            wait(0.25);
            car.goStraight(70);
            wait(1);
            // start circling
            car.turn(30, -0.2);  // turn right 90 degrees
            wait(3.8);
            car.stop();
            wait(0.25);
            car.goStraight(200);
            wait(2.15);
            car.turn(30, -0.2);  // turn right 90 degrees
            wait(3.5);
            car.stop();
            wait(0.25);
            car.goStraight(200);
            wait(1.8);
            car.turn(30, -0.2);  // turn right 90 degrees
            wait(3.47);
            car.stop();
            wait(0.25);
            car.goStraight(200);
            wait(2.13);                       

            if(flag==0) {
                car.turn(30, -0.2);  // turn right 90 degrees
                wait(3.5); 
                car.stop();
                wait(0.25);                         
                led1 = 0;   // finish circling
                wait(1);
                led1 = 1;
                car.goStraight(80);
                wait(1); 
                car.turn(30, 0.2);  // turn left 90 degrees
                wait(3.5);           
            }

            car.stop();
            wait(0.25);  
            led1 = 0;   // finish circling
            wait(0.5);
            led1 = 1;
            
            while ((float)ping1>=30) {
                car.goStraight(200);
                wait(0.5);
            }

            car.stop();  // last step
            wait(0.25);
            car.turn(30, 0.2);  // turn left 90 degrees
            wait(3.2);
            car.stop();
            wait(0.25);

            while ((float)ping1>=27) {
                car.goStraight(100);
                wait(0.5);
            }
            car.turn(30, -0.2);  // turn right 90 degrees
            wait(3.8);
            car.stop();
            led1 = 0;   // finish, led on
            break;   
        }
        wait(0.5);
    }
}
