/*
 * PacketSender
 * ZigBeeを積んだArduinoにパケットを送信する
 * 
 */

// ひとまとめにしたデータを送信する処理だけ分離(あまりにもわかりにくいから)
 void Sender (unsigned long Packet) {
  Serial.println( Packet );
 }

