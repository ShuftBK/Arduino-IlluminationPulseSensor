/*
 * LightArrow
 * Lighting Arrows
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
  pinMode(2,OUTPUT);  // Arrow1
  pinMode(3,OUTPUT);  // Arrow2
  pinMode(4,OUTPUT);  // Arrow3
  pinMode(5,OUTPUT);  // Arrow4
  pinMode(6,OUTPUT);  // Arrow5  
  pinMode(7,OUTPUT);  // Arrow6
  pinMode(8,OUTPUT);  // Arrow7

  // Flag Check
  pinMode(9,OUTPUT);

  Serial.begin(Speed);
  SignalSerial.begin(Speed);
}

void loop() {

  get_word();

  // switch Mode
  switch(ControlWord){
    // All turn off Mode
    case '0':
      ModeReset();
      digitalWrite(9,LOW);
      Allturnoff();
      break;

    // All turn on Mode
    case '1':
      ModeReset();
      digitalWrite(9,LOW);
      Allturnon();
      break;

    // Pattern Light Mode
    case 'P':
      ModeReset();
      digitalWrite(9,LOW);
      LightPatternMode();
      break;

    // Conbination Light Mode
    case 'C':
      if(PrevMode != 'C')
        Allturnoff();
      digitalWrite(9,HIGH);
      PrevMode = 'C';
      if(get_data())
        LightPulseArrow();
        Serial.println(data,BIN);
      break;
  }
  
}
