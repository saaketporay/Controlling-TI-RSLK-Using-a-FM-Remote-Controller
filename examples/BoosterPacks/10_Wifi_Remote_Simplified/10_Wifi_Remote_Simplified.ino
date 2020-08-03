#include "SimpleRSLK.h"
#include "Wifi_Remote.h"

/*
 * Robot Wifi Example
 * 
 * This example will demonstrate controlling the remote via Wifi
 * by Franklin S. Cooper Jr.
 */

String wifi_name = "rslk";
String wifi_password = "rslkwifi";

void setup()
{
  Serial.begin(115200);
  wifi_setup();
  setupRSLK();
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS,50);
}

void loop()
{
  wifiLoop();
}

void custom_logic() {
	if (left_button_pressed)
        setMotorSpeed(RIGHT_MOTOR,70);
    else
        setMotorSpeed(RIGHT_MOTOR,50);
    
    if (right_button_pressed)
        setMotorSpeed(LEFT_MOTOR,70);
    else
        setMotorSpeed(LEFT_MOTOR,50);

    if (up_down_pressed) {
      enableMotor(BOTH_MOTORS);
      
      if(up_button_pressed)
        setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
      
      if(down_button_pressed)
        setMotorDirection(BOTH_MOTORS,MOTOR_DIR_BACKWARD);
    }
    else
		  disableMotor(BOTH_MOTORS);
}