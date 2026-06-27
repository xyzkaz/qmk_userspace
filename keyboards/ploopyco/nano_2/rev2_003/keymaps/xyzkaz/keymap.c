#include QMK_KEYBOARD_H

#include "quantum.h"

extern bool is_drag_scroll;
extern uint16_t dpi_array[];

enum CustomLayer
{
    _BASE = 0,
    _SCROLL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( LT(_SCROLL, MS_BTN1) ),
    [_SCROLL] = LAYOUT( KC_NO ),
};

bool led_update_user(led_t led_state) {
    // hold / scroll lock on -> scroll mode
    is_drag_scroll = led_state.scroll_lock || IS_LAYER_ON(_SCROLL);

    // num lock on -> 2nd DPI
    if (led_state.num_lock) {
        pointing_device_set_cpi(dpi_array[0]);
    } else {
        pointing_device_set_cpi(dpi_array[1]);
    }

    return true;
}
