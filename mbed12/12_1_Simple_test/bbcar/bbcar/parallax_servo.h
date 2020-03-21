#ifndef PARALLAX_SERVO_H
#define PARALLAX_SERVO_H
#include "mbed.h"

#define CENTER_BASE 1500

class parallax_servo {
    public:
        parallax_servo(PwmOut& pin);

        void set_speed( int value ){ speed = value; }
        void set_factor( double value ){ factor = value; }
        void control();

    private:
        PwmOut *pwm;
        double factor;
        int speed;
};

#endif
