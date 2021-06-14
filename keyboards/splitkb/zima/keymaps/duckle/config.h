/* Copyright 2019 Thomas Baart
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef MIDI_ENABLE
#define MIDI_BASIC
#define MIDI_ADVANCED
#endif

#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 4

#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_TWINKLE

// I'm using an old prototype board, so it's wired differently

#undef DIRECT_PINS
#define MATRIX_ROW_PINS { B7, F7, B5, B4 }
#define MATRIX_COL_PINS { C6, C7, D2 }
#define DIODE_DIRECTION COL2ROW

#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#define ENCODERS_PAD_A { F1 }
#define ENCODERS_PAD_B { F0 }

#undef RGB_DI_PIN
#define RGB_DI_PIN F6

#undef RGBLED_NUM
#define RGBLED_NUM 4

#undef AUDIO_CLICKY
