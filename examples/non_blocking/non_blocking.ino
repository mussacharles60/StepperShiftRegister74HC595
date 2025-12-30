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
