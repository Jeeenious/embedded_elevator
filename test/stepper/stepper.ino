/*
 * 功能说明：
 * 本程序使用 AccelStepper 库控制步进电机驱动器。
 *
 * 接线：
 * Arduino D2 → 驱动器 PUL/STEP
 * Arduino D3 → 驱动器 DIR
 *
 * 当前驱动器细分设置为 1600 脉冲/圈。
 * 电机启动后先运行到 -204800 步，即反向运行 128 圈；
 * 到达目标位置后停止 1 秒，然后返回 0 位置；
 * 到达 0 位置后再次停止 1 秒，并重复上述过程。
 *
 * 运动参数：
 * 最大速度：2400 步/秒 = 90 RPM
 * 加速度：1600 步/秒²
 *
 * 注意：
 * stepper.run() 必须在 loop() 中持续执行，
 * 因此运行过程中应避免使用较长时间的 delay() 或其他耗时操作。
 */

#include <AccelStepper.h>

const int pulPin = 2;
const int dirPin = 3;

// 目前驱动器上的细分设置为 1600
const int PulsePerRev = 1600;

// 运行 128 圈
long STEP = -(long)PulsePerRev * 128;

AccelStepper stepper(AccelStepper::DRIVER, pulPin, dirPin);

void setup() {
  // 最大速度：2400 步/秒
  stepper.setMaxSpeed(2400);

  // 加速度：1600 步/秒²
  stepper.setAcceleration(1600);

  // 设置第一个目标位置
  stepper.moveTo(STEP);
}

void loop() {
  if (stepper.distanceToGo() == 0) {
    delay(1000);

    if (stepper.currentPosition() == STEP) {
      stepper.moveTo(0);
    } else {
      stepper.moveTo(STEP);
    }
  }

  // 持续执行步进电机运动
  stepper.run();
}