//オブジェ側サンプルプログラム

//注意!!!
//オブジェ側の処理ではdelay関数の使用は減禁!
//delay関数は処理が止まるのでモード切替が遅れる原因になる
//delay関数の代替としてd_delay関数を実装済み
//また、自作関数を作成する場合にその関数内で遅延処理を行う場合は
//必ずd_delay関数を用いたリターンフラグを設けること


/*------d_delay関数の使い方--------
 <all_off関数、all_on関数、pattern関数、combination関数内での記述>
  if(d_delay(遅延時間[ms]))
    break;

<d_delay関数を用いたリターンフラグの設け方>
  if(d_delay(遅延時間[ms]))
    return true;
  //なんらかの処理
  return false//最後にfalseをリターン
  //また、その自作関数の引数をbreakの条件判別に利用する
-------------------------------*/



char controlword;//現在のモードを格納する変数
char stack;//シリアルデータを一時保管する為の変数
void setup(){
  Serial.begin(9600);//シリアルポートの通信速度を9600bpsに設定  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop(){
  get_word();//モード命令を取得
  
  switch(controlword){
    case '0':
      all_off();
      break;
    case '1':
      all_on();
      break;
    case 'P':
      pattern();
      break;
    case 'C':
      combination();
      break;
    default:
      break;
  }
}

void all_off(){
  //全消灯の処理を記述

  //以下サンプルプログラム
  digitalWrite(13,LOW);
  //サンプルプログラム終了
  
  //注意:この関数内では遅延処理を行わない!!!
}


void all_on(){
  //全点灯の処理を記述

  //以下サンプルプログラム
  digitalWrite(13,HIGH);
  //サンプルプログラム終了
  
  //注意:この関数内では遅延処理を行わない!!!
}

void pattern(){
  all_off();//モード変更のタイミングによっては出力が意図せぬ状態に
            //なっている場合があるので、出力の状態を初期化(全消灯)にする
  
  //パターン点灯の処理を記述
  
  //以下サンプルプログラム
  for(int i=0;i<=1000;i++){//ループ回数は多め(数百回〜数千回)でも無問題
      digitalWrite(13,HIGH);
      
      if(d_delay(1000))//遅延処理
        break;

      digitalWrite(13,LOW);

      if(d_delay(1000))//遅延処理
        break;
  }
  //サンプルプログラム終了
}

void combination(){
  //連携モードの処理を記述
  //連携モードに関係のないオブジェは記述する必要なし
}


bool d_delay(unsigned long delay_time){//delay関数の代替
  unsigned long start_time;
  start_time = millis();//d_delay関数の実行が開始された時間を記憶
  while(millis() <= start_time + delay_time){//指定時間だけ遅延させる
  if(get_word())
    return true;//モードが変更された場合、trueを返し、遅延処理を中止  
  }
  return false;//処理が完了(モードが変更されなかった)場合、falseを返す
}

bool get_word(){//モード命令(シリアルデータ)を取得する為の関数
  while(Serial.available() > 0)//最後に受信したデータだけを
    stack = Serial.read();//stackに格納する処理
  if(stack != controlword&&stack != -1){
      controlword=stack;//モード状態を記憶している変数を書き換える
      return true;//モードが変更された場合、trueを返す
    }
  else
    return false;//モードが変更されなかった場合、falseを返す
}

