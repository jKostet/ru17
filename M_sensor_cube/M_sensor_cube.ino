void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);


  // Wait for system to power up stable
  delay(3000); 
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
    Serial.println(", DROP CUBE");
    dropCube();
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
