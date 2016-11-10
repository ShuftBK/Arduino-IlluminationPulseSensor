
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/

const bool Arduino_ID = 1;

//#include <TimerOne.h>           // TimerOneﾗｲﾌﾞﾗﾘの読み込み(要ﾗｲﾌﾞﾗﾘｲﾝｽﾄｰﾙ
#include <MsTimer2.h>           // MsTimer2ﾗｲﾌﾞﾗﾘの読み込み(要ﾗｲﾌﾞﾗﾘｲﾝｽﾄｰﾙ
#include <SoftwareSerial.h>   // SoftwareSerialﾗｲﾌﾞﾗﾘの読み込み

// Init SoftwareSerial
// もと = 3,5,6,9,10,11
// Tim2 = 3,11
// Tim1 = 9,10
// つまり = 5,6ですね
SoftwareSerial OutSerial = SoftwareSerial(5,6);

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int ModeUpdate = 7;               // Update Mode 'P' or 'C'
unsigned long times;              // time
unsigned long lastUpdateTime;     // 更新時間関係

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// なぜかDetectHandで定義していたにもかかわらずよみこまなかったのでこちら
volatile boolean DetectedHand = false;

// Setupします
// interruptSetupが今回のｷﾓ
void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  pinMode(ModeUpdate,OUTPUT);       
  Serial.begin(9600);             // we agree to talk fast!
  
  digitalWrite(ModeUpdate,LOW);
  
  OutSerial.begin(9600);
  /*
  // TimerOne割り込みにおける処理
  Timer1.initialize(2);               // 2mSごとに処理を実行する
  Timer1.attachInterrupt(HandRead);   // Timer1のｴﾝﾄﾘｰﾎﾟｲﾝﾄ
  */
  // Timer2割り込みにおける処理
  MsTimer2::set(2, PulseRead);  // 2mSごとにTimerのオンオフ
  MsTimer2::start();            // Timer2のｴﾝﾄﾘｰﾎﾟｲﾝﾄ
}

//  Where the Magic Happens
void loop(){
  //Serial.println(Signal);
  times = millis();
  // QS(センサーが反応しているかどうか)で反応があった場合の処理を以下で行う
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined (BPMおよびIBMが決定されています)
                       // Quantified Self "QS" true when arduino finds a heartbeat
    // LEDをフェードするときに用いるレート(256までなので255で指定)
    // フェードの必要性がないので消していい
    fadeRate = 255;         // Makes the LED Fade Effect Happen
                            // Set 'fadeRate' Variable to 255 to fade LED with pulse
    // フラグ判別にかける
    JudgementFlag();
 
    // QSのフラグをリセットして次回の反応を待つ
    QS = false;                      // reset the Quantified Self flag for next time    
  }
  
    // 時間表示(相対)  
    //Serial.println(times - lastUpdateTime);
  
  if(times - lastUpdateTime >= 5000){
    digitalWrite(ModeUpdate,LOW);
  }
  
  // フェードするLEDのエフェクトを出力するけど、ｼｮｳｼﾞｷｲﾗﾅｲ
  // QSフラグが立たなかった場合にも呼び出される。
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  
  // アップデートサイクル20ms
  delay(20);                             //  take a break
}

// フェードするLEDの部分ですが、実際にフェードしたらシャレになりません
// QSフラグが立たなかったときにも呼び出されているので2msごとに減衰していきます
void ledFadeToBeat(){
    
    // 減衰時の減衰するレートを決める
    fadeRate -= 15;                         //  set LED fade value
    
    // 数値を指定した範囲の中に収める(らしい)
    // constrain(x, a, b);
    // x: 計算対象の値 
    // a: 範囲の下限
    // b: 範囲の上限
    // xがa以上b以下のときはxがそのまま返ります。xがaより小さいときはa、bより大きいときはbが返ります。
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    
    // fadeRateを使ってフェードさせる。
    analogWrite(fadePin,fadeRate);          //  fade LED
}




