#include QMK_KEYBOARD_H

#include "eeconfig.h"
#include "keymap_jp.h"
#include <sendstring_jis.h>  // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避
#include <send_string_keycodes.h>

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum {
  _QWERTY = 0,
  _MAC,
  _LOWER,
  _RAISE,
  _MAC_LOWER,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MAC,
  MC_DELK,
  MC_ENTO,
  MC_CLEFT,
  MC_CRGHT,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER LT(_LOWER, KC_MHEN)	// タップで無変換     ホールドでLower
#define RAISE LT(_RAISE, KC_HENK)	// タップで変換       ホールドでRaise
#define EMACS MO(_LOWER)          // EMacs風
#define SPC_ADJ LT(_ADJUST, KC_SPC)

//#define META_TAB LT(_META, KC_TAB) // タップでTab     ホールドでMeta
#define SFT_UNDS SFT_T(JP_UNDS)
#define SFT_BSLS SFT_T(JP_BSLS)
#define ALT_KANA ALT_T(JP_MKANA)
#define ALT_EISU ALT_T(JP_MEISU)

#define LOWER_M LT(_MAC_LOWER, JP_MEISU)	// タップで無変換     ホールドでLower
#define RAISE_M LT(_RAISE, JP_MKANA)	// タップで変換       ホールドでRaise

#define KC_L1 KC_LGUI
#define KC_L2 KC_LALT
#define KC_L3 LOWER
#define KC_L4 KC_SPC
#define KC_L5 KC_LCTRL
#define KC_L6 KC_BSPC

#define KC_R1 KC_RGUI
#define KC_R2 KC_RALT
#define KC_R3 RAISE
#define KC_R4 KC_SPC
#define KC_R5 KC_ENT
#define KC_R6 KC_DEL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   @  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Emcs |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |   :  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | Bksp |  Del |   N  |   M  |   ,  |   .  |   /  |BSL/Sf|
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  GUI |  Alt |Space | Lower| Enter|Enter |Raise |Space |  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT, \
  KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_BSPC,  KC_DEL,  KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, SFT_BSLS, \
                    KC_LGUI, KC_LALT, KC_ENT,  LOWER,  KC_SPC,   KC_SPC,  RAISE,   KC_ENT,  KC_RALT, KC_RGUI\
),

