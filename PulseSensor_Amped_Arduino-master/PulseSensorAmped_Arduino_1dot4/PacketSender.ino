/*
 * PacketSender
 * ZigBeeを積んだArduinoにパケットを送信する
 * 
 */

// ひとまとめにしたデータを送信する処理だけ分離(あまりにもわかりにくいから)
 void PacketSender (int Packet) {
  // ヘッダーを追加
  Serial.print('H');
  Serial.println( Packet );

  // dataの初期化
  PacketData = 0;
  Serial.println(Packet);
 }

