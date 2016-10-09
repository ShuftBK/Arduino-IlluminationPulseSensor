/*
 * volatile修飾子を使うことによって割り込み時に変数が変化したときにその変化を受け取る
 * わかったらいろいろ書く
 * 
 * 
 * 
 */


volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM

// ここの処理がミソ
// これより下のコードはすべてArduinoというよりAVRとしての機能をフル活用しているため、要解読。
// 割り込みで2msの読み込みをすることによってloopに縛られないセンサーの読み取りが可能
// レジスタによる制御のせいでわけわかめ

// ループの速度はTCCR2BとOCR2Aで調整する。
// TCCR2Bはプレスケーラの値で、クロックを何分割するかを決める。
void interruptSetup(){     
  // Initializes Timer2 to throw an interrupt every 2mS.

/* 
 *  CTCモードでの使用(OCR2A)
 *  
 *  CS = 110 : 分周比256
 *  出力するPWMの周波数 : f = 16MHz / ( 256 * 510 ) = 122.54901960784313725490196078431 [Hz]
 *  
 */

  // タイマ/カウンタ2制御レジスタA
  // 0x02 = 0000 0010
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  
  // タイマ/カウンタ2制御レジスタB
  // 0x06 = 0000 0110
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER 


  // 8ビット比較レジスタ
  // 11番ピン用。analogWrite()で指定したデューティ比を保持します。
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  // 割り込みマスク
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A

  // グローバル割り込みを許可する。
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED      
} 


// ISRを使って割り込みベクタの登録を行う
// TIMER2_COMPA_vectはタイマ/カウンタ2(TCNT2)と比較レジスタ(OCR2A)が同じ値になったときに起動される割り込みハンドラです。
// PWMでのタイミング取得

// これはタイマー2の割り込みルーチンです
// タイマー2が2msごとに毎回呼び出されるのを確かめてください
// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE. 
// Timer 2 makes sure that we take a reading every 2 miliseconds
ISR(TIMER2_COMPA_vect){                         // triggered when Timer2 counts to 124

  
  /*
   * cli();で割り込み禁止処理
   * 以下sei();まで割り込み禁止で処理を行っていく(つまり最後かfirstbeatのところまで）
   * おそらく処理中に変数が変わっては困るため
   */
  cli();                                      // disable interrupts while we do this

  /*
   * ここでようやく真打ち登場
   * 以下からパルスの処理が始まる
   */
  Signal = analogRead(pulsePin);              // read the Pulse Sensor 
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

    //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                        // T is the trough
      T = Signal;                         // keep track of lowest point in pulse wave 
    }
  }

  if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
    P = Signal;                             // P is the peak
  }                                        // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250){                                   // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
      Pulse = true;                               // set the Pulse flag when we think there is a pulse
      digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
      lastBeatTime = sampleCounter;               // keep track of time for next pulse

      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
        secondBeat = false;                  // clear secondBeat flag
        for(int i=0; i<=9; i++){             // seed the running total to get a realisitic BPM at startup
          rate[i] = IBI;                      
        }
      }

      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
        firstBeat = false;                   // clear firstBeat flag
        secondBeat = true;                   // set the second beat flag
          // グローバル割り込みを許可する。
        sei();                               // enable interrupts again
        return;                              // IBI value is unreliable so discard it
      }   


      // keep a running total of the last 10 IBI values
      word runningTotal = 0;                  // clear the runningTotal variable    

      for(int i=0; i<=8; i++){                // shift data in the rate array
        rate[i] = rate[i+1];                  // and drop the oldest IBI value 
        runningTotal += rate[i];              // add up the 9 oldest IBI values
      }

      rate[9] = IBI;                          // add the latest IBI to the rate array
      runningTotal += rate[9];                // add the latest IBI to runningTotal
      runningTotal /= 10;                     // average the last 10 IBI values 
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      QS = true;                              // set Quantified Self flag 
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }                       
  }

  if (Signal < thresh && Pulse == true){   // when the values are going down, the beat is over
    digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
    Pulse = false;                         // reset the Pulse flag so we can do it again
    amp = P - T;                           // get amplitude of the pulse wave
    thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
    P = thresh;                            // reset these for next time
    T = thresh;
  }

  if (N > 2500){                           // if 2.5 seconds go by without a beat
    thresh = 512;                          // set thresh default
    P = 512;                               // set P default
    T = 512;                               // set T default
    lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
    firstBeat = true;                      // set these to avoid noise
    secondBeat = false;                    // when we get the heartbeat back
  }
  // グローバル割り込みを許可してどねどね
  sei();                                   // enable interrupts when youre done!
}// end isr





