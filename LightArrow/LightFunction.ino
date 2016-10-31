/*
 * LightFunction
 * Lighting Funtions
 */

const int reset_start = 2;    // stert pin num
const int reset_end = 9;      // end pin num

int NextPosition = 2;   // Next Light LED Num
int PrevPosition = 0;   // Now Light LED Num 

// All turn off
void Allturnoff() {
  for(int j = reset_start; j <= reset_end; j++)
    digitalWrite(j,LOW);
}

// All turn on
void Allturnon() {
  for (int j = reset_start; j <= reset_end; j++)
    digitalWrite(j,HIGH);
}

void ModeReset() {
  NextPosition = reset_start;
  PrevPosition = 0;
  times = 0;
  Allturnoff();
  lastPatternTime = 0;
  lastCombinationTime = 0;
}

// Pulse Read Mode
// if pulse receive, use this function
void LightPulseArrow(){
  digitalWrite(PrevPosition,LOW);
  digitalWrite(NextPosition,HIGH);
  PrevPosition = NextPosition;
  ++NextPosition;
  if(PrevPosition >= reset_end){
  NextPosition = reset_start;
  Allturnoff();
  }
  lastCombinationTime = times;
}

void LightPatternMode() {
  if(times - lastPatternTime >= 1000){
    digitalWrite(NextPosition,HIGH);
    PrevPosition = NextPosition;
    ++NextPosition;
    lastPatternTime = times;
  }
  if(PrevPosition >= reset_end){
    NextPosition = reset_start;
    Allturnoff();
  }
}

