/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/tests/marlin_tests.cpp
 * Copyright (c) 2022 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> bugfix-2.1.x:Marlin/src/HAL/NATIVE_SIM/pinsDebug.cpp
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

<<<<<<<< HEAD:Marlin/src/tests/marlin_tests.cpp
#include "../inc/MarlinConfigPre.h"

#if ENABLED(MARLIN_TEST_BUILD)

#include "../module/endstops.h"
#include "../module/motion.h"
#include "../module/planner.h"
#include "../module/settings.h"
#include "../module/stepper.h"
#include "../module/temperature.h"

// Individual tests are localized in each module.
// Each test produces its own report.

// Startup tests are run at the end of setup()
void runStartupTests() {
  // Call post-setup tests here to validate behaviors.
}

// Periodic tests are run from within loop()
void runPeriodicTests() {
  // Call periodic tests here to validate behaviors.
}

#endif // MARLIN_TEST_BUILD
========
#ifdef __PLAT_NATIVE_SIM__

#include "../../inc/MarlinConfig.h"
#include "pinsDebug.h"

int8_t ADC_pin_mode(pin_t pin) { return -1; }

int8_t get_pin_mode(const pin_t pin) { return VALID_PIN(pin) ? 0 : -1; }

bool GET_PINMODE(const pin_t pin) {
  const int8_t pin_mode = get_pin_mode(pin);
  if (pin_mode == -1 || pin_mode == ADC_pin_mode(pin)) // Invalid pin or active analog pin
    return false;

  return (Gpio::getMode(pin) != 0); // Input/output state
}

bool GET_ARRAY_IS_DIGITAL(const pin_t pin) {
  return !IS_ANALOG(pin) || get_pin_mode(pin) != ADC_pin_mode(pin);
}

void print_port(const pin_t) {}
void pwm_details(const pin_t) {}
bool pwm_status(const pin_t) { return false; }

#endif
>>>>>>>> bugfix-2.1.x:Marlin/src/HAL/NATIVE_SIM/pinsDebug.cpp
