/* Copyright 2019 zk-phi
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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layers {
    DEFAULT,
    RAISE,
    LOWER,
    ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  CFO_DOMAIN = SAFE_RANGE,
  FREEE_DOMAIN,
  TEST_ACT,
  P_EMAIL,
  FULL_NAME,
  NEW_SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CFO_DOMAIN:
            if (record->event.pressed) {
                SEND_STRING("CKEY1");
            }
            return false;
        case FREEE_DOMAIN:
            if (record->event.pressed) {
                SEND_STRING("CKEY2");
            }
            return false;
        case TEST_ACT:
            if (record->event.pressed) {
                SEND_STRING("CKEY3");
            }
            return false;
        case P_EMAIL:
            if (record->event.pressed) {
                SEND_STRING("CKEY5");
            }
            return false;
        case FULL_NAME:
            if (record->event.pressed) {
                SEND_STRING("CKEY6");
            }
            return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        LT(RAISE, KC_LANG1), KC_MS_U,   LT(LOWER, KC_LANG2),
        KC_MS_L, KC_MS_D, KC_MS_R
    ),
    [RAISE] = LAYOUT(
        _______, CFO_DOMAIN, MO(ADJUST),
        FREEE_DOMAIN, TEST_ACT, P_EMAIL
    ),
    [LOWER] = LAYOUT(
        MO(ADJUST), KC_ENT, _______,
        KC_BTN1,KC_BTN2, KC_ESC
    ),
    [ADJUST] = LAYOUT(
        _______, KC_DEL, _______,
        FULL_NAME, KC_COLN, KC_BSLS
    )
};
