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

#include <Arduino.h>
#include "StepperShiftRegister74HC595.h"
