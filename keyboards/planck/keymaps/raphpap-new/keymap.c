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

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers { _QWERTY, _LOWER, _RAISE, _ACCENT, _ADJUST };

enum planck_keycodes { QWERTY = SAFE_RANGE, BACKLIT, O_CIRCUM };

// tap dance definitions
typedef struct {
    bool is_press_action;
    int  state;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD = 2, DOUBLE_TAP = 3, DOUBLE_HOLD = 4, DOUBLE_SINGLE_TAP = 5, TRIPLE_TAP = 6, TRIPLE_HOLD = 7 };

enum { TD_USER = 0, TD_A_CIRC = 1, TD_E_CIRC = 2, TD_E_TREM = 3, TD_I_TREM = 4, TD_O_CIRC = 5 };

int  cur_dance(qk_tap_dance_state_t *state);
void user_finished(qk_tap_dance_state_t *state, void *user_data);
void user_reset(qk_tap_dance_state_t *state, void *user_data);
void a_circ_finished(qk_tap_dance_state_t *state, void *user_data);
void a_circ_reset(qk_tap_dance_state_t *state, void *user_data);
void e_circ_finished(qk_tap_dance_state_t *state, void *user_data);
void e_circ_reset(qk_tap_dance_state_t *state, void *user_data);
void e_trem_finished(qk_tap_dance_state_t *state, void *user_data);
void e_trem_reset(qk_tap_dance_state_t *state, void *user_data);
void i_trem_finished(qk_tap_dance_state_t *state, void *user_data);
void i_trem_reset(qk_tap_dance_state_t *state, void *user_data);
void o_circ_finished(qk_tap_dance_state_t *state, void *user_data);
void o_circ_reset(qk_tap_dance_state_t *state, void *user_data);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ACCENT MO(_ACCENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | TAB  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift| USER |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Accent| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_LSFT, TD(TD_USER), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_NUBS, ACCENT, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, XXXXXXX, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

    /* Accent
     * ,-----------------------------------------------------------------------------------.
     * |      |   â  |   è  |   é  |   ë  |      |      |   ù  |   ï  |   ô  |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |   à  |      |   ê  |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |   ^  |   ¨  |   `  |   ç  |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ACCENT] = LAYOUT_planck_grid(_______, TD(TD_A_CIRC), KC_QUOT, KC_SLASH, TD(TD_E_TREM), XXXXXXX, KC_LBRC, KC_GRV, TD(TD_I_TREM), TD(TD_O_CIRC), XXXXXXX, _______, _______, KC_NUHS, XXXXXXX, TD(TD_E_CIRC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_LBRC, LSFT(KC_LBRC), LALT(KC_LBRC), KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   {  |   }  |   <  |   >  |  ~   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   [  |   ]  |   «  |   »  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(_______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_7), LALT(KC_8), LALT(KC_COMM), LALT(KC_DOT), LALT(KC_RBRC), _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_9), LALT(KC_0), LALT(KC_Z), LALT(KC_X), LSFT(KC_NUBS), _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),

    /* Raise V2
     * ,-----------------------------------------------------------------------------------.
     * |      |   !  |   @  |   #  |   $  |   %  |   ?  |   &  |   *  |   -  |   =  |  Del |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   (  |   )  |   _  |   +  |   `  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   '  |   "  |   '  |   "  |   |  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(_______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, LSFT(KC_6), KC_AMPR, KC_ASTR, KC_MINS, KC_EQL, KC_DEL, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, LALT(KC_NUHS), _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_COMM), LSFT(KC_DOT), LALT(KC_NUBS), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
    /* Adjust (Lower + Raise)
     *                      v------------------------RGB CONTROL--------------------v
     * ,-----------------------------------------------------------------------------------.
     * |      | Reset|Debug |      |      |      |      |      |      |BrgDwn| BrgUP|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |AudTog|      |      |Qwerty|      | Vol- | Vol+ | Play |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |MUSmod|MusTog|      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(_______, RESET, DEBUG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLCK, KC_PAUS, _______, _______, _______, _______, _______, AU_TOG, XXXXXXX, XXXXXXX, QWERTY, XXXXXXX, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______, MU_MOD, MU_TOG, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)

};

// #ifdef AUDIO_ENABLE
//   float my_song[][2] = SONG(QWERTY_SOUND);
// #endif

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            //      PLAY_SONG(my_song);
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 10;

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
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
#else
            tap_code(KC_PGUP);
#endif
        }
    }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
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

// tap dance declarations
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;
}

static tap xtap_state = {.is_press_action = true, .state = 0};

void user_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void user_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            tap_code(KC_R);
            tap_code(KC_A);
            tap_code(KC_P);
            tap_code(KC_H);
            tap_code(KC_A);
            tap_code(KC_E);
            tap_code(KC_L);
            tap_code(KC_DOT);
            tap_code(KC_P);
            tap_code(KC_A);
            tap_code(KC_P);
            tap_code(KC_I);
            tap_code(KC_L);
            tap_code(KC_L);
            tap_code(KC_O);
            tap_code(KC_N);
            tap_code(KC_DOT);
            tap_code(KC_1);
            tap_code16(KC_AT);
            tap_code(KC_G);
            tap_code(KC_M);
            tap_code(KC_A);
            tap_code(KC_I);
            tap_code(KC_L);
            tap_code(KC_DOT);
            tap_code(KC_C);
            tap_code(KC_O);
            tap_code(KC_M);
            break;
        case TRIPLE_TAP:
            tap_code(KC_R);
            tap_code(KC_P);
            tap_code(KC_A);
            tap_code(KC_P);
            tap_code(KC_I);
            tap_code(KC_L);
            tap_code(KC_L);
            tap_code(KC_O);
            tap_code(KC_N);
            tap_code16(KC_AT);
            tap_code(KC_M);
            tap_code(KC_I);
            tap_code(KC_R);
            tap_code(KC_E);
            tap_code(KC_G);
            tap_code(KC_O);
            tap_code(KC_DOT);
            tap_code(KC_C);
            tap_code(KC_O);
            tap_code(KC_M);
            break;
    }
}

void a_circ_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void a_circ_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code16(KC_LBRC);
            tap_code(KC_A);
            break;
    }
}

void e_circ_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void e_circ_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code16(KC_LBRC);
            tap_code(KC_E);
            break;
    }
}

void o_circ_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void o_circ_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code16(KC_LBRC);
            tap_code(KC_O);
            break;
    }
}

void e_trem_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void e_trem_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code16(LSFT(KC_LBRC));
            tap_code(KC_E);
            break;
    }
}

void i_trem_reset(qk_tap_dance_state_t *state, void *user_data) { xtap_state.state = 0; }
void i_trem_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code16(LSFT(KC_LBRC));
            tap_code(KC_I);
            break;
    }
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_USER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, user_finished, user_reset),
    [TD_A_CIRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_circ_finished, a_circ_reset),
    [TD_E_CIRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_circ_finished, e_circ_reset),
    [TD_O_CIRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o_circ_finished, o_circ_reset),
    [TD_E_TREM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_trem_finished, e_trem_reset),
    [TD_I_TREM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, i_trem_finished, i_trem_reset),
};
