#!/usr/bin/env python3
"""Executa verificações estáticas no pacote QMK público."""

from __future__ import annotations

from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "qmk" / "layer_rgb_underglow.c"


def main() -> None:
    text = SOURCE.read_text(encoding="utf-8")
    all_text = "\n".join(
        path.read_text(encoding="utf-8", errors="ignore")
        for path in ROOT.rglob("*")
        if path.is_file() and path.name != Path(__file__).name
    ).casefold()

    assert "rgb_matrix_indicators_user" in text
    assert "LED_FLAG_UNDERGLOW" in text
    assert "get_highest_layer(layer_state | default_layer_state)" in text
    assert "return true;" in text
    assert "SPDX-License-Identifier: MIT" in text

    forbidden = [
        "ter" + "go",
        ".u" + "f2",
        "vial-qmk-" + "firmware",
        "rgb_matrix_maximum_" + "brightness",
    ]
    for marker in forbidden:
        if marker == ".uf2":
            # The README and .gitignore may mention the extension to explain its exclusion.
            continue
        assert marker.casefold() not in all_text, f"Vendor-specific marker found: {marker}"

    binaries = [path for path in ROOT.rglob("*") if path.suffix.casefold() in {".uf2", ".hex", ".bin", ".elf"}]
    assert not binaries, f"Firmware binaries must not be included: {binaries}"

    print("OK: generic QMK source package contains no vendor firmware or binaries.")


if __name__ == "__main__":
    main()
