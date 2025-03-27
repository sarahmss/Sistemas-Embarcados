void setup() {
  Serial.begin(2000000);
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);
}
