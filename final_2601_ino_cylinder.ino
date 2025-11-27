#include <Servo.h>  // Include servo control library

// Step 1: Create 5 Servo objects (one for each motor)
Servo baseServo;    // Servo 1: Base rotation
Servo extendServo;  // Servo 2: Arm extension
Servo clawServo;    // Servo 3: Claw grab/release
Servo liftServo;    // Servo 4: Arm lifting
Servo wristServo;   // Servo 5: Wrist tilt

// Step 2: Define "home" and "target" angles for each servo (adjust for your arm!)
// Home = Initial position; Target = Position for each step
const int BASE_HOME = 0;    // Base: Neutral (facing forward)
const int BASE_TARGET = 0;  // Base: Rotate left to target object (adjust angle)
const int BASE_BOX = 100;

const int EXTEND_HOME = 80;  // Arm: Retracted (shortest)
const int EXTEND_BOX = 120;
const int EXTEND_TARGET = 180; // Arm: Extended to reach object (adjust length)

const int CLAW_OPEN = 100;   // Claw: Fully open (ready to grab)
const int CLAW_CLOSED = 20;  // Claw: Fully closed (grab object)

const int LIFT_HOME = 40;    // Arm: Low (close to table)
const int LIFT_UP = 70;      // Arm: Lifted up (avoid hitting obstacles)
const int LIFT_DOWN = 180;   // Arm: Lowered to release object
const int LIFT_BOX = 100;    // Arm: Lowered to release object

const int WRIST_HOME = 90;   // Wrist: Neutral (claw facing down)
const int WRIST_GRAB = 55;   // Wrist: Tilt slightly to better grab object

// Movement control variables
const int SLOW_DELAY = 50;   // Delay between small movements (ms)
const int STEP_SIZE = 5;     // Degrees to move per step (smaller = slower)

void setup() {
  // Step 3: Attach each servo to its ESP8266 PWM pin
  baseServo.attach(5);    // Base 
  extendServo.attach(4);  // Extension (base2)
  clawServo.attach(12);   // Claw 
  liftServo.attach(14);   // Lift (neck)
  wristServo.attach(16);  // bottom Wrist

  // Step 4: Move all servos to "home" position first (safe initial state)
  moveServoSlowly(baseServo, BASE_HOME);
  moveServoSlowly(extendServo, EXTEND_HOME);
  moveServoSlowly(clawServo, CLAW_OPEN);
  moveServoSlowly(liftServo, LIFT_HOME);
  moveServoSlowly(wristServo, WRIST_HOME);
  delay(2000);  // Wait 2 seconds for servos to reach home
}

// Function to move servo slowly to target position
void moveServoSlowly(Servo &servo, int targetAngle) {
  int currentAngle = servo.read();
  
  if (currentAngle < targetAngle) {
    for (int pos = currentAngle; pos <= targetAngle; pos += STEP_SIZE) {
      servo.write(pos);
      delay(SLOW_DELAY);
    }
  } else {
    for (int pos = currentAngle; pos >= targetAngle; pos -= STEP_SIZE) {
      servo.write(pos);
      delay(SLOW_DELAY);
    }
  }
  // Ensure final position is exact
  servo.write(targetAngle);
  delay(300); // Small pause after movement completion
}

void loop() {
  // --------------------------
  // Step 1: Rotate Base to Target Object
  // --------------------------
  moveServoSlowly(baseServo, BASE_TARGET);

  // --------------------------
  // Step 3: Adjust Wrist Angle
  // --------------------------
  moveServoSlowly(wristServo, WRIST_GRAB);

  // --------------------------
  // Step 4: Close Claw to Grab Object
  // --------------------------
  moveServoSlowly(clawServo, CLAW_CLOSED);

  // --------------------------
  // Step 7: Lower Arm to Release Height
  // --------------------------
  moveServoSlowly(liftServo, LIFT_DOWN);

  // --------------------------
  // Step 2: Extend Arm to Reach Object
  // --------------------------
  moveServoSlowly(extendServo, EXTEND_TARGET);
                      
  // --------------------------
  // Step 8: Open Claw to Release Object
  // --------------------------
  moveServoSlowly(clawServo, CLAW_OPEN);

  // --------------------------
  // Step 5: Lift Arm Up (Avoid Hitting Surfaces)
  // --------------------------
  moveServoSlowly(liftServo, LIFT_UP);

  // --------------------------
  // Step 6: Rotate Base to Target Release Position
  // --------------------------
  moveServoSlowly(baseServo, BASE_BOX);

  // --------------------------
  // Step 2: Extend Arm to Reach Box
  // --------------------------
  moveServoSlowly(extendServo, EXTEND_BOX);

  // --------------------------
  // Step 7: Lower Arm to Release Height
  // --------------------------
  moveServoSlowly(liftServo, LIFT_DOWN);

  // --------------------------
  // Step 4: Close Claw to Grab Object
  // --------------------------
  moveServoSlowly(clawServo, CLAW_CLOSED);

  // --------------------------
  // Step 9: Reset All Servos to Home Position
  // --------------------------
  moveServoSlowly(extendServo, EXTEND_HOME);
  moveServoSlowly(wristServo, WRIST_HOME);
  moveServoSlowly(liftServo, LIFT_HOME);
  
  delay(2000); // Wait before next cycle
}