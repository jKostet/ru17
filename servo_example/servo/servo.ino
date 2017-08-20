#include <Servo.h>

Servo servo1, servo2;

int pos;

void setup() {
  pinMode(1, OUTPUT);
  servo1.attach(14);
  servo2.attach(15);
  pos = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 0; pos <= 180; pos += 1) {
    servo1.write(pos);
    servo2.write(180-pos);
    delay(30);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo1.write(pos);
    servo2.write(180-pos);
    delay(30);
  }
}
