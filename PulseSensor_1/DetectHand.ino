/* 
 *  DetectHand
 *  もう一方のArduinoで手が検知されているかどうかの判断
 *  検知されていたらHIGHなのでDetectHandがtrue,なければLOWなのでfalse
 */
void HandRead (){
  if(digitalRead(7) == HIGH)
  DetectedHand = true;
  else
  DetectedHand = false;
}

