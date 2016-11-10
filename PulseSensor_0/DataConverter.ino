/*
 * DataReader
 * 各種データを送信前にチェックしまとめ指定フォーマットへ変換する
 * 
 */

char Upperbit = 0;
char Underbit = 0;

boolean _Pulse = 0;
int _BPM = 0;

// パルスが読み込まれているタイミングで呼び込まれる
// これ自体は読み取った値に対して本当にそれが有効であるかを判断させ、モードを確定する
// 要は脈拍が異常値をたたき出していないかと、ちゃんと手を認識しているかを判別する
void JudgementFlag () {
  // テストで呼び込まれていればserialprintする
  
  Serial.print("BPM     :");
  Serial.print(BPM);
  Serial.print("Signal  :");
  Serial.print(Signal);
  Serial.print("IBI     :");
  Serial.print(IBI);
  Serial.print("Pulse   :");
  Serial.print(Pulse);
  Serial.print("QS      :");
  Serial.println(QS);  
  
  if (BPM >= 40 && BPM <= 127) {
    digitalWrite(ModeUpdate,HIGH);
    lastUpdateTime = times;
    HandRead();
    DataMerge();
  }
}

// JudgementFlagでフラグの判断後に、データをまとめる
// 即データConvertに投げる
void DataMerge () {
  // BPMを格納
  _BPM = BPM;
  _Pulse = QS;
  
  DataConvert();
}

// データを一度バイナリ化しパケットにして送信する。
// データをまとめて送信時に困らないようにするためにある
void DataConvert (){
  
  Underbit = _BPM;
  
  // Pulse値を書き込み
  bitWrite(Upperbit,0,1);
  
  // Arduinoの固有IDを書き込み
  bitWrite(Upperbit,3,Arduino_ID);

  // 検知してるかどうかのｱﾚ
  if(DetectedHand == true)
    bitWrite(Upperbit,4,1);
  else
    bitWrite(Upperbit,4,0);
    
  PacketSender(Upperbit,Underbit);
}
