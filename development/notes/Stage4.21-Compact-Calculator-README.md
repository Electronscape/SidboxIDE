# GamerGirl Stage 4.21 — Compact Programmer Calculator

Based on Stage 4.20. This update changes **only** the IDE's calculator layout and its central control sizing rules.

## Changed production files
- `mainwindow.cpp`: `SidboxProgrammerCalculator` constructor — 22px keypad keys, equal-width button columns, tighter layout spacing, shorter COPY BIN button.
- `ideglobaltheme.h`: scoped CSS overrides for *only* controls inside `#sidboxProgrammerCalculator`. Generic buttons previously used 22px minimum height PLUS 5px top and bottom padding; this defeated the keypad's fixed heights. Compact readouts and combo boxes also receive reduced padding/min-height.

## Installation
Replace those two files in the IDE source root and rebuild. No new CMake resources or dependencies. The full IDE archive is also provided.

## Expected result
- Seven full rows of five calculator keys visible, including the bottom `~ DEL CLR = COPY` row.
- Keys uniformly sized across five columns and around 22px high.
- Shorter HEX/UDEC/SDEC/REAL readouts and expression field, giving the project tree more space.
- Binary bit buttons continue to be shown in high-to-low order for 8/16/32/64-bit widths.
- All button text, keyboard focus, arithmetic, bitwise toggles, colours and square corners retained.

## Testing
23 Stage 4.00–4.21 source regression tests passed. Qt6 development files are unavailable in this environment; Fedora compilation and visual confirmation are still required.

Suggested visual check: open the calculator in 8-, 32-, and 64-bit modes, switch IDE themes, resize the sidebar, and confirm every keypad key remains visible and has a proper border. Click the `COPY` and bottom-left `~` keys to confirm they work.

No SIDBOX firmware changes or changes to game, map or project formats.
