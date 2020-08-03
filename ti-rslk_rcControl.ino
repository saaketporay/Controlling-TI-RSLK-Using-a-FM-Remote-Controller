/* TI-RSLK Connect to Radio Controller */
/* Created by Saaket Poray using the TI-RSLK documentation and examples
  Allows for fully proportional motor control on the TI-RSLK
*/

/*
  BUGS:
  1. Motor initializes and starts spinning if not connected to controller. Make sure the radio is on to prevent this. Please feel free to add a pull request if you have a solution.
*/

#include "Energia.h"

/* Defines motor functions of robot */
#include "Romi_Motor_Power.h"

/* Defines pin configuration of robot */
#include "RSLK_MAX_Pins.h"


Romi_Motor_Power left_motor;
Romi_Motor_Power right_motor;

#define LEFT_BTN         73 // LaunchPad S1 pin number or can use LP_S1_PIN
#define RIGHT_BTN        74 // LaunchPad S2 pin number or can use LP_S2_PIN


int rc2; //intializes variable that stores the value recieved from channel 2 on the controller
int rc4; //intializes variable that stores the value recieved from channel 4 on the controller

/* The setup() funtion runs one time at the beginning of the Energia program */
void setup() {
  /* Set serial communication to 115200 baud rate for MSP432 */
  Serial.begin(115200);


  /* Initialize motor object pins */
  left_motor.begin(MOTOR_L_SLP_PIN,
                   MOTOR_L_DIR_PIN,
                   MOTOR_L_PWM_PIN);

  right_motor.begin(MOTOR_R_SLP_PIN,
                    MOTOR_R_DIR_PIN,
                    MOTOR_R_PWM_PIN);

  /* Set bump switches to inputs */
  pinMode(BP_SW_PIN_0, INPUT_PULLUP);
  pinMode(BP_SW_PIN_1, INPUT_PULLUP);
  pinMode(BP_SW_PIN_2, INPUT_PULLUP);
  pinMode(BP_SW_PIN_3, INPUT_PULLUP);
  pinMode(BP_SW_PIN_4, INPUT_PULLUP);
  pinMode(BP_SW_PIN_5, INPUT_PULLUP);

  /* Set left and right button on LaunchPad as input */
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);

  pinMode(2, INPUT);
  pinMode(4, INPUT);

}

/* The loop() function runs after the setup() function completes in an Energia porgram
   and will continue to run in a repeating loop until the LaunchPad is reset or powered off */
void loop() {

  left_motor.disableMotor();
  right_motor.disableMotor();
  rc2 = pulseIn(2, HIGH, 115200);
  rc4 = pulseIn(4, HIGH, 115200);

  digitalWrite(LP_RGB_LED_BLUE_PIN, HIGH);

  while (rc4 > 1550) //turn right
  {
    Serial.println("works");
    left_motor.enableMotor();
    right_motor.enableMotor();
    left_motor.directionForward();
    right_motor.directionBackward();

    left_motor.setSpeed((rc4 - 1550) / 5);
    right_motor.setSpeed((rc4 - 1550) / 5);
    rc2 = pulseIn(2, HIGH, 115200);
    rc4 = pulseIn(4, HIGH, 115200);

  }

  while (rc4 < 1490) //turn left
  {
    Serial.println("works");
    left_motor.enableMotor();
    right_motor.enableMotor();
    left_motor.directionBackward();
    right_motor.directionForward();

    left_motor.setSpeed((1490 - rc4) / 5);
    right_motor.setSpeed((1490 - rc4) / 5);
    rc2 = pulseIn(2, HIGH, 115200);
    rc4 = pulseIn(4, HIGH, 115200);

  }

  while (rc2 > 1550) //going forward
  {

    left_motor.enableMotor();
    right_motor.enableMotor();
    digitalWrite(LP_RGB_LED_RED_PIN, LOW);
    digitalWrite(LP_RGB_LED_GREEN_PIN, HIGH);
    left_motor.directionForward();
    right_motor.directionForward();

    left_motor.setSpeed((rc2 - 1550) / 5);
    right_motor.setSpeed((rc2 - 1550) / 5);
    rc2 = pulseIn(2, HIGH, 115200);
    rc4 = pulseIn(4, HIGH, 115200);

  }

  while (rc2 < 1490) //going backward
  {
    Serial.println("works");
    left_motor.enableMotor();
    right_motor.enableMotor();
    digitalWrite(LP_RGB_LED_GREEN_PIN, LOW);
    digitalWrite(LP_RGB_LED_RED_PIN, HIGH);
    left_motor.directionBackward();
    right_motor.directionBackward();

    left_motor.setSpeed((1490 - rc2) / 5);
    right_motor.setSpeed((1490 - rc2) / 5);
    rc2 = pulseIn(2, HIGH, 115200);
    rc4 = pulseIn(4, HIGH, 115200);

  }



}
