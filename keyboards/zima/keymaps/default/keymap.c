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
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(/* Base */
                                                                           KC_P7, KC_P8, KC_P9, KC_P4, KC_P5, KC_P6, KC_P1, KC_P2, KC_P3, KC_P0, KC_PDOT, KC_PENT)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    //     case QMKBEST:
    //         if (record->event.pressed) {
    //             // when keycode QMKBEST is pressed
    //             SEND_STRING("QMK is the best thing ever!");
    //         } else {
    //             // when keycode QMKBEST is released
    //         }
    //         break;
    //     case QMKURL:
    //         if (record->event.pressed) {
    //             // when keycode QMKURL is pressed
    //             SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
    //         } else {
    //             // when keycode QMKURL is released
    //         }
    //         break;
    // }
    // return true;
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) { render_qmk_logo(); }
#endif

void keyboard_post_init_user() {
    // rgblight_sethsv(0, 0, 255);
}

void switch_program_win(bool clockwise) {
    if (clockwise) {
        SEND_STRING(SS_TAP(X_TAB));
    }
}

#ifdef ENCODER_ENABLE
bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;
#    define ALTTAB_HOLD_TIME 1000
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) {
        return;
    }

    alt_tab_timer = timer_read();

    if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB));
        wait_ms(50);
        SEND_STRING(SS_TAP(X_LEFT));
    }

    if (clockwise) {
        SEND_STRING(SS_TAP(X_TAB));
    } else {
        SEND_STRING(SS_TAP(X_LEFT));
    }
    /*
    if (index == 0) {
        if(rgblight_get_val() == 255)
        {
            rgblight_sethsv(0,100,150);
        }
        // Move whole words. Hold shift to select while moving.
        if (clockwise) {
            rgblight_increase_hue_noeeprom();
        } else {
            rgblight_decrease_hue_noeeprom();
        }
    }*/
}
#endif

void matrix_scan_user(void) {
#ifdef ENCODER_ENABLE
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > ALTTAB_HOLD_TIME) {
            SEND_STRING(SS_UP(X_LALT));
            is_alt_tab_active = false;
        }
    }
#endif
}
