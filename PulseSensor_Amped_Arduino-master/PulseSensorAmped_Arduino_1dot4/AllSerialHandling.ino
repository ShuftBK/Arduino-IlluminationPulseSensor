
//////////
/////////  All Serial Handling Code, 
/////////  It's Changeable with the 'serialVisual' variable
/////////  Set it to 'true' or 'false' when it's declared at start of code.  
/////////

// シリアル出力でやることをここが決めていく
void serialOutput(){   // Decide How To Output Serial. 
 // シリアルモニタでASCIIモニタリングを行うときにここが呼び込まれる
 if (serialVisual == true){  
     arduinoSerialMonitorVisual('-', Signal);   // goes to function that makes Serial Monitor Visualizer
 // シリアルモニタリングを行わない場合、この処理が通される
 // processingのパルスモニタはここを通す
 } else{
      sendDataToSerial('S', Signal);     // goes to sendDataToSerial function
 }        
}

// どのようにBPMとIBIのデータを出力するか決める
//  Decides How To OutPut BPM and IBI Data
void serialOutputWhenBeatHappens(){    
 // シリアルモニタでASCIIモニタリングを行うときにここが呼び込まれる
 if (serialVisual == true){            //  Code to Make the Serial Monitor Visualizer Work
  // 以下はASCIIアート作成に用いられる
    Serial.print("*** Heart-Beat Happened *** ");  //ASCII Art Madness
    Serial.print("BPM: ");
    Serial.print(BPM);
    Serial.print("  ");
 // シリアルモニタリングを行わない場合、この処理が通される
 } else{
        sendDataToSerial('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToSerial('Q',IBI);   // send time between beats with a 'Q' prefix
 }   
}


// シリアル出力をprocessingのパルスモニタを使う場合にここを通す
//  Sends Data to Pulse Sensor Processing App, Native Mac App, or Third-party Serial Readers. 
void sendDataToSerial(char symbol, int data ){
    // シンボル(S,B,Qのデータプレフィックスをつけたうえで出力する
    // printlnで改行ありになるためsymbolの時点ではprintlnにしない
    Serial.print(symbol);

    Serial.println(data);                
  }

// シリアルモニタを使ってASCIIアートで可視化する部分
//  Code to Make the Serial Monitor Visualizer Work
void arduinoSerialMonitorVisual(char symbol, int data ){    
  const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 1024;    // sensor maximum, discovered through experiment
  // データをmapで変換し、12段階に分ける
  // それによってこの後出力される内容が変わる
  int sensorReading = data;
  // map the sensor range to a range of 12 options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);

  // switchを用いてデータの大きさによってprint内容を変えASCIIアートを作っていく
  // do something different depending on the 
  // range value:
  switch (range) {
  case 0:     
    Serial.println("");     /////ASCII Art Madness
    break;
  case 1:   
    Serial.println("---");
    break;
  case 2:    
    Serial.println("------");
    break;
  case 3:    
    Serial.println("---------");
    break;
  case 4:   
    Serial.println("------------");
    break;
  case 5:   
    Serial.println("--------------|-");
    break;
  case 6:   
    Serial.println("--------------|---");
    break;
  case 7:   
    Serial.println("--------------|-------");
    break;
  case 8:  
    Serial.println("--------------|----------");
    break;
  case 9:    
    Serial.println("--------------|----------------");
    break;
  case 10:   
    Serial.println("--------------|-------------------");
    break;
  case 11:   
    Serial.println("--------------|-----------------------");
    break;
  
  } 
}


