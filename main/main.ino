/*
 * 红外遥控 + 步进电机控制
 *
 * 接线：
 * IR OUT → D4
 * PUL/STEP → D2
 * DIR → D3
 *
 * ↑：加速
 * ↓：减速
 * ←：反转
 * →：正转
 * A：停止
 *
 * 默认速度：2400 步/秒
 * 加速度：1600 步/秒²
 * 细分：1600 脉冲/圈
 */

#include <IRremote.h>
#include <AccelStepper.h>

#define IR_RECEIVE_PIN 4

IRrecv irrecv_4(IR_RECEIVE_PIN);

const int pulPin = 2;
const int dirPin = 3;

const int PulsePerRev = 1600;

AccelStepper stepper(AccelStepper::DRIVER, pulPin, dirPin);

long motorSpeed = 2400;

const long motorAcceleration = 1600;
const long speedStep = 400;
const long minSpeed = 400;
const long maxSpeed = 4800;

#define IR_A       0xBA45FF00
#define IR_UP      0xBF40FF00
#define IR_DOWN    0xE619FF00
#define IR_LEFT    0xF807FF00
#define IR_RIGHT   0xF609FF00

int motorDirection = 0;

void setup() {

  Serial.begin(9600);

  pinMode(IR_RECEIVE_PIN, INPUT);
  irrecv_4.enableIRIn();

  stepper.setMaxSpeed(motorSpeed);
  stepper.setAcceleration(motorAcceleration);

  Serial.println("红外 + 步进电机控制启动");
  Serial.println("↑ 加速");
  Serial.println("↓ 减速");
  Serial.println("← 反转");
  Serial.println("→ 正转");
  Serial.println("A 停止");

  Serial.print("默认速度：");
  Serial.print(motorSpeed);
  Serial.println(" steps/s");
}

void loop() {

  if (irrecv_4.decode()) {

    unsigned long ir_item =
      irrecv_4.decodedIRData.decodedRawData;

    if (ir_item == 0x00000000) {
      irrecv_4.resume();
      return;
    }

    Serial.print("编码: 0x");
    Serial.println(ir_item, HEX);

    if (ir_item == IR_UP) {

      motorSpeed += speedStep;

      if (motorSpeed > maxSpeed) {
        motorSpeed = maxSpeed;
      }

      stepper.setMaxSpeed(motorSpeed);

      Serial.print("↑ 加速，当前速度：");
      Serial.print(motorSpeed);
      Serial.println(" steps/s");

    } else if (ir_item == IR_DOWN) {

      motorSpeed -= speedStep;

      if (motorSpeed < minSpeed) {
        motorSpeed = minSpeed;
      }

      stepper.setMaxSpeed(motorSpeed);

      Serial.print("↓ 减速，当前速度：");
      Serial.print(motorSpeed);
      Serial.println(" steps/s");

    } else if (ir_item == IR_LEFT) {

      motorDirection = -1;
      stepper.setSpeed(-motorSpeed);

      Serial.print("← 反转，当前速度：");
      Serial.print(motorSpeed);
      Serial.println(" steps/s");

    } else if (ir_item == IR_RIGHT) {

      motorDirection = 1;
      stepper.setSpeed(motorSpeed);

      Serial.print("→ 正转，当前速度：");
      Serial.print(motorSpeed);
      Serial.println(" steps/s");

    } else if (ir_item == IR_A) {

      motorDirection = 0;
      stepper.stop();

      Serial.println("A → 停止");

    } else {

      Serial.print(">>> 未知按键：0x");
      Serial.println(ir_item, HEX);
    }

    Serial.println("--------------------");

    irrecv_4.resume();
  }

  stepper.run();
}