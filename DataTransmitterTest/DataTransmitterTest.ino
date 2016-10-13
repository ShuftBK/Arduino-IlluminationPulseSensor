/*
 * DataTransmitterTest.ino
 * Transmitting data to other Devises
 */

const int Speed = 9600;

void setup() {
  Serial.begin(9600);

}

void loop() {
 int data = Serial.read();
 if(data != -1){
  Serial.print("data : ");
  Serial.println(data);
 }

}
