#include <Stepper.h>

//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

// Define the stepper with the correct pins, note that the two middle pins need to be in reverse order
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 4, 6, 5, 7);

int Steps2Take;


void setup() {
  // Wait for system to power up stable
  delay(3000); 
  
  //Serial.begin(9600);
  
  // Trapdoor / cube sensor only has one contact.
  // Should it have two? 
  pinMode(12, INPUT_PULLUP);
  //pinMode(13, INPUT_PULLUP);
}

void loop() {
  testSensor();
}


void testSensor() {
  // switches
  int rightSwitch = digitalRead(13);
  int leftSwitch = digitalRead(12);

  // debug print
  Serial.print("RIGHT: ");
  Serial.print(rightSwitch);
  Serial.print(", LEFT: ");
  Serial.println(leftSwitch);

  // if both switches are on, send signal to cube dispenser
  if ((rightSwitch + leftSwitch) == 0) {
    openGate();
  } else {
    Serial.println(", HOLD");
  }
  delay(200);
}

void dropCube() {
  // some timer so cubes aren't dispensed all at once,
  // as standing on the sensor will keep triggering it
  // should probably dispense one every 15s? 
}

void openGate() {

  // OPEN GATE
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 4;  // Rotate CW 1/4 turn
  small_stepper.setSpeed(300);   
  small_stepper.step((Steps2Take));
  delay(1000);

  // HOLD OPEN FOR 15s
  // delay(15000);

  Steps2Take  =  (-1)*STEPS_PER_OUTPUT_REVOLUTION / 4;  // Rotate CCW 1/4 turn  
  small_stepper.setSpeed(300);
  small_stepper.step(Steps2Take);
  delay(1000);

}

