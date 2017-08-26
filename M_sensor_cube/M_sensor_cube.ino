#include <Servo.h>

long delaymillis, timer;

Servo cubeservo;

int pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  
  pinMode(1, OUTPUT);
  cubeservo.attach(14); // analog pin 0

  // ms to delay after each iteration of the loop
  delaymillis = 200;

  // timer for the cube dispenser
  timer = 0;

  // initialize servo position
  pos = 0;

  // Wait for system to power up stable
  delay(3000); 
}

void loop() {
  testSensor();
  delay(delaymillis);
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
  if ((rightSwitch + leftSwitch) < 2) {
    Serial.println(", DROP CUBE");
    dropCube();
  } else {
    Serial.println(", HOLD");
    // robot is not on sensor, set timer to 0
    timer = 0;
  }
}

void dropCube() {
  // some timer so cubes aren't dispensed all at once,
  // as standing on the sensor will keep triggering it
  // should probably dispense one every 15s?
  // if timer < delaymillis dispense cube, after that timer += delaymillis, timer = timer%(15000/delaymillis)
  if (timer < delaymillis) {
    moveServo(cubeservo, 40, 130, 10);
  }
  timer += delaymillis;
  timer = timer % 15000;
  Serial.println(timer);
}

void moveServo(Servo servo, int min_pos, int max_pos, int delaytime) {
  //Serial.println("MOVE SERVO");
  for (pos = min_pos; pos <= max_pos; pos += 1) {
    servo.write(pos);
    delay(10);
  }
  delay(delaytime);
  for (pos = max_pos; pos >= min_pos; pos -= 1) {
    servo.write(pos);
    delay(10);
  }
}
