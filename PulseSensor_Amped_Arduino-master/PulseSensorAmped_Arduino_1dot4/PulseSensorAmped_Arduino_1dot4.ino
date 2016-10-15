
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

#include <MsTimer2.h> // MsTimer2ライブラリの読み込み(要ライブラリインストール

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


volatile int rate[10];                    // array to hold last ten IBI values
// パルスのタイミングを決定するために使用
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
// IBIを見つけるために使用
volatile unsigned long lastBeatTime = 0;           // used to find IBI
// ピーク値を見つけるために使用
volatile int P =512;                      // used to find peak in pulse wave, seeded
// 脈拍の谷の部分を見つけるために使用
volatile int T = 512;                     // used to find trough in pulse wave, seeded
// 鼓動の瞬間をすぐさま見つけるために使用(?)閾値(?)
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
// パルス波形の振幅を保持するために使用
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM(Google翻訳:我々は合理的なBPMで始まるので、レート・アレイを播種するために使用)
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM

void TimerSet () {
    MsTimer2::stop();                                      // disable interrupts while we do this

  /*
   * ここでようやく真打ち登場
   * 以下からパルスの処理が始まる
   */
  Signal = analogRead(pulsePin);              // read the Pulse Sensor 
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

  // 波のピークと谷を見つける(Tを谷の値とする)
  //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                        // T is the trough
      T = Signal;                         // keep track of lowest point in pulse wave 
    }
  }
  
  // シグナルが現在取得しているピーク値より大きいときはその値がピーク値となる。
  // Signalよりthreshが小さくシグナルがピーク値より大きいとき
  if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
    P = Signal;                             // P is the peak
  }                                        // keep track of highest point in pulse wave

  // いい感じに鼓動を検出してほげる
  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250){                                   // avoid high frequency noise(高周波ノイズを回避します)
    
    // センサーが何も感知していなくて
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
      // センサーがパルスを検出している状態とする。
      Pulse = true;                               // set the Pulse flag when we think there is a pulse
      // 検出したのでLED(blinkPin)を光らせる
      digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
      // ミリ秒でビート間の時間を測定
      // 現在の時間から、最後にパルスを検出した時間の差を取り、IBI(インターバル)を求める
      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
      // 現在の時間を最後にパルスを検出した時刻とし、次のパルスの検出に備える
      lastBeatTime = sampleCounter;               // keep track of time for next pulse

      // if(secondBeat == true)と同じ動作するので、ここC++の仕様です
      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
        // secondBeatのフラグをfalseに戻す
        secondBeat = false;                  // clear secondBeat flag
        // IBI値をrate配列に格納する
        for(int i=0; i<=9; i++){             // seed the running total to get a realisitic BPM at startup(Google翻訳:起動時に現実的なBPMを得るために累計をシード)
          rate[i] = IBI;                      
        }
      }

      // if(firstBeat == true)と同じ動作するので、ここC++の仕様です
      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
        // firstBeatのフラグをfalseに戻す
        firstBeat = false;                   // clear firstBeat flag
        // 次の鼓動をsecondBeatとするためにtrueにする
        secondBeat = true;                   // set the second beat flag
        // グローバル割り込みを許可する。
        MsTimer2::start();                               // enable interrupts again
        // 返した
        return;                              // IBI value is unreliable so discard it(Google翻訳:IBI値の信頼性が低いので、それを捨てます)
      }   

      // 最後10回のトータルIBI値を保つ
      // keep a running total of the last 10 IBI values
      word runningTotal = 0;                  // clear the runningTotal variable    
      
      // IBI値をrate配列内でシフトする
      for(int i=0; i<=8; i++){                // shift data in the rate array
        // 古いものを捨てて新しいのに上書き
        rate[i] = rate[i+1];                  // and drop the oldest IBI value 
        // 9つ分の古いIBI値をrunningTotalにプラスイコールする
        runningTotal += rate[i];              // add up the 9 oldest IBI values
      }

      // rate[9]が最新のIBI値であるように格納する
      rate[9] = IBI;                          // add the latest IBI to the rate array
      // 最新のIBI値をrunningTotalにプラスイコールする
      runningTotal += rate[9];                // add the latest IBI to runningTotal
      // runningTotalの平均を出す
      runningTotal /= 10;                     // average the last 10 IBI values 
      /*
       *  １分間の平均心拍数、つまりBPM(Beat Per Minute)を算出する
       *  1min = 60sec
       *  1sec = 1000msec
       *  1min = 60 sec * 1000msec = 60000msec
       */
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      // きちんと値が出そろったのでQSのフラグを立てる
      QS = true;                              // set Quantified Self flag 
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }                       
  }

  // センサーが感知しなくなったとき(詳しくは翻訳読んで)
  if (Signal < thresh && Pulse == true){   // when the values are going down, the beat is over(Google翻訳:値が下がり続けているときに、ビートは終わりました)
    // blinkPinをLOWにする
    digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
    // Pulseフラグを折る
    Pulse = false;                         // reset the Pulse flag so we can do it again
    // amp値をピーク値から脈拍の谷の値で差を取る
    amp = P - T;                           // get amplitude of the pulse wave
    // thresh値を振幅の半分でとる
    thresh = amp/2 + T;                    // set thresh at 50% of the amplitude(Google翻訳:振幅の50％でTHRESHを設定します)
    // 次回に備えてthresh値で上書きリセットしていく
    P = thresh;                            // reset these for next time
    T = thresh;
  }

  // 2500msecの間心拍を検出しなかったとき
  if (N > 2500){                           // if 2.5 seconds go by without a beat(Google翻訳:2.5秒はビートなしで行く場合)
    // 各値をデフォルト値へ戻す
    thresh = 512;                          // set thresh default
    P = 512;                               // set P default
    T = 512;                               // set T default
    // 現在の時間を最後にパルスを検出した時刻とし、次のパルスの検出に備える
    lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
    // 再び心拍を検出するときに備えノイズを避けるために初期値とする。
    firstBeat = true;                      // set these to avoid noise
    secondBeat = false;                    // when we get the heartbeat back(Google翻訳:我々は戻ってハートビートを取得するときに、これらのノイズを避けるために設定)
  }
  // グローバル割り込みを許可してどねどね
  MsTimer2::start();
}

