#include QMK_KEYBOARD_H

#define TG_NKRO MAGIC_TOGGLE_NKRO

const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("eye", 0x1F441),     // 👁
    UCIS_SYM("lips", 0x1F444),    // 👄
    UCIS_SYM("nose", 0x1F443)     // 👃

);

enum layer_names {
  _BASE,
  _FN,
  _MACRO
};

enum custom_keycodes {
  UCIS_S = SAFE_RANGE,
  UC_FLIP,
  UC_TABL,
  UC_SHRG,
  UC_DISA,
  UC_LENN,
  UC_FACE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi_split_bs_rshift(
    // Layer 0: Default Layer
    /*  Esc       1       2       3       4       5       6       7       8       9       0        -           =            \          `
    */KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,    KC_EQL,     KC_BSLS,    KC_GRV, \
    /*  Tab       Q       W       E       R       T       Y       U       I       O       P        [           ]                    <----
    */KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,    KC_RBRC,               KC_BSPC, \
    /*  FN        A       S       D       F       G       H       J       K       L       ;        '                            Enter
    */MO(_FN),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,  KC_SCLN, KC_QUOT,                       KC_ENT,      \
    /* SHIFT      Z       X       C       V       B       N       M       ,                          .       /       Shift            FN
    */KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,  KC_COMM,                   KC_DOT,KC_SLSH,   KC_RSFT,       MO(_FN), \
    /* CTRL     GUI       ALT                    Space
    */KC_LCTL,  KC_LGUI,  KC_LALT,               KC_SPC,                                       KC_RALT,      KC_NO,     KC_RCTL,   MO(_MACRO)),

    [_FN]   = LAYOUT_60_ansi_split_bs_rshift(
    // Layer 1: General second layer with common functions
    /*DELETE      F1      F2      F3      F4      F5      F6     F7      F8      F9      F10      F11        F12          VOL-       VOL+
    */KC_DEL,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6, KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,    KC_F12,      KC_VOLD,   KC_VOLU, \
    /*  CAPS      F11     UP                                                    MUTE    PL/PS  PREV_TRACK NEXT_TRACK              DELETE
    */KC_CAPS,  KC_F11, KC_UP,_______,_______,_______,_______, UCIS_S, _______, KC_MUTE,KC_MPLY, KC_MPRV,   KC_MNXT,               KC_DEL,  \
    /*           LEFT     DOWN    RIGHT                                                                      HOME    END
    */_______,  KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,_______,_______,_______,_______,                  KC_HOME, KC_END,       _______,  \
    /*                                                                                           PAGE UP  PAGE DOWN
    */_______,_______,_______,_______,_______,_______,_______,_______,_______,                   KC_PGDN, KC_PGUP,   _______,      _______, \
    /*
    */_______,_______,_______,                   _______,                                      _______,    _______,   _______,     _______) ,

    [_MACRO]   = LAYOUT_60_ansi_split_bs_rshift(
    // Layer 2: Specialized layer with complicated shortcuts placed to better chord, and macros
    /*            P1      P2      P3      P4      P5      P6     P7      P8      P9      P0       P-         P=           P*          P+
    */TG_NKRO,  KC_P1,  KC_P2,  KC_P3,  KC_P4,  KC_P5,  KC_P6, KC_P7,  KC_P8,  KC_P9,  KC_P0,   KC_PMNS,   KC_PEQL,    KC_PAST,   KC_PPLS,  \
    /*                   
    */_______,  UC_FLIP,UC_TABL,UC_SHRG,UC_DISA,UC_LENN,_______,_______,_______,_______,_______,_______,_______,               _______,     \
    /*                                                                                                    PRT_SCR   LCTRL          Pent
    */_______,  UC_FACE, _______,_______,_______,_______,_______,_______,_______,_______,                 KC_PSCR, KC_LCTL,       KC_PENT,  \
    /*                                                                                             P.       p/
    */_______,  _______, _______,_______,_______,_______,_______,_______,_______,                KC_PDOT, KC_PSLS,   _______,     _______,  \
    /*
    */_______,  _______, _______,                   RESET,                                    _______,    _______,   _______,     _______)
};

void keyboard_post_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UCIS_S:
      if (record->event.pressed) {
        qk_ucis_start();
      }
      break;

    case UC_FLIP:  // (╯°□°）╯︵┻━┻)
        if (record->event.pressed) {
          send_unicode_string("(╯°□°）╯︵┻━┻");
        }
        break;

    case UC_TABL:  // ┬─┬ノ( º _ ºノ)
        if (record->event.pressed) {
          send_unicode_string("┬─┬ノ( º _ ºノ)");
        }
        break;

    case UC_SHRG:  // ¯\_(ツ)_/¯
        if (record->event.pressed) {
          send_unicode_string("¯\\_(ツ)_/¯");
        }
        break;

    case UC_DISA:  // ಠ_ಠ
        if (record->event.pressed) {
          send_unicode_string("ಠ_ಠ");
        }
        break;

    case UC_LENN: // ( ͡° ͜ʖ ͡°)
        if (record->event.pressed) {
          send_unicode_string("( ͡° ͜ʖ ͡°)");
        }
        break;

    case UC_FACE: // 👁👄👁
        if (record->event.pressed) {
          send_unicode_string("👁👄👁");
        }
        break;
    default:
      return true;
  }
  return false;
}

      
    