/* Mac
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   @  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |   :  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | Bksp |  Del |   N  |   M  |   ,  |   .  |   /  | _/Sf |
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  GUI |  Alt |Space |LOWER_M|Enter|Enter |RAISE_M|Space|  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_MAC] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT, \
    KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC,  KC_DEL, KC_N,    KC_M,    JP_COMM, JP_DOT,  JP_SLSH, SFT_UNDS, \
                      KC_LGUI, KC_LALT, KC_ENT,  LOWER_M, KC_SPC,   KC_SPC, RAISE_M, KC_ENT,  KC_RALT, KC_RGUI\
    ),

/* Lower
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |   -  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |CtlTab|  F11 |  F12 |  End |   R  |   T  |             | CtrlY|   U  |   I  | EntO |   ↑  |   @  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Ctrl | Home | CtrlS|  Del |   →  |   G  |             |  BS  |   J  | DelK |   L  |   ;  |   :  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift| CtrlZ| CtrlX| CtrlC| CtrlV|   ←  | Bksp |  Del |   ↓  |   M  | Ctrl,| Ctrl.|   /  |BSL/Sf|
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  GUI |  Alt |CtrlSp|Lower | Enter|Enter |Raise| CtrlSp|  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  _______,      KC_F1,      KC_F2,      KC_F3,      KC_F4,       KC_F5,                       KC_F6,       KC_F7,   KC_F8,         KC_F9,   KC_F10,  JP_MINS, \
  LCTL(KC_TAB), KC_F11,     KC_F12,     KC_END,     KC_R,        KC_T,                        LCTL(KC_Y),  KC_U,    KC_I,          MC_ENTO, KC_UP,   JP_AT, \
  _______,      KC_HOME,    LCTL(KC_S), KC_DEL,     KC_RGHT,     KC_G,                        KC_BSPC,     KC_J,    MC_DELK,       KC_L,    JP_SCLN, JP_COLN, \
  _______,      LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),  KC_LEFT,  _______,  _______, KC_DOWN,     KC_M,    LCTL(KC_COMMA),LCTL(KC_DOT),JP_SLSH, SFT_BSLS, \
                            _______,    _______,    _______,     _______,  _______,  _______, _______,     _______, _______,       _______\
),

/* Raise
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | ESC  |   !  |   "  |   #  |   $  |   %  |             |   &  |   '  |   (  |   )  |   ^  |   =  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  |   Q  | CtrlW|  End |   R  |   ~  |             |   ¥  |   μ  |   [  |   ]  | PgUp |   `  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Ctrl | Home | CtrlS|  Del | Ctrl→|   G  |             |  BS  |   J  |   {  |   }  |   +  |   *  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift| CtrlZ| CtrlX| CtrlC| CtrlV| Ctrl←| Bksp |  Del | PgDn |   M  |   <  |   >  |   ?  |   _  |
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  GUI |  Alt |Lower |Space | Ctrl |Enter |Space | Raise|  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  _______,   JP_EXLM,     JP_DQT,     JP_HASH,    JP_DLR,         JP_PERC,                     JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC, JP_EQL, \
  KC_TAB,    KC_Q,        LCTL(KC_W), KC_END,     KC_R,           JP_TILD,                     JP_YEN,  JP_PIPE, JP_LBRC, JP_RBRC, KC_PGUP, JP_GRV, \
  _______,   KC_HOME,     LCTL(KC_S), KC_DEL,     MC_CRGHT,       KC_G,                        KC_BSPC, KC_J,    JP_LCBR, JP_RCBR, JP_PLUS, JP_ASTR, \
  _______,   LCTL(KC_Z),  LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),     MC_CLEFT, _______,  _______, KC_PGDN, KC_M,    JP_LT,   JP_GT,   JP_QUES, JP_UNDS, \
                          _______,    _______,    _______,        _______,  _______,  _______, _______, _______, _______, _______\
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |             |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  | lclk |  M↑  | rclk |   R  |   T  |             |   Y  |   U  |   I  |   O  |   ↑  |   @  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Ctrl |  M←  |  M↓  |  M→  |   →  |   G  |             |   H  |   J  |   K  |   L  |   ;  |   :  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift|  F6  |  F7  |  F8  |  F9  |  F10  | Bksp |  Del |   ↓  |   M  |   ,  |   .  |   /  |BSL/Sf|
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  F11 |  F12 |Space | Lower| Enter|Enter |Raise |Space |  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY, \
  KC_ACL0, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MAC, \
  KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_R, KC_RGHT, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_ACL2, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                    KC_F11,  KC_F12,  _______, _______, _______,  _______, _______, _______, _______, _______\
),

/* Lower_Mac */
[_MAC_LOWER] = LAYOUT( \
  KC_ESC,       KC_F1,      KC_F2,       KC_F3,      KC_F4,      KC_F5,                       KC_F6,             KC_F7,   KC_F8,   KC_F9,   KC_F10,  JP_MINS, \
  LCTL(KC_TAB), KC_F11,     KC_F12,      LCTL(KC_E), KC_R,       KC_T,                        LGUI(LSFT(KC_Y)),  KC_U,    KC_I,    MC_ENTO, KC_UP,   JP_AT, \
  _______,      LCTL(KC_A),LGUI(KC_S),   KC_DEL,     KC_RGHT,    KC_G,                        KC_BSPC,           KC_J,    MC_DELK, KC_L,    JP_SCLN, JP_COLN, \
  _______,      LGUI(KC_Z), LGUI(KC_X),  LGUI(KC_C), LGUI(KC_V), KC_LEFT,  _______,  _______, KC_DOWN,           KC_M,    KC_COMMA,KC_DOT,  JP_SLSH, SFT_BSLS, \
                            _______,     _______,    _______,    _______,  _______,  _______, _______,           _______, _______, _______\
)

};

  uint32_t layer_state_set_user(uint32_t state) {
      switch (biton32(default_layer_state)) {
          case _QWERTY:
              state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
              break;
          case _MAC:
              state = update_tri_layer_state(state, _MAC_LOWER, _RAISE, _ADJUST);
              break;
      }
      return state;
  }

  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;

      case MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_MAC);
        }
        return false;
        break;

      case MC_DELK:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_END) SS_UP(X_LSHIFT) SS_TAP(X_DELETE));
        }
        break;

      case MC_ENTO:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ENTER) SS_TAP(X_UP) SS_TAP(X_END));
        }
        break;

      case MC_CLEFT:
        if (record->event.pressed) {
          uint8_t layer = biton32(default_layer_state);
          if (layer == _QWERTY)
          {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_LEFT) SS_UP(X_LCTRL));
          }
          else
          {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
          }
        }
        break;

      case MC_CRGHT:
        if (record->event.pressed) {
          uint8_t layer = biton32(default_layer_state);
          if (layer == _QWERTY)
          {
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_RIGHT) SS_UP(X_LCTRL));
          }
          else
          {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
          }
        }
        break;

    }
    return true;
}
