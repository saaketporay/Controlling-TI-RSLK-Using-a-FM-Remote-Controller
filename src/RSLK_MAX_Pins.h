#ifndef RSLKMAXPins_h
#define RSLKMAXPins_h

/* TI-RSLK MAX */

/* MSP-EXP432P401R 
 * Red LED, RGB LED, two push buttons on board 
 */
#define LP_RED_LED_PIN		78 // <- Energia Pin #   Launchpad Pin -> P1.0
#define LP_RGB_LED_RED_PIN	75 // <- Energia Pin #   Launchpad Pin -> P2.0
#define LP_RGB_LED_GREEN_PIN	76 // <- Energia Pin #   Launchpad Pin -> P2.1
#define LP_RGB_LED_BLUE_PIN	77 // <- Energia Pin #   Launchpad Pin -> P2.2
#define LP_S1_PIN		73 // <- Energia Pin #   Launchpad Pin -> P1.1
#define LP_S2_PIN		74 // <- Energia Pin #   Launchpad Pin -> P1.4

/* Blinker LEDs on Chassis Board (https://www.pololu.com/product/3671)
 */
#define LED_BL_PIN	57 // <- Energia Pin #   Launchpad Pin -> P8.6
#define LED_BR_PIN	58 // <- Energia Pin #   Launchpad Pin -> P8.7
#define LED_FL_PIN	51 // <- Energia Pin #   Launchpad Pin -> P8.0
#define LED_FR_PIN	41 // <- Energia Pin #   Launchpad Pin -> P8.5

/* 8-Channel QTRX Reflectance Sensor Array Pins (https://www.pololu.com/product/3672)
 * Below shows how the line sensor pins are mapped to the MSP-EXP432P401R 
 */
#define LS_PIN_IR_EVEN	61 // <- Energia Pin #   Launchpad Pin -> P5.3
#define LS_PIN_IR_ODD	45 // <- Energia Pin #   Launchpad Pin -> P9.2
#define LS_PIN_1	65 // <- Energia Pin #   Launchpad Pin -> P7.0
#define LS_PIN_2	48 // <- Energia Pin #   Launchpad Pin -> P7.1
#define LS_PIN_3	64 // <- Energia Pin #   Launchpad Pin -> P7.2
#define LS_PIN_4	47 // <- Energia Pin #   Launchpad Pin -> P7.3
#define LS_PIN_5	52 // <- Energia Pin #   Launchpad Pin -> P7.4
#define LS_PIN_6	68 // <- Energia Pin #   Launchpad Pin -> P7.5
#define LS_PIN_7	53 // <- Energia Pin #   Launchpad Pin -> P7.6
#define LS_PIN_8	69 // <- Energia Pin #   Launchpad Pin -> P7.7

/* Pololu Snap-Action Switches (https://www.pololu.com/product/1404)
 * Robot utilizes 6 of these switches.
 * Switches' common pin is connected to ground.
 * NO (normally open) is connected to Launchpad
 */
#define BP_SW_PIN_0 24 // <- Energia Pin #   Launchpad Pin -> P4.0
#define BP_SW_PIN_1 25 // <- Energia Pin #   Launchpad Pin -> P4.2
#define BP_SW_PIN_2 6 // <- Energia Pin #   Launchpad Pin -> P4.3
#define BP_SW_PIN_3 27 // <- Energia Pin #   Launchpad Pin -> P4.5
#define BP_SW_PIN_4 8 // <- Energia Pin #   Launchpad Pin -> P4.6
#define BP_SW_PIN_5 28 // <- Energia Pin #   Launchpad Pin -> P4.7

/* Motor Driver and Power Distribution Board (https://www.pololu.com/product/3543)
 * Pin configuration for the left and right motor's sleep, direction and pwm pin
 */
#define MOTOR_L_SLP_PIN 31  // <- Energia Pin #   Launchpad Pin -> P3.7
#define MOTOR_L_DIR_PIN 29  // <- Energia Pin #   Launchpad Pin -> P5.4
#define MOTOR_L_PWM_PIN 40  // <- Energia Pin #   Launchpad Pin -> P2.7
#define MOTOR_R_SLP_PIN 11  // <- Energia Pin #   Launchpad Pin -> P3.6
#define MOTOR_R_DIR_PIN 30  // <- Energia Pin #   Launchpad Pin -> P5.5
#define MOTOR_R_PWM_PIN 39  // <- Energia Pin #   Launchpad Pin -> P2.6

