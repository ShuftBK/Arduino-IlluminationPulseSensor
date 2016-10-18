int data;
byte data_1,data_2;

void setup(){
  Serial.begin(9600);
  
}

void loop(){
  if(get_data())
    Serial.println(data);
}

bool get_data(){
  if(Serial.available() >= sizeof(byte)+sizeof(int))
  if(Serial.read()=='H'){
    data_1 =Serial.read();
    data_2 =Serial.read();
    data = makeWord(data_1,data_2);
    return true;
  }
  return false;
}
