#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin8(D8), pin9(D9);

BBCar car(pin8, pin9, servo_ticker);

int main() {
    // please contruct you own calibration table with each servo
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150}; // D8
    double speed_table0[] = {-16.584, -16.265, -15.229, -12.199, -6.139, 0.000, 6.139, 12.199, 15.229, 16.265, 16.584};
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150}; // D9
    double speed_table1[] = {-16.823, -16.345, -15.149, -12.119, -4.146, 0.000, 4.146, 12.119, 15.149, 16.345, 16.823};

    // first and fourth argument : length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    while (1) {
        car.goStraightCalib(-5);
        wait(5);
        car.stop();
        wait(5);
    }
}