#ifndef BBCAR_H
#define BBCAR_H
#include "parallax_servo.h"
#include "parallax_encoder.h"
#include "parallax_ping.h"

class BBCar{
	public:
		BBCar( PwmOut &pin_servo0, PwmOut &pin_servo1, Ticker &servo_ticker );

		parallax_servo servo0;
		parallax_servo servo1;

		void controlWheel();
		void stop();
		void goStraight( int speed );
		void turn( int speed, double turn );
		void controller( float err );
		void setController( float kp, float ki );

		//Range limit the output
		float clamp( float value, float max, float min );
		int turn2speed( float turn );
};

#endif
