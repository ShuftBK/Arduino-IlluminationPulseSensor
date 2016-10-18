# Arduino-IlluminationPulseSensor
東舞鶴駅イルミネーション事業用プログラム(電気情報工学実験ⅡB)

* AVRの仕様書421ﾍﾟｰｼﾞってマジか…
* たまーに出てくるC++に困惑しか感じられない

---

# ﾘﾎﾟｼﾞﾄﾘ構成  
* DataReceiverTest
 * DataReceiverTest.ino
* DataTransmitterTest
 * DataTransmitterTest.ino
* LEDLightTest
 * LEDLightTest.ino
 * LightFunction.ino
* PulseReadTest  
 * PulseReadTest.ino  
 センサー動作テスト用プログラム
* PulseSensor_Amped_Arduino-master
 * PulseSensorAmped_Arduino_1dot4
  * AllSerialHandling.ino

---

## 制御内容
### オブジェ1(angel,arrow)
* 7つの矢を飛ばすために、１周期ごとにフラグ(Pulse[Boolean])をセンサー側からオブジェ側へ送信する。なお、表示する矢は基本的に一本ずつ光らせる。パターンを以下に示す。
  1. 光らせ方はすでに光っている一本を消して次の一本をつける場合
  2. 消さずに一本ずつつける場合(7本光ったら一度すべて消す)
* エンジェルのハートは光らせるために、１周期ごとにフラグ(Pulse[Boolean])をセンサー側からオブジェ側へ送信する。
* 脈拍センサーに触れていない時は、スタンバイモードであらかじめプログラムしている点灯方法を用いる。

## 定義された変数について
### センサー側

Variable Name   | Type    |  description
----------------|---------|-----------------------
Signal          | Int     | AnalogInputで得た値。500Hz(2ms)ごとに更新される。
BPM             | Int     | 1分間あたりの脈拍値。
IBI             | Int     | 鼓動と鼓動のｲﾝﾀｰﾊﾞﾙの値。
Pulse           | Boolean | センサーが感知したらtrue,それ以外はfalseを返す
QS              | Boolean | BPMが更新されたりパルスが更新されるたびにtrueを返す。リセット時に使用する。

### オブジェ側  
**以下未確定のため編集領域として置いておく**  

Variable| Type    | data | description
--------|---------|------|-----------------------
BPM     | Int     | 8bit | 1分間あたりの脈拍値。
Pulse   | Boolean | 1bit | センサーが感知したらtrue,それ以外はfalseを返す
Mode    | Int     | 2bit |

## 送信データ仕様

* 送信データが2byteのためint,unsigned int,wordの型のうちどれかを使います(未確定)

bit       | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 
----------|------|------|------|------|------|-------|-------|-----
上位8bit  |      |      |      |      | Object0 | Mode1 | Mode0 | Pulse0 
下位8bit  | BPM7 | BPM6 | BPM5 | BPM4 | BPM3 | BPM2 | BPM1 | BPM0 

* Mode : ﾓｰﾄﾞを指定して送信する(内容は別途規定)
* Pulse : センサーの反応値
* BPM : ヒトの正常な脈拍の値が広いため8bitで送信
* Object : センサーのArduino2台使用時に使用(現在未使用)  
**残りは未使用の予約領域として残す**

## 主な仕様
### センサー側  
センサーによる検知や処理はサンプルプログラムに依る  
受け取った値を解析してZigBeeの積んであるArduinoへ送信する

### オブジェ側
