/*
 * PacketSender
 * ZigBeeを積んだArduinoにパケットを送信する
 * 
 */

// ひとまとめにしたデータを送信する処理だけ分離(あまりにもわかりにくいから)
 void PacketSender (char Up, char Under) {
  // コンソール確認用
  Serial.print('H');
  Serial.print(Up,HEX);
  Serial.println(Under,HEX);
  Serial.println(Up,BIN);
  Serial.println(Under,BIN);

  // ZigBee送信用
  OutSerial.print('H');
  OutSerial.print( Up );
  OutSerial.println( Under );
  
  // dataの初期化
  Upperbit = 0;
  Underbit = 0;
}
