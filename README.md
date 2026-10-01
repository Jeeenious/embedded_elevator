

# Arduino 红外遥控 + 步进电机控制

## 1. 项目说明

本项目使用 Arduino、IRremote 和 AccelStepper 实现红外遥控步进电机。

按键功能：

- ↑：加速
- ↓：减速
- ←：反转
- →：正转
- A：停止

---

## 2. 硬件接线

### 红外接收器

| 红外接收器 | Arduino |
| ---------- | ------- |
| OUT / S    | D4      |
| VCC / +    | 5V      |
| GND / -    | GND     |

### 步进电机驱动器

| 电机驱动器 | Arduino |
| ---------- | ------- |
| PUL / STEP | D2      |
| DIR        | D3      |

---

## 3. 开发板：

Arduino UNO

---

## 4. Arduino 库版本

```text
IRremote 3.x
```