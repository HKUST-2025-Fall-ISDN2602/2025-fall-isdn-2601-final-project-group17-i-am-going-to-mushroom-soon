#include <Servo.h>  // Include servo control library ({insert\_element\_2\_}, {insert\_element\_3\_})

// Step 1: Create 5 Servo objects (one for each motor, {insert\_element\_4\_})
Servo baseServo;    // Servo 1: Base rotation
Servo extendServo;  // Servo 2: Arm extension
Servo clawServo;    // Servo 3: Claw grab/release
Servo liftServo;    // Servo 4: Arm lifting
Servo wristServo;   // Servo 5: Wrist tilt

// Step 2: Define "home" and "target" angles for each servo (adjust for your arm!)
// Home = Initial position; Target = Position for each step
const int BASE_HOME = 90;    // Base: Neutral (facing forward)
const int BASE_TARGET = 0;  // Base: Rotate left to target object (adjust angle)
const int BASE_BOX = 180;

const int EXTEND_HOME = 80;  // Arm: Retracted (shortest)
const int EXTEND_BOX = 120;
const int EXTEND_TARGET = 85;// Arm: Extended to reach object (adjust length)

const int CLAW_OPEN = 130;   // Claw: Fully open (ready to grab)
const int CLAW_CLOSED = 20;  // Claw: Fully closed (grab object)

const int LIFT_HOME = 40;    // Arm: Low (close to table)
const int LIFT_UP = 70;      // Arm: Lifted up (avoid hitting obstacles)
const int LIFT_DOWN = 180;    // Arm: Lowered to release object
const int LIFT_BOX = 100;    // Arm: Lowered to release object

const int WRIST_HOME = 90;   // Wrist: Neutral (claw facing down)
const int WRIST_GRAB = 20;   // Wrist: Tilt slightly to better grab object


void setup() {
  // Step 3: Attach each servo to its ESP8266 PWM pin ({insert\_element\_5\_}, {insert\_element\_6\_})
  baseServo.attach(5);    // Base 
  extendServo.attach(4);  // Extension (base2)
  clawServo.attach(12);    // Claw 
  liftServo.attach(14);     // Lift (neck)S
  wristServo.attach(16);    //bottom Wrist

  // Step 4: Move all servos to "home" position first (safe initial state)
  baseServo.write(BASE_HOME);
  extendServo.write(EXTEND_HOME);
  clawServo.write(CLAW_OPEN);
  liftServo.write(LIFT_HOME);
  wristServo.write(WRIST_HOME);
  delay(2000);  // Wait 2 seconds for servos to reach home (adjust if needed)
}


void loop() {
  // --------------------------
  // Step 1: Rotate Base to Target Object
  // --------------------------
  baseServo.write(BASE_TARGET);  // Turn base to face the object
  delay(1500);                   // Wait 1.5s for base to finish rotating (adjust time)


  // --------------------------
  // Step 3: Adjust Wrist Angle (Optional but helps grab)
  // --------------------------
  wristServo.write(WRIST_GRAB);  // Tilt wrist to align claw with object
  delay(1500);                   // Wait 1s for wrist to adjust

  // // --------------------------
  // // Step 4: Close Claw to Grab Object
  // // --------------------------
  clawServo.write(CLAW_CLOSED);  // Close claw tightly to hold the object
  delay(1000);                   // Wait 1.5s for claw to close (ensure grip)

  // // --------------------------
  // // Step 7: Lower Arm to Release Height
  // // --------------------------
  liftServo.write(LIFT_DOWN);  // Lower arm to place object gently
  delay(1500);                 // Wait 1.5s for arm to lower

  // --------------------------
  // Step 2: Extend Arm to Reach Object
  // --------------------------
  extendServo.write(EXTEND_TARGET);  // Extend arm toward the object
  delay(1500);                       // Wait 1.5s for arm to extend
                       
  // // --------------------------
  // // Step 8: Open Claw to Release Object
  // // --------------------------
  clawServo.write(CLAW_OPEN);  // Open claw to let go of the object
  delay(1500);                 // Wait 1.5s for claw to open

  // --------------------------
  // Step 5: Lift Arm Up (Avoid Hitting Surfaces)
  // --------------------------
  liftServo.write(LIFT_UP);  // Lift the arm with the object
  delay(1500);               // Wait 1.5s for arm to lift

  // // --------------------------
  // // Step 6: Rotate Base to Target Release Position
  // // --------------------------
  baseServo.write(BASE_BOX);  // Rotate base back to neutral (or new release angle)
  delay(1500);                 // Wait 1.5s for base to rotate

  // --------------------------
  // Step 2: Extend Arm to Reach Object
  // --------------------------
  extendServo.write(EXTEND_BOX);  // Extend arm toward the object
  delay(1500);                       // Wait 1.5s for arm to extend

  // // --------------------------
  // // Step 7: Lower Arm to Release Height
  // // --------------------------
  liftServo.write(LIFT_DOWN);  // Lower arm to place object gently
  delay(1500);                 // Wait 1.5s for arm to lower

  // // --------------------------
  // // Step 4: Close Claw to Grab Object
  // // --------------------------
  clawServo.write(CLAW_CLOSED);  // Close claw tightly to hold the object
  delay(1500);                   // Wait 1.5s for claw to close (ensure grip)

  // --------------------------
  // Step 9: Reset All Servos to Home Position (Ready for Next Cycle)
  // --------------------------
  extendServo.write(EXTEND_HOME);  // Retract arm
  wristServo.write(WRIST_HOME);    // Reset wrist to neutral
  liftServo.write(LIFT_HOME);      // Lower arm fully (optional)
  delay(2000);                     // Wait 2s for reset

}