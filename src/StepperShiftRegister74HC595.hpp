/*
 * Implementation file for StepperShiftRegister74HC595
 * --------------------------------------------------
 * Uses templates, so implementation must be included
 * at the end of the header file.
 */

#include "StepperShiftRegister74HC595.h"

/*
* StepperShiftRegister74HC595 Constructor
*
* @param Size             Size is the number of shiftregisters stacked in serial
* @param number_of_steps  Steps per full revolution (e.g. 200)
* @param shiftReg         Reference to shared ShiftRegister74HC595 object
* @param pin1..pin4       Output pin numbers on the shift register chain
*                         (0 = Q0 of first 74HC595)
*/
template<uint8_t Size>
StepperShiftRegister74HC595<Size>::StepperShiftRegister74HC595(
    int number_of_steps,
    ShiftRegister74HC595<Size>& shiftReg,
    uint8_t pin1,
    uint8_t pin2,
    uint8_t pin3,
    uint8_t pin4
) {
    // Store motor parameters
    _stepsPerRev = number_of_steps;
    _stepNumber = 0;
    _lastStepTime = 0;

    // Store pointer to the shared shift register
    _sr = &shiftReg;

    // Store shift register output pins for this motor
    _pins[0] = pin1;
    _pins[1] = pin2;
    _pins[2] = pin3;
    _pins[3] = pin4;
}

/*
* Set motor speed in RPM (revolutions per minute)
*/
template<uint8_t Size>
void StepperShiftRegister74HC595<Size>::setSpeed(long rpm) {
    /*
     * Calculate delay between steps:
     * 60 sec → minutes
     * 1e6    → microseconds
     */
    _stepDelay = 60L * 1000L * 1000L / _stepsPerRev / rpm;
}

/*
* Move motor by a given number of steps
*  - Positive value → forward
*  - Negative value → reverse
*
* NOTE:
*  - This function is BLOCKING (same as Arduino Stepper library)
*/
template<uint8_t Size>
void StepperShiftRegister74HC595<Size>::step(int steps) {
    int stepsLeft = abs(steps);

    // Determine direction
    _direction = (steps > 0);

    // Blocking loop (Arduino Stepper compatible behavior)
    while (stepsLeft > 0) {
        unsigned long now = micros();

        if (now - _lastStepTime >= _stepDelay) {
            _lastStepTime = now;

            // Advance or reverse step index
            if (_direction) {
                _stepNumber++;
                if (_stepNumber == _stepsPerRev)
                    _stepNumber = 0;
            } else {
                if (_stepNumber == 0)
                    _stepNumber = _stepsPerRev;
                _stepNumber--;
            }

            // Output coil pattern
            stepMotor(_stepNumber % 4);
            stepsLeft--;
        }
    }
}

/*
* Outputs the coil sequence for a single step
*/
template<uint8_t Size>
void StepperShiftRegister74HC595<Size>::stepMotor(uint8_t step) {
    /*
     * 4-step full-step sequence
     * Suitable for:
     *  - ULN2003 + 28BYJ-48
     *  - Bipolar steppers via H-bridge
     */
    static const uint8_t sequence[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1}
    };

    // Set outputs without updating registers yet
    for (uint8_t i = 0; i < 4; i++) {
        _sr->setNoUpdate(_pins[i], sequence[step][i]);
    }

    // Push all changes to the shift register at once
    _sr->updateRegisters();
}
