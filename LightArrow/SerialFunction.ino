
bool get_word(){
  while(Serial.available() > 0)
  stack = Serial.read();

  if(stack != ControlWord){
    ControlWord = stack;
    return true;
  }else{
    return false;
  }
  
}

bool get_data(){
  if(Serial.available() >= sizeof(byte)+sizeof(int))
  if(Serial.read()=='H'){
    data_1 = Serial.read();
    data_2 = Serial.read();
    
    Pulse = bitRead(data_1,1);
    ArduinoID = bitRead(data_1,4);
    BPM = data_2;
    
    data = makeWord(data_1,data_2);

    // Pulse Read Mode
    if(Mode == 'C'){
      if (bitRead(data_1,1) == 1)
        LightPulseArrow();
    //if (bitRead(data_1,1) == 0)
      //LeavePulseArrow();
    }
      
    return true;
  }
  return false;
}
