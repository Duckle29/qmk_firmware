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

enum zima_layers {
  _BASE,
  _FN,
  #ifdef MIDI_ENABLE
  _MIDI1,
  #endif
  _CVAT,
  _TOP_LAYER
};

enum custom_keycodes {
    NOTE0 = SAFE_RANGE,
    NOTE1,
    NOTE2,
    NOTE3,
    NOTE4,
    NOTE5,
    NOTE6,
    NOTE7,
    NOTE8,
    NOTE9,
    NOTE10,
    NOTE11,

    CHR_JMP,
    TG_SPRINT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_4x3(
        KC_P7,      KC_P8,      KC_P9,  \
        KC_P4,      KC_P5,      KC_P6,  \
        KC_P1,      KC_P2,      KC_P3,  \
        KC_P0,      RESET,    KC_PENT \
    ),
    [_FN] = LAYOUT_ortho_4x3(
        KC_F13,     KC_F14,     KC_F15, \
        KC_F16,     C(S(KC_F8)),     KC_F18, \
        KC_F19,     KC_F20,     KC_F21, \
        KC_F22,     KC_F23,     KC_F24  \
    ),
    #ifdef MIDI_ENABLE
    [_MIDI1] = LAYOUT_ortho_4x3(
        NOTE0,      NOTE1,      NOTE2,  \
        NOTE3,      NOTE4,      NOTE5,  \
        NOTE6,      NOTE7,      NOTE8,  \
        NOTE9,      NOTE10,     NOTE11  \
    ),
    #endif
    [_CVAT] = LAYOUT_ortho_4x3(
        KC_NO,      KC_NO,      KC_NO,  \
        KC_NO,      KC_NO,      KC_NO,  \
        KC_NO,      KC_NO,      KC_NO,  \
        KC_D,       KC_N,       KC_F    \
    )
};

void shutdown_user()
{
    rgblight_setrgb(255, 0, 0);
}

bool tg_sprint_state = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef MIDI_ENABLE
        case NOTE0 ... NOTE11:
            if (record->event.pressed) {
                process_midi_basic_noteon(keycode - NOTE0);
            } else {
                process_midi_basic_noteoff(keycode - NOTE0);
            }
            break;
        #endif
        case CHR_JMP:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING(SS_DOWN(X_C) SS_TAP(X_SPC) SS_UP(X_C));
            } else {
                // when keycode QMKURL is released
            }
            break;
        case TG_SPRINT:
            if(tg_sprint_state)
            {
                SEND_STRING(SS_UP(X_LSHIFT) SS_UP(X_W));
                rgblight_setrgb_at(255, 255, 255, 0);
            }
            else
            {
                SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_W));
                rgblight_setrgb_at(255, 0, 0, 0);
            }
            tg_sprint_state = !tg_sprint_state;
            break;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {

    switch(get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("Functions"), false);
            break;
        #ifdef MIDI_ENABLE
        case _MIDI1:
            oled_write_ln_P(PSTR("MIDI1"), false);
            break;
        #endif
        case _CVAT:
            oled_write_ln_P(PSTR("CVAT"), false);
            break;
    }
}
#endif

void keyboard_post_init_user() {
    #ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(100, 100, 100);
    #endif
    #ifdef OLED_DRIVER_ENABLE
        wait_ms(2000);
        oled_init(OLED_ROTATION_180);
    #endif
    layer_move(_FN);
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) {
        return;
    }

    int new_layer = 0;
    if (clockwise) {
        new_layer = get_highest_layer(layer_state) + 1;
    } else {
        new_layer = get_highest_layer(layer_state) - 1;
    }

    if(new_layer >= _TOP_LAYER)
    {
        new_layer = _BASE;
    }
    if(new_layer < _BASE)
    {
        new_layer = _TOP_LAYER-1;
    }
    layer_move(new_layer);
}
#endif
