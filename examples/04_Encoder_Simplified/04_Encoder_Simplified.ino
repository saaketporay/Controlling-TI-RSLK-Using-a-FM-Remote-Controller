/* TI-RSLK MAX Example 4 */
/* Robot will drive forward until it hits an object with bump switches */

#include "Energia.h"

/* Defines functions of robot */
#include "SimpleRSLK.h"

/*
 * Robot Encoder Library Example
 * 
 * Summary:
 * This example will demonstrate the various features of the Encoder library.
 * The robot will go forward by a specified amount in inches. A robot natually
 * will not go straight due to factors such as wheel whooble or differences in
 * behavior of the left and right motor. Incorporting PID with the encoder count
 * could be used to improve this but in reality a compass should be used to help
 * the robot know exactly when its divating and how to correct itself.
 *
 * Parts Info:
 * o Romi Encoder Pair Kit, 12 CPR, 3.5-18V - https://www.pololu.com/product/3542
 * o Pololu Wheel 70×8mm Pair - https://www.pololu.com/product/1429
 *
 * created 5 Nov 2018
 * by Franklin S. Cooper Jr.
 */
 
/* Diameter of Romi wheels in inches */
#define WHEEL_DIAMETER 2.7559055

/* Number of encoder (rising) pulses every time the wheel turns completely */
#define CNT_PER_REVOLUTION 360

/* How far in inches for the robot to travel */
#define INCHES_TO_TRAVEL 6

/* Function that waits until a button on the LaunchPad is pressed */
void waitBtnPressed() {
	while(1) {
		if (digitalRead(LP_S1_PIN) == 0) break;
    		if (digitalRead(LP_S2_PIN) == 0) break;
		digitalWrite(LP_RGB_LED_GREEN_PIN, HIGH);
    		delay(500);
    		digitalWrite(LP_RGB_LED_GREEN_PIN, LOW);
    		delay(500);
	}
}

/* The setup() funtion runs one time at the beginning of the Energia program */
void setup() {
	/* Set serial communication to 115200 baud rate for MSP432 */
	Serial.begin(115200);
	delay(500);

	/* Run setup code */
	setupRSLK();

	/* Left and right button on LaunchPad */
	pinMode(LP_S1_PIN, INPUT_PULLUP);
	pinMode(LP_S2_PIN, INPUT_PULLUP);
}

/* The loop() function runs after the setup() function completes in an Energia porgram 
   and will continue to run in a repeating loop until the LaunchPad is reset or powered off */
void loop() {
	uint16_t total_count = 0; // Total amount of encoder pulses received

	uint8_t default_speed = 10; // Default raw pwm speed for motor.
	uint8_t left_wheel_speed = default_speed;
	uint8_t right_wheel_speed = default_speed;

	/* Amount of encoder pulses needed to achieve distance */
	uint16_t x = countForDistance(WHEEL_DIAMETER, CNT_PER_REVOLUTION, INCHES_TO_TRAVEL);
	Serial.print("Expected count: ");
	Serial.println(x);
  
	Serial.println("Waiting until left or right button is pushed");
	/* Wait until button is pressed to start robot */
	waitBtnPressed();

	/* Wait two seconds before starting */
	delay(2000);
  

	/* Set the encoder pulses count back to zero */
	resetLeftEncoderCnt();
	resetRightEncoderCnt();

	/* Cause the robot to drive forward */
	setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

	/* "Turn on" the motor */
	enableMotor(BOTH_MOTORS);

	/* Set motor speed */
	setMotorSpeed(LEFT_MOTOR,left_wheel_speed);
	setMotorSpeed(RIGHT_MOTOR,right_wheel_speed);

	/* Drive motor until it has received x pulses */
	while(total_count < x)
	{
		total_count = getEncoderLeftCnt();
		Serial.println(total_count);
	}

	/* Halt motors */
	disableMotor(BOTH_MOTORS);
} 