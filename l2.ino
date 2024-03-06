void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT); // right forward
  pinMode(3, OUTPUT); // right backward
  pinMode(4, OUTPUT); // left forward
  pinMode(5, OUTPUT); // left backward

  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  analogWrite(6, 255);
  analogWrite(9, 100);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(1000);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);
}
