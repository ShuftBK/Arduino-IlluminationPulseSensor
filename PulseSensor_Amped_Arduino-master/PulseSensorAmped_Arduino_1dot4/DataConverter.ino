/*
 * DataReader
 * 各種データを送信前にチェックしまとめ指定フォーマットへ変換する
 * 
 */

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
}

// JudgementFlagでフラグの判断後に、データをまとめる
// 即データConvertに投げる
void DataMerge () {
  
}

// データを一度バイナリ化しパケットにして送信する。
// データをまとめて送信時に困らないようにするためにある
void DataConvert ( char prefix, int data ){

  
}

