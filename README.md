# Arduino-IlluminationPulseSensor
東舞鶴駅イルミネーション事業用心拍センサープログラム(電気情報工学実験ⅡB)

# 構成  
* PulseReadTest  
 * PulseReadTest.ino  
 センサー動作テスト用プログラム

## 定義された変数について
### センサー側

Variable Name   | Type    |  description
----------------|---------|-----------------------
Signal          | Int     | AnalogInputで得た値。
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
