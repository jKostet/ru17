#include <Stepper.h>

#define STEPS_PER_MOTOR_REVOLUTION 32

#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64

Stepper gate1(STEPS_PER_MOTOR_REVOLUTION, 10, 12, 11, 13);
Stepper gate2(STEPS_PER_MOTOR_REVOLUTION, 6, 8, 7, 9);
Stepper gate3(STEPS_PER_MOTOR_REVOLUTION, 2, 4, 3, 5);

int Steps2Take;
long gateToChoose;

void setup() {
  delay(500);

  Serial.begin(9600);

  randomSeed(analogRead(0));

}

void loop() {
  
  gateToChoose = random(1, 4);

  Serial.println(gateToChoose);

  switch(gateToChoose) {
    case 1:
      openAndCloseGate(gate1);
      break;
    case 2:
      openAndCloseGate(gate2);
      break;
    case 3:
      openAndCloseGate(gate3);
      break;
    default:
      break;
  }

}

void openAndCloseGate(Stepper gate) {
  Steps2Take = STEPS_PER_OUTPUT_REVOLUTION / 4;
  gate.setSpeed(400);
  gate.step(Steps2Take);
  delay(2000);
  gate.step(-Steps2Take);
}

