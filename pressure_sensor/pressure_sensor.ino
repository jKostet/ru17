void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);


  // Wait for system to power up stable
  delay(3000); 
}

void loop() {
  

  
  int rightSwitch = digitalRead(13);
  int leftSwitch = digitalRead(12);
  Serial.print("RIGHT: ");
  Serial.print(rightSwitch);
  Serial.print(", LEFT: ");
  Serial.println(leftSwitch);
  //Serial.println(buttonStatus);
  if ((rightSwitch + leftSwitch) == 0) {
    Serial.println(", DROP CUBE");
  } else {
    Serial.println(", HOLD");
  }
  delay(200);
}
