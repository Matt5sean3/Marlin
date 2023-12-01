/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/lcd/e3v2/proui/printstats.h
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2023 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> bugfix-2.1.x:Marlin/src/lcd/tft/ui_theme.h
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
#pragma once

<<<<<<<< HEAD:Marlin/src/lcd/e3v2/proui/printstats.h
/**
 * Print Stats page for PRO UI
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 1.4.2
 * Date: 2022/12/03
 */

class PrintStatsClass {
public:
  static void Draw();
  static void Reset();
};

extern PrintStatsClass PrintStats;

void Goto_PrintStats();
void PrintStatsReset();
========
#include "../../inc/MarlinConfigPre.h"

#ifndef TFT_THEME
  #define TFT_THEME BLUE_MARLIN
#endif

#define TFT_THEME_INCL_(M) STRINGIFY_(themes/theme_##M.h)
#define TFT_THEME_INCL(M) TFT_THEME_INCL_(M)

#include "tft_color.h"
#include TFT_THEME_INCL(TFT_THEME)
#include "themes/theme_default.h"
>>>>>>>> bugfix-2.1.x:Marlin/src/lcd/tft/ui_theme.h
