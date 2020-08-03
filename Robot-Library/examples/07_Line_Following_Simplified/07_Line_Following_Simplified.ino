#include "SimpleRSLK.h"

#define LEFT_BTN        74
/*
 * Robot QTR Sensor Example
 * 
 * This example will demonstrate the various features of the QTR Line Sensor library.
 * by Franklin S. Cooper Jr.
 */

void waitBtnPressed() {
  while(digitalRead(LEFT_BTN) == 1);
}

void setup()
{
	Serial.begin(115200);
	delay(500);

	setupRSLK();

	Serial.println("Push left button to start"); 
	pinMode(LEFT_BTN, INPUT_PULLUP);
	waitBtnPressed();
	delay(4000);
	Serial.println("Running calibration");
	simpleCalibrate();

	Serial.println("Calibration complete");
	waitBtnPressed();
	Serial.println("Printing calibration data");
	printLineSensorCal();
	Serial.println("Push left button to begin line following");
	waitBtnPressed();
	delay(4000);
	enableMotor(BOTH_MOTORS);
}

void simpleCalibrate() {
	int16_t count;
	Serial.println("Driver robot forward to calibrate sensors");

	setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

	setMotorSpeed(BOTH_MOTORS,10);
	enableMotor(BOTH_MOTORS);

	count = getEncoderLeftCnt();
	while(getEncoderLeftCnt() < count + 200) {
		calLineSensor();
	}
  setMotorSpeed(BOTH_MOTORS,0);
  delay(1000);
  setMotorSpeed(BOTH_MOTORS,10);
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_BACKWARD);

  Serial.println("Driver robot forward to calibrate sensors");
  count = getEncoderLeftCnt();
  while(getEncoderLeftCnt() < count + 200) {
    calLineSensor();
  }  

	setMotorSpeed(BOTH_MOTORS,0);
	disableMotor(BOTH_MOTORS);
	setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
}

void loop()
{
	unsigned int sensor[NUM_SENSORS];
	getLineSensorCalValue(sensor);

	float leftValues = (0.0 + sensor[7]+sensor[6]+sensor[5])/3.0;
	float centralValues = (0.0 + sensor[3]+sensor[4])/2.0;
	float rightValues = (0.0 + sensor[0]+sensor[1]+sensor[2])/3.0;

	if(leftValues > centralValues && leftValues > rightValues && leftValues > 200) {
		/* Spin the robot counter clock wise */
		setMotorDirection(LEFT_MOTOR,MOTOR_DIR_BACKWARD);
		setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_FORWARD);

		setMotorSpeed(BOTH_MOTORS,10);

	} else if(rightValues > leftValues && rightValues > centralValues && rightValues > 200) {
		/* Spin the robot clock wise */
		setMotorDirection(LEFT_MOTOR,MOTOR_DIR_FORWARD);
		setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);

		setMotorSpeed(BOTH_MOTORS,10);
	}
	else {
		/* Drive forward */
		setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
		setMotorSpeed(BOTH_MOTORS,10);
	}

	delay(100);
}
