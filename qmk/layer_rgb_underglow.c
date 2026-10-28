// SPDX-License-Identifier: MIT
// Copyright (c) 2026 QMK Layer RGB Underglow contributors
//
// Copy this file into a QMK keymap or include it from keymap.c.
// Override the layer and color macros before including it when needed.

#ifdef RGB_MATRIX_ENABLE

#    ifndef LAYER_RGB_LAYER_0
#        define LAYER_RGB_LAYER_0 0
#    endif
#    ifndef LAYER_RGB_LAYER_1
#        define LAYER_RGB_LAYER_1 1
#    endif
#    ifndef LAYER_RGB_LAYER_2
#        define LAYER_RGB_LAYER_2 2
#    endif
#    ifndef LAYER_RGB_LAYER_3
#        define LAYER_RGB_LAYER_3 3
#    endif
#    ifndef LAYER_RGB_LAYER_4
#        define LAYER_RGB_LAYER_4 4
#    endif
#    ifndef LAYER_RGB_LAYER_5
#        define LAYER_RGB_LAYER_5 5
#    endif
#    ifndef LAYER_RGB_LAYER_6
#        define LAYER_RGB_LAYER_6 6
#    endif
#    ifndef LAYER_RGB_LAYER_7
#        define LAYER_RGB_LAYER_7 7
#    endif

#    ifndef LAYER_RGB_HUE_1
#        define LAYER_RGB_HUE_1 24
#    endif
#    ifndef LAYER_RGB_HUE_2
#        define LAYER_RGB_HUE_2 128
#    endif
#    ifndef LAYER_RGB_HUE_3
#        define LAYER_RGB_HUE_3 170
#    endif
#    ifndef LAYER_RGB_HUE_4
#        define LAYER_RGB_HUE_4 0
#    endif
#    ifndef LAYER_RGB_HUE_5
#        define LAYER_RGB_HUE_5 195
#    endif
#    ifndef LAYER_RGB_HUE_6
#        define LAYER_RGB_HUE_6 85
#    endif
#    ifndef LAYER_RGB_HUE_7
#        define LAYER_RGB_HUE_7 43
#    endif

bool rgb_matrix_indicators_user(void) {
    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    HSV           hsv   = {.h = 0, .s = 0, .v = rgb_matrix_get_val()};

    switch (layer) {
        case LAYER_RGB_LAYER_0:
            // White: saturation zero makes the hue irrelevant.
            hsv.s = 0;
            break;
        case LAYER_RGB_LAYER_1:
            hsv.h = LAYER_RGB_HUE_1;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_2:
            hsv.h = LAYER_RGB_HUE_2;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_3:
            hsv.h = LAYER_RGB_HUE_3;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_4:
            hsv.h = LAYER_RGB_HUE_4;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_5:
            hsv.h = LAYER_RGB_HUE_5;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_6:
            hsv.h = LAYER_RGB_HUE_6;
            hsv.s = 255;
            break;
        case LAYER_RGB_LAYER_7:
            hsv.h = LAYER_RGB_HUE_7;
            hsv.s = 255;
            break;
        default:
            // Unmapped layers fall back to white.
            hsv.s = 0;
            break;
    }

    const RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        if (HAS_FLAGS(g_led_config.flags[index], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
        }
    }

    // Preserve any keyboard-level indicator processing.
    return true;
}

#endif // RGB_MATRIX_ENABLE
