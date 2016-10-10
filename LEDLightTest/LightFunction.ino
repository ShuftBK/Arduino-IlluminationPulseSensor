
int start = 2;

int i = start;
int last = 8;

int lastMode;


void Allturnoff() {
  for(int j = 2; j <= 8; j++)
    digitalWrite(j,LOW);
  last = 8;
  i = start;
}


// change it lightswitch
void light (boolean QS, int Mode) {
  
  if(Mode == 'N'){
  lightMode_N(QS,Mode);
  }
  else if(Mode == 'P'){
  lightMode_P(QS,Mode);
  }
  else{
    Allturnoff();
  }
  lastMode = Mode;
  Serial.println(QS);
}

// lightmode_p
void lightMode_P (int QS, int Mode){
  if(lastMode == Mode){
    digitalWrite(last,LOW);
    digitalWrite(i,HIGH);
    last = i;
    ++i;
    if(i == 10){
      Allturnoff();
      i = start; // reset
    }
  }else{
    Allturnoff();
    i = start;
  }
}



//lightmode_n

void lightMode_N (int QS, int Mode){
  if(lastMode == Mode){
    digitalWrite(i,HIGH);
    ++i;
    if(i == 10){
      Allturnoff();
      i = start;
    }
  }else{
    Allturnoff();
    i = start;
  }
}


