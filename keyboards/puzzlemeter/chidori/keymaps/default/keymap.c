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
  LOCKMAC,
  NEW_SAFE_RANGE
};

enum {
  TT_CLN,
  TT_QUO,
  TT_LINE,
};

/* tap dance */
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
        case LOCKMAC:
          if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LCTL("q")));
          }
          break;
    }
    return true;
}

tap_dance_action_t tap_dance_actions[] = {
  [TT_LINE]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, S(KC_MINS)),
  [TT_CLN]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
  [TT_QUO]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;:  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |  ,<  |  .>  |  /?  |  -_  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CMD  | Opt  | Ctrl |Shift |LOWER |ADJUST|             | Bksp | RAISE| Left | Down |  Up  | Right|
   * |      |      |      | Esc  | Tab  | Space|             |      |   :; |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,        KC_I,      KC_O, RSFT_T(KC_P), KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,        KC_K,      KC_L,   TD(TT_CLN),  KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,        KC_COMM,   KC_DOT,   KC_SLSH,  TD(TT_LINE),
      KC_LGUI, KC_LALT,  KC_LCTL, LSFT_T(KC_ESC),LT(1,KC_TAB),LT(3,KC_SPC),    KC_BSPC, LT(2,KC_SCLN),KC_LEFT,  KC_DOWN,     KC_UP,  KC_RIGHT
    ),

 /* Lower
  * ,-----------------------------------------.             ,---------------------------------------.
  * | Esc  |   !  |   @  |   #  |   $  |   %  |             |   ^  | &  |   *  |   (  |   )  | Bksp |
  * |------+------+------+------+------+------|             |------+----+------+------+------+------|
  * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |             |  -   | +  |   =  |   {  |   }  |Enter |
  * |------+------+------+------+------+------|             |------+----+------+------+------+------|
  * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 | |  |  F6  |  "'  |Shift | Tab  |
  * |------+------+------+------+------+------|             |------+----+------+------+------+------|
  * | CMD  | Opt  | Ctrl |Shift |LOWER |ADJUST|             |  TO  |    | Left | Down |  Up  | Right|
  * |      |      |      | Esc  | Tab  | Space|             |RAISE |    |      |      |      |      |
  * `-----------------------------------------'             `---------------------------------------'
  */
    [_LOWER] = LAYOUT(
      _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),           S(KC_6), S(KC_7), S(KC_8),    S(KC_9),     S(KC_0), KC_BSPC,
      _______,   KC_F1,  KC_F2,    KC_F3,  KC_F4,    KC_F5,          KC_MINS,S(KC_EQL),  KC_EQL,  S(KC_LBRC), S(KC_RBRC),  KC_ENT,
      _______,   KC_F6,  KC_F7,    KC_F8,  KC_F9,   KC_F10,          KC_F12, S(KC_BSLS),  KC_F6,  TD(TT_QUO),   KC_RSFT,  KC_TAB,
      _______, _______, _______, _______, _______, _______,          TO(2),   _______, _______,     _______,   _______, _______
    ),

  /* Raise
   * ,-------------------------------------------.             ,-------------------------------------------.
   * | Esc  |LOCK  |   1  |   2  |   3  |    _   |             |   -  |   [  |  Up  |  ]   |        | Bksp |
   * |------|------+------+------+------+--------|             |------+------+------+------+--------+------|
   * | Ctrl | \    |   4  |   5  |   6  |        |             |   :  | LEFT | Down |  [   |        |Enter |
   * |------|------+------+------+------+--------|             |------+------+------+------+--------+------|
   * |Shift | `~   |   7  |   8  |   9  |   0    |             |  TO  |      | Pgup | Pgup |        |   \  |
   * |      |      |      |      |      |        |             |QWERTY|      |      |      |        |      |
   * |------|------+------+------+------+--------|             |------+------+------+------+--------+------|
   * | CMD  | Opt  | Ctrl |Shift |LOWER |KC_LNG1 |             | TO   |RAISE | Left | Down |  Up    |Right |
   * |      |      |      | Esc  |      |        |             |LOWER |      |      |      |        |      |
   * `-------------------------------------------'             `-------------------------------------------'
   */
    [_RAISE] = LAYOUT(
      _______,   LOCKMAC,    KC_1,    KC_2,   KC_3,   S(KC_MINS),            KC_MINS, KC_LBRC,     KC_UP,  KC_RBRC, _______,   KC_BSPC,
      _______, KC_BSLS,    KC_4,    KC_5,   KC_6, _______,         S(KC_SCLN), KC_LEFT,   KC_DOWN,  KC_RGHT, _______,    KC_ENT,
      _______,  KC_GRV,    KC_7,    KC_8,   KC_9,         KC_0,         TO(0),  _______,   KC_PGUP,  KC_PGDN, _______,KC_BSLS,
      _______, _______, _______, _______,_______,  KC_LNG1,        TO(1),  _______, _______, _______, _______, _______
    ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |Qwerty| KANA | Eisu |      | Ins  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |domain|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Home |PageDn|PageUp| End  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] = LAYOUT(
      _______, QK_RBT,   _______, _______, _______, _______,           _______, QWERTY,  KC_LNG1, KC_LNG2,  _______, KC_INS,
      _______, _______, _______, _______, _______, AG_NORM,           AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SCRL, KC_PAUS,
      _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    )
};
