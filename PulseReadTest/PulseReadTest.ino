/*
 * PulseReadTest.ino
 * Pulse reading test program.
 * 
 * [How to use]
 * 1. Compile and Write to arduino.
 * 2. Open Serial Monitor or Serial Plotor
 */

//assign pulse read pin num.
const int PulseIn = 0;

void setup() {
  pinMode(PulseIn,INPUT);
  Serial.begin(9600);
}

void loop() {
  int pulse = analogRead(PulseIn);
  Serial.println(pulse);
  delay(10);
}
