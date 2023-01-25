/* Copyright 2021 Moritz Plattner
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

enum layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _0,
    _1,
    _2,
    _3,
};

// Led indicator bool for auto shift
bool did_auto_shift_on = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_0] = LAYOUT_all(
        KC_DEL, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,  KC_LEAD,
        KC_HOME, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_END, KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_UP), LT(1, KC_RIGHT),
                 KC_LCTL,                   LM(1, MOD_LALT), KC_SPC,  LT(1, KC_SPC),          LT(1, KC_SPC),           LT(1, KC_LEFT),                            MT(MOD_RCTL, KC_DOWN)
    ),
    [_1] = LAYOUT_all(
        TO(0), KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LOCK,  KC_ASTG,
        TO(2), KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_UP, KC_TRNS,
        TO(3), KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_LEFT, KC_RIGHT,          KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_DOWN, KC_TRNS, KC_MNXT,
                 KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,                            KC_MPLY
    ),
    [_2] = LAYOUT_all(
        TO(1), KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_MINS,  KC_EQL,  KC_EQL,  KC_GRV,
        TO(0), KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TO(3), KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,                            KC_TRNS
    ),
    [_3] = LAYOUT_all(
        TO(1), KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
        TO(2), KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TO(0), KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,                            KC_TRNS
    )
};

// Register led indicator pin
void keyboard_pre_init_user(void) {
    setPinOutput(B6);  // initialize B0 for LED
    setPinOutput(C7);  // initialize B1 for LED
    setPinOutput(C6);  // initialize B1 for LED
}

void matrix_scan_user (void) {
    // Turn on 3rd led as low when auto shift is on
    if(did_auto_shift_on) {
        writePinLow(B6);
    }

    // Use led indicator to show which layer the keyboard currently on
    switch (get_highest_layer(layer_state)) {
        case _0:
            
            writePinHigh(B6);
            writePinHigh(C7);
            writePinHigh(C6);
            break; 
        case _1:
            // Light up first light
            writePinLow(C7);
            writePinHigh(B6);
            writePinHigh(C6);
            break;
        case _2:
             // Light up 1st and 2nd light
            writePinLow(C6);
            writePinLow(C7);
            writePinHigh(B6);
            break;
        case _3:
            // All lights up
            writePinLow(B6);
            writePinLow(C6);
            writePinLow(C7);
            break;
        default:
            writePinHigh(B6);
            writePinHigh(C7);
            writePinHigh(C6);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            case KC_ASTG:
                if (record->event.pressed) {
                    did_auto_shift_on = !did_auto_shift_on;
                }
                return true;
    }
    return true;
};