/*
 * DataTransmitterTest.ino
 * Transmitting data to other Devises
 */

const int Speed = 9600;

void setup() {
  Serial.begin(Speed);
}

void loop() {
  if(Serial.available()){
  Serial.write(Serial.read());
  }
}
