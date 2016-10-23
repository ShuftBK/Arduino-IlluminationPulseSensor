/*
 * LightArrow
 * Lighting Arrows
 */
#include <SoftwareSerial.h>

#define rxPin = 9;    // rxPin num setup
#define txPin = 10;   // txPin num setup
SoftwareSerial SignalSerial(rxPin,txPin);

#define Speed = 9600; // Serial Speed

// Global Variables
int data, ArduinoID, Mode = 'N', BPM, Pulse, data_1, data_2;

void setup() {
  // OUTPUT Angel Setup
  pinMode(2,OUTPUT);  // Angel
  pinMode(3,OUTPUT);  // bow&arrow(Normal)
  pinMode(4,OUTPUT);  // bow&arrow(Sensor)

  // Flag Check
  pinMode(9,OUTPUT);

  Serial.begin(Speed);
}

void loop() {
  /*
  if(SignalSerial.available()){
    Mode = Serial.read();
    break;
  }
  */
  if(get_data())
    Serial.println(data);
}

bool get_data(){
  if(Serial.available() >= sizeof(byte)+sizeof(int))
  if(Serial.read()=='H'){
    data_1 =Serial.read();
    data_2 =Serial.read();
    data = makeWord(data_1,data_2);
    if (bitRead(data_1,1)){
      
    }
    return true;
  }
  return false;
}

