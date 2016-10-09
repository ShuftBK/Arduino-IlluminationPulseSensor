

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
  pinMode(11,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int readbool;
  readbool = Serial.read();

  Serial.println(readbool);

  light(QS, Mode);

  
  if(readbool != -1){

    switch(readbool){
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

  delay(950);
}