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
