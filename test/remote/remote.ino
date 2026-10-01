#include <IRremote.h>

#define IR_RECEIVE_PIN 4

IRrecv irrecv_4(IR_RECEIVE_PIN);

void setup() {
  Serial.begin(9600);

  pinMode(IR_RECEIVE_PIN, INPUT);

  irrecv_4.enableIRIn();

  Serial.println("红外遥控器测试开始");
  Serial.println("请按遥控器按键...");
}

void loop() {

  if (irrecv_4.decode()) {

    unsigned long ir_item =
      irrecv_4.decodedIRData.decodedRawData;

    Serial.print("编码: 0x");
    Serial.println(ir_item, HEX);

    switch (ir_item) {

      case 0xBA45FF00:
        Serial.println(">>> 按键：A");
        break;

      case 0xB946FF00:
        Serial.println(">>> 按键：B");
        break;

      case 0xB847FF00:
        Serial.println(">>> 按键：C");
        break;

      case 0xBB44FF00:
        Serial.println(">>> 按键：D");
        break;

      case 0xBC43FF00:
        Serial.println(">>> 按键：E");
        break;

      case 0xF20DFF00:
        Serial.println(">>> 按键：F");
        break;

      case 0xE916FF00:
        Serial.println(">>> 按键：0");
        break;

      case 0xF30CFF00:
        Serial.println(">>> 按键：1");
        break;

      case 0xE718FF00:
        Serial.println(">>> 按键：2");
        break;

      case 0xA15EFF00:
        Serial.println(">>> 按键：3");
        break;

      case 0xF708FF00:
        Serial.println(">>> 按键：4");
        break;

      case 0xE31CFF00:
        Serial.println(">>> 按键：5");
        break;

      case 0xA55AFF00:
        Serial.println(">>> 按键：6");
        break;

      case 0xBD42FF00:
        Serial.println(">>> 按键：7");
        break;

      case 0xAD52FF00:
        Serial.println(">>> 按键：8");
        break;

      case 0xB54AFF00:
        Serial.println(">>> 按键：9");
        break;

      case 0xBF40FF00:
        Serial.println(">>> 按键：上 ↑");
        break;

      case 0xE619FF00:
        Serial.println(">>> 按键：下 ↓");
        break;

      case 0xF807FF00:
        Serial.println(">>> 按键：左 ←");
        break;

      case 0xF609FF00:
        Serial.println(">>> 按键：右 →");
        break;

      case 0xEA15FF00:
        Serial.println(">>> 按键：设置");
        break;

      default:
        Serial.println(">>> 未知按键");
        break;
    }

    Serial.println("--------------------");

    irrecv_4.resume();
  }
}