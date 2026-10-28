// SPDX-License-Identifier: MIT

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT 4
#define LED_FLAG_UNDERGLOW 0x02
#define HAS_FLAGS(bits, flags) (((bits) & (flags)) == (flags))

typedef struct {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} HSV;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

typedef struct {
    uint8_t flags[RGB_MATRIX_LED_COUNT];
} led_config_t;

uint32_t     layer_state         = 1;
uint32_t     default_layer_state = 1;
led_config_t g_led_config        = {.flags = {LED_FLAG_UNDERGLOW, 0, LED_FLAG_UNDERGLOW, 0}};
static RGB   colors[RGB_MATRIX_LED_COUNT];

uint8_t get_highest_layer(uint32_t state) {
    uint8_t result = 0;
    while (state >>= 1) {
        result++;
    }
    return result;
}

uint8_t rgb_matrix_get_val(void) {
    return 100;
}

RGB hsv_to_rgb(HSV hsv) {
    // The harness preserves HSV fields in RGB slots; color conversion belongs to QMK.
    return (RGB){.r = hsv.h, .g = hsv.s, .b = hsv.v};
}

void rgb_matrix_set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
    colors[index] = (RGB){.r = red, .g = green, .b = blue};
}

#include "../qmk/layer_rgb_underglow.c"

static void clear_colors(void) {
    for (uint8_t index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        colors[index] = (RGB){0};
    }
}

int main(void) {
    clear_colors();
    assert(rgb_matrix_indicators_user());
    assert(colors[0].g == 0);
    assert(colors[0].b == 100);
    assert(colors[1].r == 0 && colors[1].g == 0 && colors[1].b == 0);

    clear_colors();
    layer_state = (1u << 2) | (1u << 5);
    assert(rgb_matrix_indicators_user());
    assert(colors[0].r == LAYER_RGB_HUE_5);
    assert(colors[0].g == 255);
    assert(colors[2].r == LAYER_RGB_HUE_5);
    assert(colors[3].r == 0 && colors[3].g == 0 && colors[3].b == 0);

    puts("OK: highest layer wins and only underglow LEDs are changed.");
    return 0;
}
