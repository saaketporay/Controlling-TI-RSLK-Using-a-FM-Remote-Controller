#include "Energia.h"

/* Defines bump switch functions of robot */
#include "Bump_Switch.h"
#include "QTRSensors.h"
#include "Romi_Motor_Power.h"
#include "Encoder.h"

/* Defines pin configuration of robot */
#include "RSLK_MAX_Pins.h"

/* Defines struct for state machine states */
typedef enum
{
    START = 0,
    WAIT,
    GO,
    GO2,
    BUMPED1a,
    BUMPED1b,
    DRIVE,
    STOP
} my_state_t;

/* Initialize state machine in START state */
my_state_t state = START;

/* Variable that will take the state machine to the STOP state */
bool done;

/* Initialize objects */ 
Romi_Motor_Power left_motor;
Romi_Motor_Power right_motor;

/*QTRDimmableRC  qtrrc((unsigned char[])
     {LS_PIN_1, 
      LS_PIN_2, 
      LS_PIN_3, 
      LS_PIN_4, 
      LS_PIN_5, 
      LS_PIN_6, 
      LS_PIN_7, 
      LS_PIN_8},
    NUM_SENSORS, TIMEOUT, LS_PIN_IR_EVEN, LS_PIN_IR_ODD);
*/

void Initialize_System()
{
  /* Set serial communication to 115200 baud rate for MSP432 */
  Serial.begin(115200);
  delay(500);
  Serial.println("Initializing.....");
  
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

  /* Set bump switches to inputs */
  pinMode(BP_SW_PIN_0,INPUT_PULLUP);
  pinMode(BP_SW_PIN_1,INPUT_PULLUP);
  pinMode(BP_SW_PIN_2,INPUT_PULLUP);
  pinMode(BP_SW_PIN_3,INPUT_PULLUP);
  pinMode(BP_SW_PIN_4,INPUT_PULLUP);
  pinMode(BP_SW_PIN_5,INPUT_PULLUP);

  /* Initialize motor object pins */
  left_motor.begin(MOTOR_L_SLP_PIN, MOTOR_L_DIR_PIN, MOTOR_L_PWM_PIN);
  right_motor.begin(MOTOR_R_SLP_PIN, MOTOR_R_DIR_PIN, MOTOR_R_PWM_PIN);

  /* Enable motors and set initial direction and speed */
  left_motor.enableMotor();
  right_motor.enableMotor();
   
  left_motor.directionForward();
  right_motor.directionForward();

  left_motor.setSpeed(20);
  right_motor.setSpeed(20);
  
  left_motor.disableMotor();
  right_motor.disableMotor(); 

  /* Initialize Encoder */
  setupEncoder(ENCODER_ELA_PIN, ENCODER_ELB_PIN, ENCODER_ERA_PIN, ENCODER_ERB_PIN);

  /* Initialize Line Sensor */
  
  Serial.println("Initializing System Complete.");
}


void setup() {
  Initialize_System();
}


void loop() {


  // Emergency stop switch S2
  // Switch to state "STOP" if pressed
  if (digitalRead(LP_S2_PIN) == 0) state = STOP;

  //-----------------------------------
  //        Main State Machine
  //-----------------------------------
  switch (state) {

    case START:
        Serial.println("Enter START state");
        state = WAIT;
    break;

    case WAIT:
        Serial.println("Enter WAIT state");
        digitalWrite(LP_RGB_LED_GREEN_PIN, HIGH);
        delay(200);
        digitalWrite(LP_RGB_LED_GREEN_PIN, LOW);
        delay(200);
        if (digitalRead(LP_S1_PIN) == 0) {
            state = GO;
        }
    break;

    case GO:
        Serial.println("Enter GO state");
        /* Start running the motors */
        left_motor.enableMotor();
        right_motor.enableMotor();
        left_motor.directionForward();
        right_motor.directionForward();
        left_motor.setSpeed(25);
        right_motor.setSpeed(25);
        
        state = GO2;
    break;

    case GO2:
        Serial.println("Enter GO2 state");
        /* Detect a bump and then switch to bump correction state */
        if (digitalRead(BP_SW_PIN_0) == 0 || digitalRead(BP_SW_PIN_1) == 0 || digitalRead(BP_SW_PIN_2) == 0 || 
              digitalRead(BP_SW_PIN_3) == 0 || digitalRead(BP_SW_PIN_4) == 0 || digitalRead(BP_SW_PIN_5) == 0)  state = BUMPED1a;

        /* Continue to rotate until done condition is met */
        /* Certain distance traveled or other conditions can be set */
        if (getEncoderLeftCnt() > 50000) {
          done = 1; 
        }

        if (done) state = STOP;
    break;

    case BUMPED1a:
        Serial.println("Enter BUMPED1a state");
        /* Stop the motors */
        left_motor.setSpeed(0);
        right_motor.setSpeed(0);
        /* Reverse the robot */
        left_motor.directionBackward();
        right_motor.directionBackward();
        left_motor.setSpeed(25);
        right_motor.setSpeed(25);
        delay(500);
        
        state = BUMPED1b;
    break;

    case BUMPED1b:
        Serial.println("Enter BUMPED1b state");
        /* Turn robot to avoid obstacle */
        left_motor.setSpeed(0);
        right_motor.setSpeed(25);
        delay(100);

        state = DRIVE;
    break;

    case DRIVE:
        Serial.println("Enter DRIVE state");
        /* Put motors back to forward direction */
        left_motor.directionForward();
        right_motor.directionForward();
        left_motor.setSpeed(25);
        right_motor.setSpeed(25);

        state = GO2;
    break;

    case STOP:
          Serial.println("Enter STOP state");
          Serial.println("Press Reset to begin again");
          /* Stop all motors */
          left_motor.disableMotor();
          right_motor.disableMotor();
    break;
  }

  delay(10);
}
