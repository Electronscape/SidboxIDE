# GamerGirl Stage 4.19 — Programmer Calculator bit-row layout

Based on Stage 4.18 (including the now-working centrally themed combo popups).

## Changed production file
- `mainwindow.cpp` (IDE source root)

## What changed
- The binary bit rows now appear from most significant to least significant.
- In 32-bit mode, the first row is `31-16` and the second is `15-0`.
- In 64-bit mode, the rows are `63-48`, `47-32`, `31-16`, `15-0`.
- Each label lists bit numbers in the same left-to-right order as its 16 toggle buttons.
- Removed unnecessary minimum widths on the individual bit buttons and reduced nibble gaps so the rightmost bits stay inside the narrow calculator sidebar.
- The bits themselves, click-to-toggle behaviour, calculator operations and values are untouched.

## Installation
Replace **only** `mainwindow.cpp` in your Stage 4.18 source tree, then rebuild your IDE. No CMake changes or firmware changes required.

## Fedora visual verification
1. Open the calculator in 32-bit mode: the first row should read `31-16`, the second `15-0`, with 16 fully visible buttons per row.
2. Click bit 31 (top-left): HEX should show `0x80000000`; click it again to reset.
3. Click bit 0 (bottom-right): HEX should show `0x00000001`.
4. Switch to 8-, 16-, and 64-bit modes and verify the labels and toggles stay in range.
5. Resize the left project pane and check the last button no longer overflows at normal width.

Source regression tests pass. Native Qt6 GUI compilation/rendering require your Fedora machine.
