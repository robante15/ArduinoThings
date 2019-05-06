void setup() {
  Serial.begin(9600);
}
void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  int pulse = pulseIn(A0,HIGH);
  int pulseRate = (60000/pulse);
  Serial.println(pulseRate);
}
