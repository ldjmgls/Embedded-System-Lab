#include "bbcar.h"

BBCar::BBCar( PwmOut &pin_servo0, PwmOut &pin_servo1, Ticker &servo_ticker ):servo0(pin_servo0), servo1(pin_servo1){
    servo0.set_speed(0);
    servo1.set_speed(0);
    servo_ticker.attach(callback(this, &BBCar::controlWheel), 0.5);
}

void BBCar::controlWheel(){
    servo0.control();
    servo1.control();
}

void BBCar::stop(){
    servo0.set_speed(0);
    servo1.set_speed(0);
    servo0.set_factor(1);
    servo1.set_factor(1);
}

void BBCar::goStraight( int speed ){
    servo0.set_speed(speed);
    servo1.set_speed(-speed);
}

void BBCar::turn( int speed, double direction ){
    static int last_speed = 0;
    if(last_speed!=speed){
        servo0.set_speed(speed);
        servo1.set_speed(-speed);
    }
    if(direction>0){
        servo0.set_factor(direction);
        servo1.set_factor(1);
    }
    if(direction<0){
        servo0.set_factor(1);
        servo1.set_factor(-direction);
    }
}

float global_kp, global_ki;
float BBCar::clamp( float value, float max, float min ){ return (max<value)?max:((min>value)?min:value); }
int BBCar::turn2speed( float turn ){ return 25+abs(25*turn); }
void BBCar::setController( float kp, float ki ){ global_kp = kp; global_ki = ki;}

void BBCar::controller( float err ){
    static float erri = 0;
    const float bound = .9;
    erri += err;
    float correction = err*global_kp + erri*global_ki;
    correction = clamp(correction, bound, -bound);
    printf("correction(%.2f,%.2f) = %3.2f (kp = %.2f, ki = %.2f)\r\n", err, erri, correction, global_kp, global_ki);
    float val = ((correction>0) ?1:(-1)) - correction;
    turn(turn2speed(val),val);
}




