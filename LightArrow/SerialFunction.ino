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
  if(SignalSerial.available() >= sizeof(byte)+sizeof(int))
  if(SignalSerial.read()=='H'){
    data_1 = SignalSerial.read();
    data_2 = SignalSerial.read();
    
    Pulse = bitRead(data_1,1);
    ArduinoID = bitRead(data_1,4);
    BPM = data_2;
    Serial.println(data_1,BIN);
    data = makeWord(data_1,data_2);
    
    return true;
  }
  return false;
}

