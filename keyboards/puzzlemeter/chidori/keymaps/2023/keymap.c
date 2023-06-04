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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { QWERTY = SAFE_RANGE };

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

enum {
  TT_LINE,
  TT_CLN,
  TT_QUO,
  TD_EMAIL,
  TD_ARR,
  TD_IME,
  TD_DOMAIN,
};

/* tap dance time */
void tdemail(tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING("${CKEY4}");
  } else {
    SEND_STRING("${CKEY5}");
  }
  reset_tap_dance (state);
}
void tdomain(tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING("${CKEY2}");
  } else {
    SEND_STRING("${CKEY1}");
  }
  reset_tap_dance (state);
}
void tdarr(tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING("->");
  } else {
    SEND_STRING("=>");
  }
  reset_tap_dance (state);
}
void tdime(tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    tap_code(KC_LNG1);
  } else {
    tap_code(KC_LNG2);
  }
  reset_tap_dance (state);
}

tap_dance_action_t tap_dance_actions[] = {
  [TT_LINE]  = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
  [TT_CLN]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
  [TT_QUO]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
  [TD_EMAIL] = ACTION_TAP_DANCE_FN(tdemail),
  [TD_ARR]   = ACTION_TAP_DANCE_FN(tdarr),
  [TD_IME]   = ACTION_TAP_DANCE_FN(tdime),
  [TD_DOMAIN] = ACTION_TAP_DANCE_FN(tdomain),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;:  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |  ,<  |  .>  |  Up  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | GUI  | Opt  | Tab  |Eisu  |LOWER |Space |             | Space| RAISE|  -_  | Left | Down | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    TD(TT_CLN), KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP, KC_SLSH,
      KC_LGUI,  KC_LALT,  KC_TAB, TD(TD_IME), LOWER,   KC_SPC,            KC_SPC,  RAISE,   TD(TT_LINE), KC_LEFT, KC_DOWN,   KC_RGHT
    ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CTRL |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  +   |   =  |   {  |   }  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | SHIFT|  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |  |   |   '  |  "   |  ;   | PgUp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CMD  | Opt   | ESC |email |      |      |             |      |      |  _   | LEFT | RIGHT| PgDn |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_LOWER] = LAYOUT(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      KC_LCTL,   KC_F1,  KC_F2,    KC_F3,  KC_F4,    KC_F5,           KC_F6, KC_PLUS, KC_EQL, KC_LCBR, KC_RCBR, KC_ENT,
      KC_LSFT,   KC_F7,  KC_F8,    KC_F9,  KC_F10,   KC_F11,          KC_F12, KC_PIPE, KC_QUOT, KC_DQUO, TD(TT_QUO), KC_PGUP,
      KC_LGUI, KC_LALT, KC_ESC, TD(TD_EMAIL), _______, _______,           _______, _______, KC_UNDS, KC_LEFT, KC_RIGHT, KC_PGDN
    ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |SHIFT |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |  =>  |   '  |  "   |  :   |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CMD  | Opt  |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_RAISE] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_DEL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_ENT,
      KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,            KC_F12,  TD(TD_ARR), KC_QUOT,  KC_DQUO, KC_COLON, KC_BSLS,
      KC_LGUI, KC_LALT, _______, _______, _______, _______,           _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |Qwerty| KANA | Eisu |      | Ins  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Caps |      |      |      |      | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |domain|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Home |PageDn|PageUp| End  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] = LAYOUT(
      _______, QK_BOOT,   _______, _______, _______, _______,           _______, QWERTY,  KC_LNG1, KC_LNG2,  _______, KC_INS,
      KC_CAPS, _______, _______, _______, _______, AG_NORM,           AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SCRL, KC_PAUS,
      _______, _______, _______, _______, _______, _______,           _______, TD(TD_DOMAIN), _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,           _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    )
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
