void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // 12 for our special sneaky gate key
  pinMode(12, INPUT_PULLUP);
  // 13 for Wormhole gate top
  pinMode(13, INPUT_PULLUP);

  // Wait for system to power up stable
  delay(3000); 
}

void loop() {
  testSensor();
}

void testSensor() {
  // switches
  int doorSwitch = digitalRead(13);
  int secretSwitch = digitalRead(12);

  // debug print
  Serial.print("DOOR: ");
  Serial.print(doorSwitch);
  Serial.print(", SECRET: ");
  Serial.println(secretSwitch);

  // if either switch is on, send signal to ramp lifter
  // (secret could be buffed with a sneaky sound effect)
  if ((doorSwitch + secretSwitch) < 2) {
    Serial.println(", LIFT RAMP");
    liftRamp();
  } else {
    Serial.println(", HOLD");
  }
  delay(200);
}

void liftRamp() {
  // todo ramp logic, should stay up for maybe 60s + time it takes to lift,
  // then lower automatically.
  // Triggering the sensors should reset the timer,
  // or if the ramp is lowering, to stop and rise.
}

