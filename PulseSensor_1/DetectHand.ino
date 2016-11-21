/* 
 *  DetectHand
 *  もう一方のArduinoで手が検知されているかどうかの判断
 *  検知されていたらHIGHなのでDetectHandがtrue,なければLOWなのでfalse
 */
bool HandRead (){
  if(digitalRead(detect) == HIGH)
  return true;
  else
  return false;
}

