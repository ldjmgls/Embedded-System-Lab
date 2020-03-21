#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin8(D8), pin9(D9);
DigitalIn pin3(D4);

BBCar car(pin8, pin9, servo_ticker);

int main() {
    parallax_encoder encoder0(pin3);
    encoder_ticker.attach(callback(&encoder0, &parallax_encoder::encoder_control), .01);
    encoder0.reset();

    car.goStraight(100);
    while(encoder0.get_cm()<30) wait_ms(50);
    car.stop();
}