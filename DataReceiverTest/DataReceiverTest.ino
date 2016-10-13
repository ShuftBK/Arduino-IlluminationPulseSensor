/*
 * DataReceiverTest.ino
 * Receive data other devices
 */

#include <SoftwareSerial.h>

const int rxPin = 9;    // SoftwareSerial RX
const int txPin = 10;   // SoftwareSerial TX

SoftwareSerial softSerial(rxPin,txPin);
 
const int Speed = 9600;

void setup() {
  Serial.begin(Speed);
  softSerial.begin(Speed);
}

void loop() {
  if (softSerial.available()){
  Serial.println(softSerial.read());
  softSerial.println(Serial.read());
  }
}
