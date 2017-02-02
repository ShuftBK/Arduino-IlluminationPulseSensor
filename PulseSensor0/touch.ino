void touchinput(){
  if (touchme){
    //データ送信
      _BPM = 60;
      _Pulse = 1;
      DataConvert();
    touchme = false;
  }else{
    //とくに処理なし
  }
  
}

