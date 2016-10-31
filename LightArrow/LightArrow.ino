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
unsigned long times;
unsigned long lastPatternTime = 0;
unsigned long lastCombinationTime = 0;

char PrevMode;

char ControlWord = 'C';
char stack;

void setup() {
  // OUTPUT Arrow and Bow Setup
  pinMode(2,OUTPUT);  // Arrow1(Draw a bow)
  pinMode(3,OUTPUT);  // Arrow2(Normal bow)
  pinMode(4,OUTPUT);  // Arrow3
  pinMode(5,OUTPUT);  // Arrow4
  pinMode(6,OUTPUT);  // Arrow5
  pinMode(7,OUTPUT);  // Arrow6
  pinMode(8,OUTPUT);  // Arrow7(shot heart)

  // Flag Check
  pinMode(9,OUTPUT);

  Serial.begin(Speed);
  SignalSerial.begin(Speed);
}

void loop() {

  get_word();
  times = millis();
  
  if(PrevMode != ControlWord)
  ModeReset();
  
  PrevMode = ControlWord;
  
  // switch Mode
  switch(ControlWord){
    // All turn off Mode
    case '0':
      digitalWrite(9,LOW);
      break;
  
    // All turn on Mode
    case '1':
      digitalWrite(9,LOW);
      Allturnon();
      break;

    // Pattern Light Mode
    case 'P':
      digitalWrite(9,LOW);
      LightPatternMode();
      break;

    // Conbination Light Mode
    case 'C':
      digitalWrite(9,HIGH);
      PrevMode = 'C';
      if(get_data())
        LightPulseArrow();
        Serial.println(data,BIN);
      break;
  }
  
}

