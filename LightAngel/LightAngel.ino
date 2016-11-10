/*
 * LightAngel
 * Lighting Angel and angle's bow arrow
 */
#include <SoftwareSerial.h>

#define rxPin 10     // rxPin num setup
#define txPin 11   // txPin num setup
SoftwareSerial SignalSerial(rxPin,txPin);

#define Speed 9600 // Serial Speed

// Global Variables
int data;         // marge data
int ArduinoID;    // Get Arduino Identifier
int Mode = 'C';   // use debug only
int BPM;          // Beat Per Minutes
int Pulse;        // Pulse Peak
int data_1;       // up bit data
int data_2;       // under bit data(BPM)

char PrevMode;

char ControlWord = 'C';
char stack;

void setup() {
  // OUTPUT Angel Setup
  pinMode(2,OUTPUT);  // Angel

  // Flag Check
  pinMode(13,OUTPUT);

  Serial.begin(Speed);
  SignalSerial.begin(Speed);
}

void loop() {

  get_word();

  // switch Mode
  switch(ControlWord){
    // All turn off Mode
    case '0':
      digitalWrite(13,LOW);
      turnoffAngel();
      break;

    // All turn on Mode
    case '1':
      digitalWrite(13,LOW);
      turnonAngel();
      break;

    // Pattern Light Mode
    case 'P':
      digitalWrite(13,LOW);
      turnonAngel();
      break;

    // Conbination Light Mode
    case 'C':
      digitalWrite(13,HIGH);
      turnonAngel();
      break;
  }
  
}
