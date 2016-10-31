/*
 * LightFunction
 * Lighting Funtions
 */

const int reset_start = 2;    // stert pin num
const int reset_end = 8;      // end pin num

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
}

// Pulse Read Mode
// if pulse receive, use this function
void LightPulseArrow(){
  // Allturnoff();
  digitalWrite(NextPosition,HIGH);
  PrevPosition = NextPosition;
  ++NextPosition;
  if(PrevPosition >= reset_end)
  NextPosition = reset_start;
}

void LeavePulseArrow() {
  
}

void LightPatternMode() {
  
}
