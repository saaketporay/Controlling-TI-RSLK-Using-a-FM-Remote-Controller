#include <SparkFunMiniMoto.h>  // Include the MiniMoto library
 
// Create two MiniMoto instances, with different address settings.
MiniMoto motor0(0x67); // A1 = 1, A0 = clear
MiniMoto motor1(0x68); // A1 = 1, A0 = 1 (default)
 
#define FAULTn  16     // Pin used for fault detection.
 
int serialA = 2;
int lastSerial = 2;
//start the motors derated (less than full power)
int lPwr = 50;
int rPwr = 50;
 
void setup() 
{
// initialize the serial communication:
Serial1.begin(9600);
Serial.begin(9600);
}
 
 
 
void loop() {
 
  switch (serialA) {
  case 1:  //fwd
      motor0.drive(lPwr);
      motor1.drive(rPwr);
    lastSerial = 1;
    break;
  case 2:  //stop
      motor0.stop();
      motor1.stop();
    lastSerial = 2;
    break;
  case 3:  //left
      motor0.drive(lPwr);
      motor1.drive(-1 * rPwr);
    lastSerial = 3;
    break;
  case 4:  //right
      motor0.drive(-1 * lPwr);
      motor1.drive(rPwr);
    lastSerial = 4;
    break;
  case 5:  //backwards
      motor0.drive(-1 * lPwr);
      motor1.drive(-1 * rPwr);
    lastSerial = 5;
    break;
  case 11:  //left motor boost
    if (lPwr < 62 && lastSerial != 11) {
      lPwr += 2;
    }
    lastSerial = 11;
    break;
  case 12:  //left motor derate
    if (lPwr > 2 && lastSerial != 12) {
      lPwr -= 2;
    }
    lastSerial = 12;
    break;
  case 13:  // right motor boost
    if (rPwr < 62 && lastSerial != 13) {
      rPwr += 2;
    }
    lastSerial = 13;
    break;
  case 14:  //right motor derate
    if (rPwr > 0 && lastSerial != 14) {
      rPwr -= 2;
    }
    lastSerial = 14;
    break;
 
  default:
    break;
  }
 
  if(Serial1.available()){
    serialA = Serial1.read(); 
    Serial.println("Char rx'ed");
   
  }
}
