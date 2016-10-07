//assign pulse read pin num.
const int PulseIn = 0;
const int led_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(PulseIn,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pulse = analogRead(PulseIn);
  Serial.println(pulse);
  delay(500);
}
