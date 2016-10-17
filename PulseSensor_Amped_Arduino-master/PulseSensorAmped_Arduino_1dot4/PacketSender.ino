/*
 * PacketSender
 * ZigBeeを積んだArduinoにパケットを送信する
 * 
 */

// ひとまとめにしたデータを送信する処理だけ分離(あまりにもわかりにくいから)
 void PacketSender (int Packet) {
  Serial.println( Packet );
 }

