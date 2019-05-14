/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ACCENT,
  _UPPER_ACCENT,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ACCENT MO(_ACCENT)
#define UP_ACC MO(_UPPER_ACCENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |ENTER |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_DQUO,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |ENTER |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_SLSH,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower V1
* ,-----------------------------------------------------------------------------------.
* | ESC  |   `  |   ^  |   ¨  |      |      |   /  |   (  |   )  |   <  |   >  | Bksp |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | TAB  |      |   è  |      |      |      |   |  |   {  |   }  |   '  |   "  |  `   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|   à  |   é  |   ù  |   ç  |      |   \  |   [  |   ]  |   «  |   »  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
// [_LOWER] = LAYOUT_planck_grid(
//   KC_ESC,   KC_GRAVE,    KC_CIRC,      UC(0x00A8),  _______,    _______, KC_SLSH,    KC_LPRN, KC_RPRN, KC_LT,       KC_GT,       KC_BSPC,
//   KC_TAB,   _______,     UC(0x00E8),   _______,     _______,    _______, UC(0x007C), KC_LCBR, KC_RCBR, KC_QUOT,     KC_DQUO,     KC_GRAVE,
//   KC_LSFT,  UC(0x00E0), UC(0x00E9),   UC(0x00F9),  UC(0x00E7),  _______, UC(0x005C), KC_LBRC, KC_RBRC, UC(0x00AB),  UC(0x00BB),  _______,
//   _______,  _______,     _______,      _______,     _______,    _______, _______,    _______, _______, _______,     _______,     _______
// ),

/* Raise V1
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   ?  |   &  |   =  |   *  |   +  |   -  |   0  |   1  |   2  |   3  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   !  |   @  |   #  |   $  |   %  |   _  |      |   4  |   5  |   6  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_RAISE] = LAYOUT_planck_grid(
//     KC_ESC,   KC_QUES, KC_AMPR, KC_EQL,  KC_ASTR, KC_PLUS, KC_MINS, KC_0,    KC_1,    KC_2,    KC_3,    KC_BSPC,
//     KC_TAB,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS, _______, KC_4,    KC_5,    KC_6,    KC_7,
//     KC_LSFT,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    _______,
//     _______,  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),

/* Adjust (Lower + Raise) V1
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_ADJUST] = LAYOUT_planck_grid(
//     _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
//     _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______,
//     _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// )

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Accent| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,       KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, UC(0x2603), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    ACCENT,  KC_LCTL,    KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   â  |   è  |   é  |   ë  |      |      |   (  |   )  |   <  |   >  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   à  |      |   ê  |      |      |      |   {  |   }  |   '  |   "  |  `   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ù  |      |      |   ç  |   î  |   ô  |   [  |   ]  |   «  |   »  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_LOWER] = LAYOUT_planck_grid(
//     KC_ESC,   UC(0x00E2), UC(0x00E8), UC(0x00E9),  UC(0x00EB), XXXXXXX,    XXXXXXX,    KC_LPRN, KC_RPRN, KC_LT,       KC_GT,       KC_BSPC,
//     KC_TAB,   UC(0x00E0), XXXXXXX,    UC(0x00EA),  XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LCBR, KC_RCBR, KC_QUOT,     KC_DQUO,     KC_GRAVE,
//     KC_LSFT,  UC(0x00F9), XXXXXXX,    XXXXXXX,     UC(0x00E7), UC(0x00EE), UC(0x00F4), KC_LBRC, KC_RBRC, UC(0x00AB),  UC(0x00BB),  UC(0x007C),
//     _______,  _______,    _______,    _______,     _______,    _______,    _______,    _______, _______, _______,     _______,     _______
// ),

/* Accent
 * ,-----------------------------------------------------------------------------------.
 * |      |   â  |   è  |   é  |   ë  |      |   û  |   ù  |   î  |   ô  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   à  |   ä  |   ê  |      |      |      |   ü  |   ï  |   ö  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ù  |      |      |   ç  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_ACCENT] = LAYOUT_planck_grid(
     _______,  UC(0x00E2), UC(0x00E8), UC(0x00E9),  UC(0x00EB), _______,  UC(0x00FB), UC(0x00F9), UC(0x00EE), UC(0x00F4),  _______, _______,
     _______,  UC(0x00E0), UC(0x00E4),  UC(0x00EA), _______,    _______,  _______,    UC(0x00FC), UC(0x00EF), UC(0x00F6),  _______, _______,
     UP_ACC,   UC(0x00F9), _______,     _______,    UC(0x00E7), _______,  _______,    _______,    _______,    _______,    _______, _______,
     _______,  _______,    _______,     _______,    _______,    _______,  _______,    _______,    _______,    _______,    _______, _______
 ),
 [_UPPER_ACCENT] = LAYOUT_planck_grid(
     _______,  UC(0x00C2), UC(0x00C8), UC(0x00C9),  UC(0x00CB), _______,  UC(0x00DB), UC(0x00D9), UC(0x00CE), UC(0x00D4),  _______, _______,
     _______,  UC(0x00C0), UC(0x00C4),  UC(0x00CA), _______,  _______,    _______,    UC(0x00DC), UC(0x00CF), UC(0x00D6),  _______, _______,
     _______,  UC(0x00D9),  _______,    _______,   UC(0x00C7), _______,  _______,     _______,     _______,   _______,    _______, _______,
     _______,  _______,     _______,    _______,   _______,    _______,  _______,     _______,    _______,   _______,     _______,   _______
 ),

/* Lower V2
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |      |      |      |      |      |      |   {  |   }  |   <  |   >  |  ~   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |   [  |   ]  |   «  |   »  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_ESC,   KC_1,       KC_2,       KC_3,        KC_4,       KC_5,       KC_6,       KC_7,    KC_8,    KC_9,        KC_0,        KC_BSPC,
    KC_TAB,   XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LCBR, KC_RCBR, KC_LT,       KC_GT,       KC_TILD,
    KC_LSFT,  XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LBRC, KC_RBRC, UC(0x00AB),  UC(0x00BB),  UC(0x005C),
    _______,  _______,    _______,    _______,     _______,    _______,    _______,    _______, _______, _______,     _______,     _______
),


/* Raise V2
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   !  |   @  |   #  |   $  |   %  |   ?  |   &  |   *  |   -  |   =  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |      |      |      |      |      |      |   (  |   )  |   _  |   +  |   `  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |   '  |   "  |   |  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_ESC,   KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_QUES, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_DEL,
    KC_TAB,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_GRAVE,
    KC_LSFT,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, KC_DQUO, UC(0x007C),
    _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______
),



/* Adjust (Lower + Raise) V2
 * ,-----------------------------------------------------------------------------------.
 * | Reset|Qwerty|      |Plover|      |      | Mute | VolUP| VolDo|MIDIon|MIDIof|  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Debug |      |      |Dvorak|      |      |      | NxtTr|Play/P|Aud on|Aud of|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Colemk|      |TermON|TermOf|      |      |Mus on|Musoff|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Voice-|Voice+|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   QWERTY,  _______, PLOVER,  _______, _______, KC_MUTE,  KC_MNXT, KC_VOLD, MI_ON,  MI_OFF, KC_DEL ,
    DEBUG,   _______, _______, DVORAK,  _______, _______, _______,  KC_VOLU, KC_MPLY, AU_ON,  AU_OFF, _______,
    _______, _______, _______, COLEMAK, _______, TERM_ON, TERM_OFF, _______, _______, MU_ON,  MU_OFF, _______,
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, MUV_DE, MUV_IN, _______
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

void matrix_init_user(void) {
  set_unicode_input_mode(UC_OSX);
}
