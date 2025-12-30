#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include <StepperShiftRegister74HC595.h>

// 1 shift registers = 8 outputs
ShiftRegister74HC595<1> sr(2, 3, 4);  // (data pin, clock pin, latch pin)

StepperShiftRegister74HC595<1> motor1(2048, sr, 0, 1, 2, 3);

void setup() {
  motor1.setSpeed(15);  // RPM
}

void loop() {
  motor1.step(100);
  delay(500);
}
