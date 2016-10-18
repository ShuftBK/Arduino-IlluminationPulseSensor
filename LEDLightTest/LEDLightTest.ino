#include <SoftwareSerial.h>

const int rxPin = 10;    // SoftwareSerial RX
const int txPin = 11;   // SoftwareSerial TX

SoftwareSerial softSerial(rxPin,txPin);

const int Speed = 9600;

volatile boolean QS = false;

int Mode = 'D';

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

  // QS Flag
  pinMode(9,OUTPUT);

  Serial.begin(Speed);

  softSerial.begin(Speed);
}

void loop() {
  
  int SelectMode;
  //SelectMode = Serial.read();

  //Serial.println(SelectMode);

  if(softSerial.available()){
    SelectMode = softSerial.read();
    //Serial.println(softSerial.read());
  
  if(SelectMode != -1){

    switch(SelectMode){
      case 'D':            // DebugMode
        QS = false;
        Mode = 'D';
        digitalWrite(11,LOW);
        break;
      case 'N':            // NormalMode
        QS = true;
            Mode = 'N';
        digitalWrite(11,HIGH);
        break;
      case 'P':            // PulseMode
        QS = true;
            Mode = 'P';
        digitalWrite(11,HIGH);
        break;
    }
  }
  else {
  }
  light(QS, Mode);
  }
  
}
