/*
 * StepperShiftRegister74HC595
 * --------------------------------
 * Stepper motor control using one or more 74HC595 shift registers.
 *
 * - Uses ONLY 3 microcontroller pins (DATA, CLOCK, LATCH)
 * - Supports multiple steppers using chained shift registers
 * - Each stepper occupies 4 output pins on the shift register
 *
 * NOTE:
 *  - This library only controls logic signals
 *  - Use ULN2003, L293D, L298, or MOSFET drivers for real motors
 */

#ifndef STEPPER_SHIFT_REGISTER_74HC595_H
#define STEPPER_SHIFT_REGISTER_74HC595_H

// #pragma once

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

template<uint8_t Size>
class StepperShiftRegister74HC595 {
public:
    StepperShiftRegister74HC595(
        int number_of_steps,
        ShiftRegister74HC595<Size>& shiftReg,
        uint8_t pin1,
        uint8_t pin2,
        uint8_t pin3,
        uint8_t pin4
    );
    void setSpeed(long rpm);    // Set motor speed - RPM
    void step(int steps);       // Blocking
    void stepAsync(long steps); // Non-blocking (async)
    void update();              // Call repeatedly from loop()
    bool isRunning();           // Async status

private:
    void stepMotor(uint8_t step);

    // Motor direction (0 = reverse, 1 = forward)
    int _direction;

    // Steps per full revolution
    int _stepsPerRev;

    // Current step position
    int _stepNumber;

    // Delay between steps (microseconds)
    unsigned long _stepDelay;

    // coil sequence index (0–3)
    int _phase = 0;

    // Timestamp of last step
    unsigned long _lastStepTime;

    // Pointer to shared shift register object
    ShiftRegister74HC595<Size>* _sr;

    // Output pins on the shift register (4 per motor)
    uint8_t _pins[4];

    // Total number of steps requested for async motion
    long _targetSteps = 0;

    // Number of steps already executed in async mode
    long _currentSteps = 0;

    // Step direction: +1 = forward, -1 = reverse
    int _direction = 1;

    // Indicates whether the motor is currently moving asynchronously
    bool _isMoving = false;
};

#include "StepperShiftRegister74HC595.hpp"

#endif
