# Arduino-IlluminationPulseSensor
東舞鶴駅イルミネーション事業用心拍センサープログラム(電気情報工学実験ⅡB)

* AVRの仕様書421ﾍﾟｰｼﾞってマジか…
* たまーに出てくるC++11に困惑しか感じられない

---

# ﾘﾎﾟｼﾞﾄﾘ構成  
* PulseReadTest  
 * PulseReadTest.ino  
 センサー動作テスト用プログラム

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
Signal  | Int     | 8bit | AnalogInputで得た値。
BPM     | Int     | 8bit | 1分間あたりの脈拍値。
IBI     | Int     | 8bit | 鼓動と鼓動のｲﾝﾀｰﾊﾞﾙの値。
Pulse   | Boolean | 1bit | センサーが感知したらtrue,それ以外はfalseを返す
QS      | Boolean | 1bit | BPMが更新されたりパルスが更新されるたびにtrueを返す。リセット時に使用する。

## 主な仕様
### センサー側  
センサーによる検知や処理はサンプルプログラムに依る
受け取った値を解析してZigBee側へ送信する

### オブジェ側
