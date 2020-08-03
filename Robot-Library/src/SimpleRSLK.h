#ifndef SimpleRSLK_h
#define SimpleRSLK_h

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define BOTH_MOTORS 2

#define MOTOR_DIR_FORWARD 0
#define MOTOR_DIR_BACKWARD 1

#define NUM_SENSORS 8
#define TIMEOUT 100000

#include "RSLK_MAX_Pins.h"
#include "QTRSensors.h"
#include "GP2Y0A21_Sensor.h"
#include "Encoder.h"
#include "Romi_Motor_Power.h"
#include "Bump_Switch.h"

void setupRSLK();
uint16_t readSharpDist(uint8_t num);
bool isBumpSwitchPressed(uint8_t num);
void enableMotor(uint8_t motorNum);
void disableMotor(uint8_t motorNum);
void pauseMotor(uint8_t motorNum);
void resumeMotor(uint8_t motorNum);
void setMotorDirection(uint8_t motorNum,uint8_t direction);
void setMotorSpeed(uint8_t motorNum, uint8_t speed);
void calLineSensor();
void getLineSensorValue(unsigned int *sensor);
void getLineSensorCalValue(unsigned int *sensor);
void printLineSensorCal();
#endif