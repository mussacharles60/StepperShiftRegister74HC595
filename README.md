# StepperShiftRegister74HC595

Control one or more stepper motors using **74HC595 shift registers** while consuming only **3 microcontroller pins**.

This library is designed for **Arduino & PlatformIO** projects where pin count is limited and multiple stepper motors are needed.

---

## ✨ Features

* ✅ Uses **only 3 MCU pins** (DATA, CLOCK, LATCH)
* ✅ Supports **multiple chained 74HC595** shift registers
* ✅ Drive **multiple stepper motors** simultaneously
* ✅ Familiar Arduino `Stepper`-style API
* ✅ No dynamic memory (safe for AVR)
* ✅ Works with **ULN2003, L293D, L298, MOSFET drivers**

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

This is a **custom local library**.

Project structure:
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

## 🚀 Basic Example

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
  motor1.setSpeed(18);  // RPM
  motor2.setSpeed(15);
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

## 🔗 Required Dependency

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

---

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

If you need:

* Non-blocking control
* Acceleration
* Multi-axis sync

👉 Ask for an **async version**

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

* [ ] Half-step mode
* [ ] SPI backend
* [ ] Non-blocking motion engine
* [ ] Central motor manager
