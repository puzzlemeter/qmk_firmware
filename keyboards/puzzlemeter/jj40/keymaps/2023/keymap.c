#include QMK_KEYBOARD_H

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _CALC
};

enum custom_keycodes { QWERTY = SAFE_RANGE, CALC };

#define QWERTY  MO(_QWERTY)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)
#define CALC    MO(_CALC)
#define JP_UNDS S(KC_MINS) // _

enum {
  TT_LINE,
  TT_JLINE,
  TT_QUO,
  TT_CLN,
  TT_JCLN,
  TD_EMAIL,
  TD_ARR,
  TD_IME,
  TD_DOMAIN
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
    SEND_STRING("${CKEY3}");
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
  [TT_JLINE] = ACTION_TAP_DANCE_DOUBLE(JP_UNDS, KC_MINS),
  [TT_LINE]  = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
  [TT_QUO]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
  [TT_CLN]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLON),
  [TT_JCLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_EMAIL] = ACTION_TAP_DANCE_FN(tdemail),
  [TD_ARR]   = ACTION_TAP_DANCE_FN(tdarr),
  [TD_IME]   = ACTION_TAP_DANCE_FN(tdime),
  [TD_DOMAIN] = ACTION_TAP_DANCE_FN(tdomain),
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
  KC_ESC,    KC_Q,    KC_W,                   KC_E,  KC_R,   KC_T,   KC_Y,  KC_U,         KC_I,    KC_O,      KC_P, KC_BSPC,  \
  KC_LCTL,   KC_A,    KC_S,                   KC_D,  KC_F,   KC_G,   KC_H,  KC_J,         KC_K,    KC_L, TD(TT_CLN), KC_ENT,  \
  KC_LSFT,   KC_Z,    KC_X,                   KC_C,  KC_V,   KC_B,   KC_N,  KC_M,      KC_COMM,  KC_DOT,      KC_UP, KC_SLSH,  \
  KC_LGUI, KC_LALT, KC_TAB, TD(TD_IME), LOWER, KC_SPC, KC_SPC, RAISE,  TD(TT_LINE), KC_LEFT,    KC_DOWN, KC_RIGHT  \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  +   |   =  |   {  |   }  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SHIFT|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |   |   '  |  "   |  "'  | PgUp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CMD  | Opt   | ESC |email |      |      |      |      |  _   | LEFT | RIGHT| PgDn |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM,   KC_AT,  KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,   KC_RPRN,  KC_BSPC, \
  KC_LCTL,   KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_F5,   KC_F6,  KC_PLUS, KC_EQL, KC_LCBR,   KC_RCBR,  KC_ENT, \
  KC_LSFT,   KC_F7,   KC_F8,    KC_F9,  KC_F10,   KC_F11,  KC_F12, KC_PIPE, KC_QUOT, KC_DQUO, TD(TT_QUO), KC_PGUP, \
  KC_LGUI, KC_LALT,  KC_ESC,  TD(TD_EMAIL), _______,  _______, _______, _______, KC_UNDS, KC_LEFT,   KC_RIGHT, KC_PGDN \
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
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,     KC_9,    KC_0, KC_BSPC, \
  KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC,  KC_ENT, \
  KC_LSFT,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  TD(TD_ARR), KC_QUOT,  KC_DQUO, KC_COLON, KC_BSLS, \
  KC_LGUI, KC_LCTL, _______, _______, _______, _______, _______, _______,KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* CALC
 * ,-----------------------------------------.--------------,----------------------------.
 * |  Esc |      | DOWN |   UP |      |      |      |QWERTY |   7  |   8  |   9  |  Bksp |
 * |------+------+------+------+------+------|------+-------|------+------+------|-------|
 * |      |      | LEFT | RIGHT| PgDn | PgUp |      |   /   |   4  |   5  |   6  |   -   |
 * |------+------+------+------+------+------|------+-------|------+------+------+-------+
 * |      |      |      |      |      |      |      |   =   |   1  |   2  |   3  |   +   |
 * |------+------+------+------+------+------|------+-------|-------------+------|-------|
 * |      |      |      |      |Lower |      |      | Raise |   0  |   *  |   .  | Enter |
 * `-----------------------------------------'--------------`----------------------------'
 */
[_CALC] = LAYOUT_ortho_4x12( \
  _______, _______, KC_DOWN,    KC_UP, _______, _______, _______, QWERTY, KC_P7,    KC_P8,   KC_P9,   KC_BSPC, \
  _______, _______, KC_LEFT, KC_RIGHT, KC_PGDN, KC_PGUP, _______, KC_SLSH, KC_P4,    KC_P5,   KC_P6,   KC_PMNS,  \
  _______, _______, _______,  _______, _______, _______, _______, KC_EQL,  KC_P1,    KC_P2,   KC_P3,   KC_PPLS, \
  _______, _______, _______,  _______, _______, _______, _______, _______, KC_P0,   KC_ASTR, KC_PDOT, KC_PENT \
),

/* ADJUST
 * ,------------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |Qwerty|  F9  | F10  | F11  | F12   |
 * |------+------+------+------+------+-------------+------+------+------+------+------ |
 * |      | RGB  | RGB  | RGB  | RGB  |  BL  |  BL  |  BL  |  BL  |Swirl | Xmas |       |
 * |      | Togl | Hue+ | Sat+ | Brt+ | Togl |Breath| Brt+ | Brt- |      |      |       |
 * |------+------+------+------+------+------|------+------+------+------+------+------ |
 * |      |      | RGB  | RGB  | RGB  |      |      |      |      |      |      |       |
 * |      | CALC | Hue- | Sat- | Brt- |      |      |domain|Rnbow |      |PrScr |       |
 * |------+------+------+------+------+------+------+------+------+------+------+------ |
 * |      |      | RGB  |      |      |      |      |      |      |      |      |       |
 * |      |      | Mode |      |      |      |      |      |      |      |      |       |
 * `------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   QWERTY,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, BL_TOGG,    BL_BRTG, BL_ON,  BL_STEP, RGB_M_SW,RGB_M_X, _______, \
    _______,    CALC, RGB_HUD, RGB_SAD, RGB_VAD,  _______,    _______, TD(TD_DOMAIN), RGB_M_R, _______, KC_PSCR, _______, \
    _______, _______, RGB_MOD, _______, _______, _______,    _______, _______, _______, _______, _______, _______ \
)
};

void keyboard_post_init_user(void) {
    rgblight_enable();
    // ref rgblight.h
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
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
        oneshot_disable();
      }
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return true;
    case CALC:
      rgblight_enable();
      rgblight_setrgb(15, 120, 155);
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CALC);
      }
      return true;
    default:
      return true;
  }
}
