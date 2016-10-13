/*
 * DataTransmitterTest.ino
 * Transmitting data to other Devises
 */

const int Speed = 9600;

void setup() {
  Serial.begin(Speed);
}

void loop() {
  Serial.write('P');
  delay(950);
}
