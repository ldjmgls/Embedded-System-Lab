#include "mbed.h"

#define CENTER_BASE 1500

PwmOut servo(D9);

void servo_control(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;

    servo = (CENTER_BASE + speed)/20000.0f;
}

int main() {
    servo.period(.02);

    while(1) {
        wait(2);
        servo_control(0);       
        /*servo_control(100);
        wait(2);
        servo_control(-100);
        wait(2);*/
    }
}