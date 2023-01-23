#include QMK_KEYBOARD_H
#include <stdio.h>
#include "print.h"
#include "oled/bongocat.h"
#include "oled/layers.h"
#include "oled/kb_state.h"

// KEYMAP CONFIG
enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST,
    _DEVOPT,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_CAPS, KC_MUTE, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LALT, KC_LGUI, MO(2), KC_SPC, KC_ENT, MO(1), KC_BSPC, KC_RGUI),
                                                              [1] = LAYOUT(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_PPLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, MO(2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT(KC_TRNS, MO(4), KC_NO, KC_NO, KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TILD, KC_GRV, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(1), KC_NO, KC_NO),
                                                              [3] = LAYOUT(RGB_MOD, RGB_RMOD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, NK_TOGG, KC_NO, KC_NO, KC_NO, EE_CLR, QK_BOOT, KC_MNXT, KC_VOLU, KC_BRIU, KC_WH_U, KC_MS_L, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_VOLD, KC_BRID, KC_WH_D, KC_BTN1, KC_BTN2, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_MPLY, KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO),
                                                              [4] = LAYOUT(QK_BOOT, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)};
layer_state_t          layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {[_QWERTY] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [_LOWER] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_RAISE] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_ADJUST] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_DEVOPT] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}};
#endif

// OLED CONFIG
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_270; // flips the display 180 degrees if offhand
    return OLED_ROTATION_0;
}

bool should_process_keypress(void) {
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    bongocat_process_record_user(keycode, record);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_set_cursor(0, 0);
        oled_write_ln("preyneyv (Vayne):\nRespawning in 40s", false);
    } else {
        bongocat_render();
        layers_render();
        kb_state_render();
    }
    return false;
}
