/* TI-RSLK MAX Example 5 */
/* Robot will drive a pattern in place returning to the same spot */

#include "Energia.h"

/* Defines functions of robot */
#include "SimpleRSLK.h"

bool hit_obstacle = false;

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

void checkCollision() {
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
      disableMotor(BOTH_MOTORS);
      break;
    }
  }
}

/* The setup() funtion runs one time at the beginning of the Energia program */
void setup() {
  /* Set serial communication to 115200 baud rate for MSP432 */
  Serial.begin(115200);
  delay(500);

  /* Run setup code */
  setupRSLK();

  /* Initialize LED pins as outputs */
  pinMode(LED_FR_PIN, OUTPUT); 
  pinMode(LED_FL_PIN, OUTPUT); 
  pinMode(LED_BR_PIN, OUTPUT); 
  pinMode(LED_BL_PIN, OUTPUT);
  pinMode(LP_RED_LED_PIN, OUTPUT);
  pinMode(LP_RGB_LED_RED_PIN, OUTPUT);
  pinMode(LP_RGB_LED_BLUE_PIN, OUTPUT); 
  pinMode(LP_RGB_LED_GREEN_PIN, OUTPUT);

  /* Initialize LaunchPad buttons as inputs */
  pinMode(LP_S1_PIN, INPUT_PULLUP);
  pinMode(LP_S2_PIN, INPUT_PULLUP);
}

/* The loop() function runs after the setup() function completes in an Energia porgram 
   and will continue to run in a repeating loop until the LaunchPad is reset or powered off */
void loop() {
  
  Serial.println("Waiting until left button is pushed");
  /* Wait until button is pressed to start robot */
  waitBtnPressed();

  /* Wait two seconds before starting */
  delay(2000);
  digitalWrite(LP_RGB_LED_BLUE_PIN, HIGH);
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
  setMotorDirection(LEFT_MOTOR,MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);
  
 /* Set speed of motor.
  *  Parameter:
  *   Motor your referencing -> LEFT_MOTOR  RIGHT_MOTOR  BOTH_MOTORS
  *   Speed -> 0 - 100
  */
  setMotorSpeed(BOTH_MOTORS,15);

  while(!hit_obstacle) {
    /* Drive the robot in pattern until it runs into something */
    delay(1000);
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    delay(1000);
    
    /* 360 spin */
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
    setMotorSpeed(BOTH_MOTORS,25);
    delay(1900);
    setMotorSpeed(BOTH_MOTORS,15);

    /* Left turn */
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    delay(500);

    /* Back and Front */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_BACKWARD);
    delay(1000);
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    delay(1000);

    /* 360 spin */
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
    setMotorSpeed(BOTH_MOTORS,25);
    delay(1900);
    setMotorSpeed(BOTH_MOTORS,15);
    
    /* Left turn */
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    delay(500);

    /* Back and Front */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_BACKWARD);
    
  }
  disableMotor(BOTH_MOTORS);
}