#ifndef Romi_Motor_Power_h
#define Romi_Motor_Power_h

#include "Energia.h"

class Romi_Motor_Power
{
    private:
    	uint8_t slp_pin;
    	uint8_t dir_pin;
    	uint8_t pwm_pin;
    	uint8_t motor_dir;
       	uint8_t sleep_speed;
    	uint8_t preserve_speed;

    public:
		Romi_Motor_Power();
		bool begin(uint8_t islp_pin, uint8_t idir_pin,uint8_t ipwm_pin);
		void disableMotor();
		void enableMotor();
		void pauseMotor();
		void resumeMotor();
		void directionForward();
		void directionBackward();
		bool setSpeed(uint8_t speed);
		bool setRawSpeed(uint8_t speed);
};

#endif


