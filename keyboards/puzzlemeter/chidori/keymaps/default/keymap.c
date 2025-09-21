/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
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

#include "board.h"

enum layer_number { _QWERTY = 0, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NEW_SAFE_RANGE
};

enum {
  TT_CLN,
  TT_LINE,
};

void keyboard_post_init_user(void) {
    set_single_persistent_default_layer(_QWERTY);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
    }
    return true;
}

tap_dance_action_t tap_dance_actions[] = {
  [TT_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
  [TT_LINE] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer mirrors keyboards/keyball/keyball39/keymaps/takashicompany as closely as possible.
   * Extra outer-column keys remain for Chidori-specific positions and duplicate nearby functions.
   */
    [_QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,        KC_I,      KC_O,        KC_P,  KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,        KC_K,      KC_L,        KC_ENT, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,        KC_COMM,   KC_DOT, RSFT_T(KC_SLSH), KC_RSFT,
      KC_LGUI, KC_LALT, KC_LCTL, LSFT_T(KC_ESC), LT(1,KC_TAB), LT(3,KC_SPC),  KC_BSPC, LT(2,KC_SCLN), _______,   _______,    KC_LNG1, KC_LNG2
    ),

 /* Lower layer matches the Keyball function layer for symbols and navigation. */
    [_LOWER] = LAYOUT(
      _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),           S(KC_6), S(KC_7), S(KC_8),    S(KC_9),     S(KC_0), KC_BSPC,
      _______,   KC_F1,  KC_F2,    KC_F3,  KC_F4,    KC_F5,           KC_F6, S(KC_EQL),  KC_EQL,   KC_LBRC,      KC_RBRC, KC_ENT,
      _______,   KC_F6,  KC_F7,    KC_F8,  KC_F9,   KC_F10,           KC_F12, S(KC_BSLS), TD(TT_LINE), KC_QUOT,      KC_RSFT, KC_TAB,
      _______, _______, _______, _______, _______, _______,           TO(2),     TO(0),   _______,   KC_RALT,    KC_RGUI, S(KC_QUOT)
    ),

  /* Raise layer keeps navigation clustered like the Keyball layout, using standard keys available on Chidori. */
    [_RAISE] = LAYOUT(
      _______,  KC_GRV,    KC_1,    KC_2,   KC_3,   S(KC_MINS),            KC_MINS,    KC_HOME,     KC_UP,    KC_END,    KC_AUDIO_MUTE, _______,
      _______,  KC_BSLS,   KC_4,    KC_5,   KC_6,   TD(TT_CLN),            _______, KC_LEFT,   KC_DOWN,    KC_RIGHT,   LGUI(LCTL(KC_Q)), KC_ENT,
      _______,  LGUI(LSFT(KC_4)),  KC_7,    KC_8,   KC_9,         KC_0,    RCTL(KC_LEFT), RCTL(KC_RIGHT), KC_PGUP, KC_PGDN, _______,   _______,
      _______, _______, _______, _______, _______,  _______,              TO(_LOWER), _______,   _______,    _______,    _______,   KC_LNG1
    ),

  /* Adjust layer retains utility controls that remain relevant on Chidori. */
    [_ADJUST] = LAYOUT(
      _______, QK_RBT,   _______, _______, _______, _______,           _______, QWERTY,  KC_LNG1, KC_LNG2,  _______, KC_INS,
      _______, _______, _______, _______, _______, AG_NORM,           AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SCRL, KC_PAUS,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    )
};
