#include "parallax_servo.h"

parallax_servo::parallax_servo (PwmOut& pin) {
    pin.period(0.02);
    pwm = &pin;
    factor = 1;
    speed = 0;
}

void parallax_servo::control(){
    double value = factor * speed;

    if (value > 200) value = 200;
    else if (value < -200) value = -200;
    
    pwm->write((CENTER_BASE + value) / 20000);
}
