#include QMK_KEYBOARD_H

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes { QWERTY = SAFE_RANGE };

#define QWERTY  MO(_QWERTY)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)

enum {
  TT_LINE,
  TT_JLINE,
};

tap_dance_action_t tap_dance_actions[] = {
  [TT_JLINE] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
  [TT_LINE]  = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |  P   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  UP  | /?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CMD  | Opt  | Tab  | Esisu| Lower| SPC  | SPC  |Raise |  -_  | LEFT | DOWN |RIGHT |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_Q,   KC_Q,    KC_W,                   KC_E,  KC_R,   KC_T,               KC_Y,               KC_U,         KC_I,    KC_O,     KC_P,           KC_P,  \
  KC_A,   KC_A,    KC_S,                   KC_D,  KC_F,   KC_G,               KC_H,               KC_J,         KC_K,    KC_L,    KC_ENT,          KC_ENT,  \
  KC_Z,   KC_Z,    KC_X,                   KC_C,  KC_V,   KC_B,               KC_N,               KC_M,      KC_COMM,   KC_DOT,   RSFT_T(KC_SLSH), RSFT_T(KC_SLSH),  \
  KC_LGUI, KC_LALT, KC_LCTL, LSFT_T(KC_ESC), LT(LOWER,KC_TAB),KC_SPC, KC_BSPC, LT(RAISE,KC_SCLN), _______, _______,  KC_LNG1,       KC_LNG2  \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  +   |   =  |   {  |   }  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SHIFT|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |   |   '  |  "   |  "'  | PgUp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CMD  | Opt   | ESC |      |      |      |      |      |  _   | LEFT | RIGHT| PgDn |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  _______,   S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),  S(KC_6),     S(KC_7), S(KC_8),   S(KC_9),   S(KC_0),  _______, \
  _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_F5,   KC_F11,   S(KC_EQL),  KC_EQL,   KC_LBRC,   KC_RBRC, _______, \
  _______,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F12,  S(KC_BSLS), KC_MINS,   KC_QUOT,   KC_RSFT, _______, \
  _______, _______,  _______,  _______, _______,  _______, _______,     _______, _______,   _______,   _______,  _______ \
),
/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SHIFT|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  =>  |   '  |  "   |  :   |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CMD  | CTRL |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  _______, KC_GRV,          KC_1,   KC_2,   KC_3,   S(KC_MINS),            KC_MINS,         _______,  KC_UP,   _______,        KC_KB_MUTE,  _______, \
  _______, KC_BSLS,         KC_4,   KC_5,   KC_6,   S(KC_SCLN),            _______,         KC_LEFT, KC_DOWN,  KC_RIGHT, LGUI(LCTL(KC_Q)), _______, \
  _______, LGUI(LSFT(KC_4)),KC_7,   KC_8,   KC_9,         KC_0,      RCTL(KC_LEFT),  RCTL(KC_RIGHT), KC_QUOT,  KC_PGUP,           KC_PGDN, _______, \
  _______, _______,      _______, _______, _______,    _______,            _______,        _______,  _______, _______,            _______,  _______ \
),

/* ADJUST
 * ,------------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |Qwerty|  F9  | F10  | F11  | F12   |
 * |------+------+------+------+------+-------------+------+------+------+------+------ |
 * |      | RGB  | RGB  | RGB  | RGB  |  BL  |  BL  |  BL  |  BL  |Swirl | Xmas |       |
 * |      | Togl | Hue+ | Sat+ | Brt+ | Togl |Breath| Brt+ | Brt- |      |      |       |
 * |------+------+------+------+------+------|------+------+------+------+------+------ |
 * |      |      | RGB  | RGB  | RGB  |      |      |      |      |      |      |       |
 * |      |      | Hue- | Sat- | Brt- |      |      |      |Rnbow |      |PrScr |       |
 * |------+------+------+------+------+------+------+------+------+------+------+------ |
 * |      |      | RGB  |      |      |      |      |      |      |      |      |       |
 * |      |      | Mode |      |      |      |      |      |      |      |      |       |
 * `------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   QWERTY,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    _______, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, BL_TOGG,    BL_BRTG, BL_UP,  BL_DOWN, RGB_M_SW,RGB_M_X, _______, \
    _______, _______, UG_HUED, UG_SATD, UG_VALD,  _______,    _______, _______, RGB_M_R, _______, KC_PSCR, _______, \
    _______, _______, RGB_M_P, _______, _______, _______,    _______, _______, _______, _______, _______, _______ \
)
};

void keyboard_post_init_user(void) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    set_single_persistent_default_layer(_QWERTY);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      rgblight_disable();
      if (is_backlight_enabled()) {
        breathing_disable();
      }
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return true;
    default:
      return true;
  }
}
