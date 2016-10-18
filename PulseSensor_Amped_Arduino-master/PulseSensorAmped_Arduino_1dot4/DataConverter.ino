/*
 * DataReader
 * 各種データを送信前にチェックしまとめ指定フォーマットへ変換する
 * 
 */

int PacketData = 0;

boolean _Pulse = false;
int _BPM = 0;
int _ID = 0;


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
    Serial.println("HOGE");
    DataMerge();
  }
}

// JudgementFlagでフラグの判断後に、データをまとめる
// 即データConvertに投げる
void DataMerge () {
  // BPMを格納
  _BPM = BPM;
  _Pulse = Pulse;
  _ID = Arduino_ID;
  
  DataConvert();
}

// データを一度バイナリ化しパケットにして送信する。
// データをまとめて送信時に困らないようにするためにある
void DataConvert (){
  
  PacketData += _BPM;

  // Pulse値を書き込み
  bitWrite(PacketData,9,_Pulse);

  // Arduinoの固有IDを書き込み
  bitWrite(PacketData,12,_ID);

  PacketSender(PacketData);
}

