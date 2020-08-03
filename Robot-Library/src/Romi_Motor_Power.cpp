#include "Romi_Motor_Power.h"


Romi_Motor_Power::Romi_Motor_Power()
{
    slp_pin = 0;
    dir_pin = 0;
    pwm_pin = 0;
    motor_dir = 0;
}

bool Romi_Motor_Power::begin(uint8_t _slp_pin, uint8_t _dir_pin,uint8_t _pwm_pin) {
    slp_pin = _slp_pin;
    dir_pin = _dir_pin;
    pwm_pin = _pwm_pin;

    pinMode(slp_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(pwm_pin, OUTPUT);

    disableMotor();
}

void Romi_Motor_Power::disableMotor() {
	// Workaround (Sleep pin isn't working for now)
	setRawSpeed(0);
    digitalWrite(slp_pin, LOW);
}

void Romi_Motor_Power::enableMotor() {
    digitalWrite(slp_pin, HIGH);
}

void Romi_Motor_Power::directionForward() {
    digitalWrite(dir_pin, LOW);
}

void Romi_Motor_Power::directionBackward() {
    digitalWrite(dir_pin, HIGH);
}

void Romi_Motor_Power::pauseMotor() {
    sleep_speed = preserve_speed;
    setRawSpeed(0);
    disableMotor();
}

void Romi_Motor_Power::resumeMotor() {
    preserve_speed = sleep_speed;
    setRawSpeed(preserve_speed);
    enableMotor();
}

bool Romi_Motor_Power::setSpeed(uint8_t speed) {
    speed = map(speed, 0, 100, 0, 255);
    analogWrite(pwm_pin, speed);
    return true;
}

bool Romi_Motor_Power::setRawSpeed(uint8_t speed) {
    analogWrite(pwm_pin, speed);
    return true;
}