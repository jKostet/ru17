#include <Stepper.h>
#include <Servo.h>

Servo servo1;

//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

// Define the stepper with the correct pins, note that the two middle pins need to be in reverse order
//Stepper gateStepper(STEPS_PER_MOTOR_REVOLUTION, 10, 12, 11, 13);
Stepper leftStepper(STEPS_PER_MOTOR_REVOLUTION, 6, 8, 7, 9);
Stepper rightStepper(STEPS_PER_MOTOR_REVOLUTION, 2, 4, 3, 5);

int Steps2Take, i;
int pos;

void setup() {
  // Wait for system to power up stable
  delay(3000); 
  servo1.attach(14);
//  servo2.attach(15);
  pos = 15;
  
  //Serial.begin(9600);
  
  // Trapdoor / cube sensor only has one contact.
  // Should it have two? 
  //pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
}

void loop() {
  testSensor();
  //openGate();
  //openTrap();
}


void testSensor() {
  // switches  delay(100);

  int rightSwitch = digitalRead(13);
  //int leftSwitch = digitalRead(12);

  // debug print
  //Serial.print("RIGHT: ");
  //Serial.print(rightSwitch);
  //Serial.print(", LEFT: ");
  //Serial.println(leftSwitch);

  // if both switches are on, send signal to cube dispenser
  if ((rightSwitch) == 0) {
    //openGate();
    delay(5000);
    //openGate();
    openTrap();
  } else {
    Serial.println(", HOLD");
  }
  delay(200);
}


void openGate() {
  

  for (pos = 15; pos <= 80; pos += 1) {
    servo1.write(pos);
    //servo2.write(80-pos);
    delay(30);
  }
  for (pos = 80; pos >= 15; pos -= 1) {
    servo1.write(pos);
    //servo2.write(180-pos);
    delay(30);
  }

}

void openTrap() {

  
  rightStepper.setSpeed(400);
  leftStepper.setSpeed(400);

  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 4;  // Rotate CW 1/4 turn

  for (i = 0; i <= 2*Steps2Take; i += 1) {
    switch(i%2) {
      case 0:
        rightStepper.step(1);
        break;
      case 1:
        leftStepper.step(-1);
        break;
    }
    //delay(10);
  }

  // Keep open for five seconds
  delay(10000);

  for (i = 0; i <= 2*Steps2Take; i += 1) {
    switch(i%2) {
      case 0:
        rightStepper.step(-1);
        break;
      case 1:
        leftStepper.step(1);
        break;
    }
    //delay(10);
  }

  delay(3000);

  /*
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 4;  // Rotate CW 1/4 turn
  rightStepper.setSpeed(300);
  leftStepper.setSpeed(300); 

  rightStepper.step(-Steps2Take);
  leftStepper.step((Steps2Take));
  delay(1000);

  // HOLD OPEN FOR 5s
  //delay(5000);

  Steps2Take  =  (-1)*STEPS_PER_OUTPUT_REVOLUTION / 4;  // Rotate CCW 1/4 turn  
  rightStepper.step(-Steps2Take);
  leftStepper.step((Steps2Take));
  delay(1000);*/
}

