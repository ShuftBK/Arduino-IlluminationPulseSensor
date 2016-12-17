int Mode0 = 3;
int Mode1 = 4;
int out = 13;
bool isMode0 = false;
bool isMode1 = false;

volatile unsigned long times;              // 現在時刻
volatile unsigned long lastUpdateTime;     // 最終更新時刻

void setup() {
  pinMode(Mode0,INPUT);
  pinMode(Mode1,INPUT);
  pinMode(out,OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  int isMode0 = digitalRead(Mode0);
  int isMode1 = digitalRead(Mode1);

  if(isMode0 || isMode1){
    Serial.print("isMode0 : ");
    Serial.println(isMode0);
    Serial.print("isMode1 : ");
    Serial.println(isMode1);
    digitalWrite(out,HIGH);    
  }else
  digitalWrite(out,LOW);    
    
  }

