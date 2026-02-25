# StepperShiftRegister74HC595

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/mussacharles60/library/StepperShiftRegister74HC595.svg)](https://registry.platformio.org/libraries/mussacharles60/StepperShiftRegister74HC595)
[![Version](https://img.shields.io/github/v/release/mussacharles60/StepperShiftRegister74HC595)](https://github.com/mussacharles60/StepperShiftRegister74HC595/releases)
[![License](https://img.shields.io/github/license/mussacharles60/StepperShiftRegister74HC595)](LICENSE)
![Framework](https://img.shields.io/badge/framework-Arduino-blue)
![MCU](https://img.shields.io/badge/MCU-AVR%20%7C%20ESP32%20%7C%20ESP8266-green)


Control one or more stepper motors using **74HC595 shift registers** while consuming only **3 microcontroller pins**.

This library is designed for **Arduino & PlatformIO** projects where pin count is limited and multiple stepper motors are needed.

---

## ✨ Features

* ✅ Uses **only 3 MCU pins** (DATA, CLOCK & LATCH)
* ✅ Supports **multiple chained 74HC595** shift registers
* ✅ Drive **multiple stepper motors** simultaneously
* ✅ Familiar Arduino `Stepper`-style API
* ✅ **Blocking and non-blocking (async) stepping modes**
* ✅ No dynamic memory (safe for AVR)
* ✅ Works with **ULN2003, L293D, L298, MOSFET drivers**

---

# Basic Circuit Diagram

![Sample circuit diagram of Arduino with 74HC595 shift registers and 3 stepper motors (png)](/examples/sample_circuit.png)

![Sample circuit diagram of Arduino with 74HC595 shift registers and 3 stepper motors (svg)](/examples/sample_circuit.svg)

[Click here for circuit diagram source link](https://app.cirkitdesigner.com/project/cf9f8d4d-f092-4e92-b2ee-7bc8a3677775)

---

## ❗ Important Notice

⚠ **DO NOT connect stepper motors directly to the 74HC595**

The 74HC595 can only output logic signals.

You **must use a motor driver**, such as:

* ULN2003 (recommended for 28BYJ-48)
* L293D / L298
* Discrete MOSFET or transistor arrays

---

## 📦 Installation (PlatformIO)

This library is available in the PlatformIO Registry.

Add it to your `platformio.ini`:

```ini
lib_deps =
  mussacharles60/StepperShiftRegister74HC595@^1.0.2
```
PlatformIO will auto-import it.

Project structure: (If you want to add this library manually)
```
your-project/
├── lib/
│ └── StepperShiftRegister74HC595/
├── src/
│ └── main.cpp
```

PlatformIO will auto-detect it.

---

## 🔌 Wiring Overview

### Microcontroller → 74HC595
| MCU Pin | 74HC595 Pin |
|-------|-------------|
| DATA  | DS          |
| CLOCK | SH_CP       |
| LATCH | ST_CP       |

### 74HC595 → Driver
Each stepper motor uses **4 outputs**:

Q0 → IN1
Q1 → IN2
Q2 → IN3
Q3 → IN4


With chained shift registers, pin numbering continues:
* First IC: 0–7
* Second IC: 8–15
* Third IC: 16–23
* etc.

---

## 🧩 Template Parameter (`Size`)

```cpp
ShiftRegister74HC595<Size>

Size = number of 74HC595 ICs chained together.
```

Examples:

* Size = 1 → 8 outputs
* Size = 2 → 16 outputs
* Size = 3 → 24 outputs

---

<!-- ## 🔗 Required Dependency

This library **depends on** the following external library:

### ShiftRegister74HC595  
**Author:** Timo Denk  

This library handles all low-level communication with the 74HC595 shift registers.

### Installation (PlatformIO)

Add the dependency to your `platformio.ini`:

```ini
lib_deps =
    simsso/ShiftRegister74HC5955 @ ^1.3.1
```

Or install it via the PlatformIO Library Manager.

### Installation (Arduino IDE)

1. Open Library Manager
2. Search for “ShiftRegister74HC595”
3. Install the library by Timo Denk

⚠ This library will not compile without ShiftRegister74HC595 installed.

--- -->

## 🌀 Step Modes

Current implementation:

* ✔ Full-step (4-step sequence)
* Planned / Easy to add:
* Half-step (8-step)

Custom stepping tables

* Microstepping (with DAC or PWM drivers)

---

## ⏱ Blocking Behavior

⚠ The `step()` function is **blocking**, exactly like Arduino’s original `Stepper` library.

This means:

* While stepping, other code is paused

* Not suitable for time-critical multitasking

## 🚀 Basic Example 1 (Blocking)

```cpp
#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include <StepperShiftRegister74HC595.h>

// 2 shift registers = 16 outputs
ShiftRegister74HC595<2> sr(2, 3, 4);  // (data pin, clock pin, latch pin)

StepperShiftRegister74HC595<2> motor1(2048, sr, 0, 1, 2, 3);
StepperShiftRegister74HC595<2> motor2(2048, sr, 4, 5, 6, 7);
StepperShiftRegister74HC595<2> motor3(2048, sr, 8, 9, 10, 11);

void setup() {
  motor1.setSpeed(15);  // RPM
  motor2.setSpeed(12);
  motor3.setSpeed(10);
}

void loop() {
  motor1.step(200);
  motor2.step(-100);
  motor3.step(50);
  delay(500);
}
```

---

## 🚦 Non-Blocking (Asynchronous) Behavior

This means:

* The motor moves in the background
* Your program continues running

Ideal for:
* Multiple stepper motors
* Sensors
* WiFi / BLE
* Displays
* Real-time systems (ESP32, ESP8266)

✅ The `stepAsync()` function is non-blocking.

⚠️ Important:
You must call `update()` repeatedly (usually inside `loop()`) for the motor to advance.

## 🚀 Basic Example 2 (Non-Blocking / Async)
```cpp
#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include <StepperShiftRegister74HC595.h>

// 2 shift registers = 16 outputs
ShiftRegister74HC595<2> sr(2, 3, 4);  // (data pin, clock pin, latch pin)

StepperShiftRegister74HC595<2> motor1(2048, sr, 0, 1, 2, 3);
StepperShiftRegister74HC595<2> motor2(2048, sr, 4, 5, 6, 7);
StepperShiftRegister74HC595<2> motor3(2048, sr, 8, 9, 10, 11);

void setup() {
  motor1.setSpeed(15);  // RPM
  motor2.setSpeed(12);
  motor3.setSpeed(10);

  // Start motors asynchronously
  motor1.stepAsync(200);
  motor2.stepAsync(-100);
  motor3.stepAsync(50);
}

void loop() {
  // Update motors (VERY IMPORTANT) MUST be called often
  motor1.update();
  motor2.update();
  motor3.update();

  if (!motor1.isRunning()) {
    // do something when finished
  }

  if (!motor2.isRunning()) {
    // do something when finished
  }

  if (!motor3.isRunning()) {
    // do something when finished
  }

  // Other functions logics goes here...
}
```

---

### Blocking vs Non-blocking control

- `step(steps)`
  - Blocks until movement is complete
  - Compatible with Arduino Stepper behavior

- `stepAsync(steps)`
  - Non-blocking
  - Requires `update()` to be called frequently
  - Ideal for ESP32, WiFi, sensors, UI, and multitasking

---

## ⚡ Performance Notes
* Suitable up to ~500–800 steps/sec total
* SPI-based shift register control is faster (future upgrade)

---

## 🛠 Tested With

* Arduino Uno / Nano
* ESP32
* ESP8266
* 28BYJ-48 + ULN2003
* Bipolar steppers via L293D

---

## 📜 License

MIT License
Free to use, modify, and distribute.

Copyright (c) 2025 Mussa Charles

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## ❤️ Credits

* Arduino Stepper Library (original logic)
* ShiftRegister74HC595 Library by **Timo Denk**
* Custom integration by Mussa Charles

---

## 🚧 Roadmap

* [x] **Non-blocking motion engine (async stepping)**
* [ ] **Half-step mode**
  *Higher resolution, smoother motion*
* [ ] **SPI backend**
  *Hardware SPI for faster shift register updates*
* [ ] **Acceleration / deceleration (ramp profiles)**
  *Avoid missed steps at high speed*
* [ ] **Central motor manager**
  *Single update loop for many motors*
* [ ] **Stepper driver abstraction**
  *ULN2003, H-bridge, custom drivers*

---
