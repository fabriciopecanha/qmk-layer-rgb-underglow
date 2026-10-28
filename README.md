# QMK Layer RGB Underglow

A small, vendor-neutral QMK snippet that colors only LEDs marked with `LED_FLAG_UNDERGLOW`, based on the highest active layer. Per-key RGB lighting remains available to the active RGB Matrix effect.

This package contains source code only. It does not include a keyboard definition, proprietary keymap, precompiled firmware, `.uf2` file, USB identifiers, EEPROM data, or vendor branding.

## Requirements

- QMK Firmware with `RGB_MATRIX_ENABLE = yes`.
- A correct `g_led_config` in which underglow LEDs carry `LED_FLAG_UNDERGLOW`.
- A keymap with layer numbers that can be mapped to the configuration macros in the snippet.

## Installation

1. Copy the contents of `qmk/layer_rgb_underglow.c` into your keymap's `keymap.c`, or include it through your own userspace structure.
2. Set `LAYER_RGB_LAYER_0` through `LAYER_RGB_LAYER_7` to your layer enum values. The defaults are numeric layers `0` through `7`.
3. Adjust the hue and saturation macros if desired.
4. If your keymap already defines `rgb_matrix_indicators_user()`, merge the loop and color selection into the existing callback. Do not define the callback twice.
5. Compile with the normal command for your keyboard and keymap.

Example:

```c
#define LAYER_RGB_LAYER_0 _BASE
#define LAYER_RGB_LAYER_1 _LOWER
#define LAYER_RGB_LAYER_2 _RAISE
#include "layer_rgb_underglow.c"
```

For a repository contribution, prefer copying the implementation into `keymap.c` and keeping the required QMK copyright/license header style.

## Default colors

| Layer | Color |
| --- | --- |
| 0 | White |
| 1 | Orange |
| 2 | Cyan |
| 3 | Blue |
| 4 | Red |
| 5 | Purple |
| 6 | Green |
| 7 | Yellow |
| Other | White |

Brightness follows the current RGB Matrix brightness. This snippet does not impose a board-specific brightness or current limit.

## Behavior and safety

- The highest active layer wins.
- Only LEDs carrying `LED_FLAG_UNDERGLOW` are changed.
- The callback returns `true` so keyboard-level indicator processing can continue.
- No firmware is flashed by this repository.
- Always keep a known-good firmware and follow the recovery procedure for your controller before testing a new build.

## Licensing note

The standalone snippet is MIT-licensed, which is GPL-compatible. QMK Firmware itself is GPL-licensed, and a compiled firmware remains subject to the licenses of the complete QMK tree and its platform dependencies. If you distribute a QMK binary, provide the complete corresponding source required by those licenses. This repository does not provide legal advice.

Official references:

- [QMK RGB Matrix indicators](https://docs.qmk.fm/features/rgb_matrix#indicators)
- [QMK license guidance](https://github.com/qmk/qmk_firmware/blob/master/docs/license_violations.md)

## Local validation

The package includes a small C harness that checks layer priority and confirms that only LEDs marked as underglow are changed:

```bash
cc -std=c11 -Wall -Wextra -Werror tests/test_layer_rgb.c -o /tmp/test_layer_rgb
/tmp/test_layer_rgb
python3 scripts/validate_package.py
```