// Setupします
// interruptSetupが今回のｷﾓ
void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(9600);             // we agree to talk fast!

  // センサーで得る情報はここから始まる。
  // Interrupt.inoに飛ぶ
  //interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 

  MsTimer2::set(2, TimerSet); // 2mSごとにTimerのオンオフ
  MsTimer2::start();

   // この辺の処理は特に見なくてもよい
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   
}


//  Where the Magic Happens
// Magicのせいで中身が読めないのつらい(# ﾟДﾟ)
void loop(){
  
    serialOutput() ; // Signalを表示するためにをAllSerialHandling.inoに投げる(解析フェーズではない)      

  // QS(センサーが反応しているかどうか)で反応があった場合の処理を以下で行う
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined (BPMおよびIBMが決定されています)
                       // Quantified Self "QS" true when arduino finds a heartbeat

        // LEDをフェードするときに用いるレート(256までなので255で指定)
        // フェードの必要性がないので消していい
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse

        // BPMとIBIを表示するためにAllSerialHandling.inoに投げる
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     

        // QSのフラグをリセットして次回の反応を待つ
        QS = false;                      // reset the Quantified Self flag for next time    
  }

  // フェードするLEDのエフェクトを出力するけど、ｼｮｳｼﾞｷｲﾗﾅｲ
  // QSフラグが立たなかった場合にも呼び出される。
  //ledFadeToBeat();                      // Makes the LED Fade Effect Happen 

  // フラグ判別にかける
  JudgementFlag();
  
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




