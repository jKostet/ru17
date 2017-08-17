
/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

// Define the stepper with the correct pins, note that the two middle pins need to be in reverse order
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 4, 6, 5, 7);

int Steps2Take;

void setup() {
  // put your setup code here, to run once:
  // small delay to make sure everything is setup, this shouldn't technically be necessary
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  small_stepper.setSpeed(1);   // SLOWLY Show the 4 step sequence 
  Steps2Take  =  4;  // Rotate CW
  small_stepper.step(Steps2Take);
  delay(2000);

  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 2;  // Rotate CW 1/2 turn
  small_stepper.setSpeed(100);   
  small_stepper.step(Steps2Take);
  delay(1000);

  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION / 2;  // Rotate CCW 1/2 turn  
  small_stepper.setSpeed(700);  // 700 a good max speed??
  small_stepper.step(Steps2Take);
  delay(2000);

}
