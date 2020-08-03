#include "SimpleRSLK.h"
#include <BLE.h>
#include <String.h>

/*
 * Robot BLE Example
 * 
 * This example will demonstrate controlling the remote via bluetooth
 * 
 */
 

/* +1 for null-terminator */
int numBytes = 0;
char serialData[BLE_SERIAL_BUFFER_SIZE + 1];


void setup() {
  
  /* Set serial communication to 115200 baud rate for MSP432 */
  Serial.begin(115200);
  delay(500);
  Serial.println("Initializing.....");

  setupRSLK();
  
  ble.setLogLevel(BLE_LOG_ERRORS);
  ble.begin();
  ble.serial();
  ble.setAdvertName("Energia Serial");
  ble.startAdvert();


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

  Serial.println("Initializing System Complete.");

}

void parseSerialString(String dataString)
{
  // Check if we found Adafruit app msg start char
  if('!' == dataString.charAt(0))
  {
    switch (dataString.charAt(1))
    {
      case 'C':
      {
        // RGB color packet is of the form "[!],[C], [R byte], [G Byte], [B byte]"
        Serial.println("Received Adafruit RGB LED Color Packet");
        char redVal = dataString.charAt(2);
        char greenVal = dataString.charAt(3);
        char blueValue = dataString.charAt(4);

        // Use PWM to write the color to the RGB LED
        analogWrite(LP_RGB_LED_RED_PIN, redVal);
        analogWrite(LP_RGB_LED_GREEN_PIN, greenVal);
        analogWrite(LP_RGB_LED_BLUE_PIN, blueValue);
        break;
      }
      case 'B':
      {
        // Buttons packet is of the form: "[!], [B], [Button #] [1 (pressed)/0 (released)]
        String state = (('1' == dataString.charAt(3)) ? " Pressed" : "  Released");
        String result = "Received Adafruit Button Packet: Button ";
        result += dataString.charAt(2) + state;
        Serial.println(result);
      }
      default:
        break;
    }
    case 'D':
      {
        // Buttons packet is of the form: "[!], [B], [Button #] [1 (pressed)/0 (released)]
        String state = (('1' == dataString.charAt(3)) ? " Pressed" : "  Released");
        String result = "Received Adafruit Button Packet: Button ";
        result += dataString.charAt(2) + state;
        Serial.println(result);
      }
      default:
        break;
    }
  }
}

void loop() {
  ble.handleEvents();
  /* Forward Energia serial monitor to BLE serial. */
  if (Serial.available())
  {
    while ((numBytes = Serial.available()))
    {
      Serial.readBytes(serialData, numBytes);
      serialData[numBytes] = '\0';
      Serial.print("Sending via serial:");
      Serial.println(serialData);
      ble.print(serialData);
    }
  }
  if (ble.available())
  {
    /* All the Serial functions are available with BLE serial. */
    String leData = ble.readString();
    parseSerialString(leData);
    Serial.print("Received via BLE:");
    Serial.println(leData);
  }
}
