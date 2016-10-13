/*
 * DataReceiverTest.ino
 * Receive data other devices
 */
 
const int Speed = 9600;

void setup() {
  Serial.begin(Speed);

}

void loop() {
  if (Serial.available())
  Serial.println(Serial.read());
}
