int data;
byte data_1,data_2;

void setup(){
  Serial.begin(9600);
  pinMode(2,OUTPUT);
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
    if (bitRead(data_1,1)){
    digitalWrite(2,HIGH);
    delay(10);
    digitalWrite(2,LOW);
    }
    return true;
  }
  return false;
}

