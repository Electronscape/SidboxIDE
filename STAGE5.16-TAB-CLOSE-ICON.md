# Stage 5.16: Restore Tab Close X Glyph

Baseline: Stage 5.15 IDE source.

## Changes

- `gameeditoricons.h`: Return native local file paths for Qt stylesheets instead of `file:///` URLs. The embedded `:/icons/` resource remains a fallback if an external icon isn't present.
- `mainwindow.cpp`: Quote the close button icon path in theme-generated stylesheets. The initial tab stylesheet retains the embedded icon. The original sharp-corner tab and red hover behaviour are unchanged.

`icons/close_tab.png` is already included in `CMakeLists.txt` via `qt_add_resources`, so neither a new image nor a resource-list change is needed.

## Installation

Copy `gameeditoricons.h` and `mainwindow.cpp` into the IDE source directory, replacing the existing files. Rebuild and relaunch the IDE.

## Test

1. Open at least two source or world tabs and confirm both X icons are visible.
2. Hover over one; the red hover background and X should remain visible.
3. Change IDE themes and confirm the X is still visible.
4. Relaunch the IDE from a different working directory and repeat the test.
5. Confirm the tab close buttons still close the intended tab.

No SIDBOX game regeneration or firmware update is needed.

Source regressions passed: Stage 4.13, Stage 4.15, Stage 5.10, Stage 5.14, Stage 5.15, and Stage 5.16. Qt6 compilation and live GUI testing are still unverified in this environment.