/* Romi Gear Motor and Encoder assembly (https://www.pololu.com/product/3675)
 * Robot utilizes two encoders, one for the left wheel and one for the right wheel
 */
#define ENCODER_ERA_PIN 56 // <- Energia Pin #   Launchpad Pin -> P10.4
#define ENCODER_ERB_PIN 13 // <- Energia Pin #   Launchpad Pin -> P5.0
#define ENCODER_ELA_PIN 72 // <- Energia Pin #   Launchpad Pin -> P10.5
#define ENCODER_ELB_PIN 12 // <- Energia Pin #   Launchpad Pin -> P5.2

/* Optional Accessories for TI-RSLK
 * Sensors and additional actuators can be used to create custom experiences
 * Some are standalone attachments that mount to the chassis and others are BoosterPacks 
 * that attach to the LaunchPad with the standard connectors
 */

/* Romi Robot Arm Attachment (https://www.pololu.com/product/3550)
 * 3 servos with control signals and analog feedback
 */
#define SERVO_ARM_PWM_PIN 	38 // <- Energia Pin #   Launchpad Pin -> P2.4
#define SERVO_GRIP_PWM_PIN 	17 // <- Energia Pin #   Launchpad Pin -> P5.7
#define SERVO_TILT_PWM_PIN 	32 // <- Energia Pin #   Launchpad Pin -> P3.5
#define SERVO_ARM_FB_PIN 	43 // <- Energia Pin #   Launchpad Pin -> P8.4
#define SERVO_GRIP_FB_PIN 	44 // <- Energia Pin #   Launchpad Pin -> P8.2
#define SERVO_TILT_FB_PIN 	60 // <- Energia Pin #   Launchpad Pin -> P8.3


/* Sharp GP2Y0A21YK0F Analog Distance Sensor (https://www.pololu.com/product/136)
 * Robot utilizes three of these sensors
 * AUX pins used for future sensors
 */
#define SHRP_DIST_L_PIN 	59 // <- Energia Pin #   Launchpad Pin -> P9.1
#define SHRP_DIST_C_PIN 	23 // <- Energia Pin #   Launchpad Pin -> P6.1
#define SHRP_DIST_R_PIN 	42 // <- Energia Pin #   Launchpad Pin -> P9.0
#define AUX_L_PIN		63 // <- Energia Pin #   Launchpad Pin -> P6.3
#define AUX_C_PIN		54 // <- Energia Pin #   Launchpad Pin -> P10.0
#define AUX_R_PIN		46 // <- Energia Pin #   Launchpad Pin -> P6.2

/* LCD or OLED (Sparkfun 10168, Adafruit 336, Adafruit 938)
 * Robot can add LCD as accessory using SPI
 */
#define OLED_AF_CS	49 // <- Energia Pin #   Launchpad Pin -> P9.4
#define OLED_AF_RST	62 // <- Energia Pin #   Launchpad Pin -> P9.3
#define OLED_AF_DC	50 // <- Energia Pin #   Launchpad Pin -> P9.6
#define OLED_AF_SCLK	66 // <- Energia Pin #   Launchpad Pin -> P9.5
#define OLED_AF_MOSI	67 // <- Energia Pin #   Launchpad Pin -> P9.7

#define LCD_AF_SCLK	66 // <- Energia Pin #   Launchpad Pin -> P9.5
#define LCD_AF_MOSI	67 // <- Energia Pin #   Launchpad Pin -> P9.7
#define LCD_AF_DC	50 // <- Energia Pin #   Launchpad Pin -> P9.6
#define LCD_AF_CS	49 // <- Energia Pin #   Launchpad Pin -> P9.4
#define LCD_AF_RST	62 // <- Energia Pin #   Launchpad Pin -> P9.3

#define LCD_SF_SCLK	66 // <- Energia Pin #   Launchpad Pin -> P9.5
#define LCD_SF_MOSI	67 // <- Energia Pin #   Launchpad Pin -> P9.7
#define LCD_SF_DC	50 // <- Energia Pin #   Launchpad Pin -> P9.6
#define LCD_SF_RST	62 // <- Energia Pin #   Launchpad Pin -> P9.3
#define LCD_SF_CS	49 // <- Energia Pin #   Launchpad Pin -> P9.4

/* I2C
 * Default I2C pins can be used to attach multiple sensors
 * I2C is a common way to communicate with periperhals of the processor
 */
#define I2C_SCL		9  // <- Energia Pin #   Launchpad Pin -> P6.5
#define I2C_SDA 	10 // <- Energia Pin #   Launchpad Pin -> P6.4

#endif