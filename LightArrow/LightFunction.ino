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
  // 1秒立ったらの処理(簡易実装)
  if(times - lastPatternTime >= 1000){
    digitalWrite(NextPosition,HIGH);
    PrevPosition = NextPosition;
    ++NextPosition;
    lastPatternTime = times;
  }
  // 矢2本目の時に1本目消灯
  if(PrevPosition == 3)
    digitalWrite(2,LOW);
  // 矢3本目の時に2本目消灯
  if(PrevPosition == 4)
    digitalWrite(3,LOW);
  // 最後まで行ったらｶｳﾝﾀｰﾘｾｯﾄ
  if(PrevPosition >= reset_end)
    NextPosition = reset_start;
}

