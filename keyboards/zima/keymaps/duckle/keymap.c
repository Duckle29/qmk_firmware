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
  BASE,
  MIDI1,
  SATISFACTORY
};

int TOP_LAYER = SATISFACTORY;

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

    [BASE] = LAYOUT(
        KC_P7,      KC_P8,      KC_P9,  \
        KC_P4,      KC_P5,      KC_P6,  \
        KC_P1,      KC_P2,      KC_P3,  \
        KC_P0,      KC_PDOT,    KC_PENT \
    ),
    [MIDI1] = LAYOUT(
        NOTE0,      NOTE1,      NOTE2,  \
        NOTE3,      NOTE4,      NOTE5,  \
        NOTE6,      NOTE7,      NOTE8,  \
        NOTE9,      NOTE10,     NOTE11  \
    ),
    [SATISFACTORY] = LAYOUT(
        KC_NO,      KC_NO,      TG_SPRINT,\
        KC_NO,      KC_NO,      KC_NO,  \
        KC_NO,      KC_NO,      KC_NO,  \
        KC_NO,      KC_NO,      CHR_JMP \
    )
};

bool tg_sprint_state = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NOTE0 ... NOTE11:
            if (record->event.pressed) {
                process_midi_basic_noteon(keycode - NOTE0);
            } else {
                process_midi_basic_noteoff(keycode - NOTE0);
            }
            break;
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
            break;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {

    switch(get_highest_layer(layer_state)) {
        case BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case MIDI1:
            oled_write_ln_P(PSTR("MIDI1"), false);
            break;
        case SATISFACTORY:
            oled_write_ln_P(PSTR("SATISFACTORY"), false);
            break;
    }
}
#endif

void keyboard_post_init_user() {
    #ifdef OLED_DRIVER_ENABLE
        wait_ms(2000);
        oled_init(OLED_ROTATION_180);
    #endif
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

    if(new_layer > TOP_LAYER)
    {
        new_layer = BASE;
    }
    if(new_layer < BASE)
    {
        new_layer = TOP_LAYER;
    }
    layer_move(new_layer);
}
#endif
