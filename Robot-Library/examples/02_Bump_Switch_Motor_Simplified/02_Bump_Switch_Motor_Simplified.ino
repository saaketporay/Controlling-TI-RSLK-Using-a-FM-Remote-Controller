/* TI-RSLK MAX Example 2 */
/* Robot will drive forward until it hits an object with bump switches */

#include "Energia.h"

/* Defines functions of robot */
#include "SimpleRSLK.h"

// TIP: Use the Energia pin maps to find out what capabilities are attached to the LaunchPad
//      The pin maps show the functions on each pin and the pin number and names used in Energia 

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
	bool hit_obstacle = false;
  
	Serial.println("Waiting until left or right button is pushed");
	/* Wait until button is pressed to start robot */
	waitBtnPressed();

  /* Wait two seconds before starting */
  delay(2000);
  
 /* Enables specified motor.
  *  Parameter:
  *   Motor your referencing -> LEFT_MOTOR  RIGHT_MOTOR  BOTH_MOTORS
  */
	enableMotor(BOTH_MOTORS);

 /* Set direction of motor rotation.
  *  Parameter:
  *   Motor your referencing -> LEFT_MOTOR  RIGHT_MOTOR  BOTH_MOTORS
  *   Direction -> MOTOR_DIR_FORWARD  MOTOR_DIR_BACKWARD
  */
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  
 /* Set speed of motor.
  *  Parameter:
  *   Motor your referencing -> LEFT_MOTOR  RIGHT_MOTOR  BOTH_MOTORS
  *   Speed -> 0 - 100
  */
	setMotorSpeed(BOTH_MOTORS, 10);

	while(!hit_obstacle) {
		// Drive the robot forward until it runs into something
		for(int x = 0;x<6;x++)
		{
      /* Check if bump switch was pressed
       *  Parameter:
       *    bump switch number -> 0-5
       *    Returns:
       *      true -> if specific switch was pressed
       *      false -> if specific switch was not pressed
       */
			if(isBumpSwitchPressed(x) == true) {
				hit_obstacle = true;
        Serial.println("Collision detected");
				break;
			}
		}
	}

	disableMotor(BOTH_MOTORS);
}