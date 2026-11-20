# Sidbox Native Compiler: GUI + Games + Hardware Test Pack

**Target:** your working SBAPI05 compiler and `tfcard:/sidbox/l/clibs.library`.

This package contains **11 standalone C sources** to compile directly on Sidbox.
They were compiled on the development host with the native Sidbox compiler code
and the exact 16,196-byte SBAPI05 `clibs.library` from the 20 November compiler
package. **They have NOT been run on actual STM32 hardware.**

## Install

Copy the `gui`, `games`, `hardware`, and `compile-only` directories to a
convenient place such as `tfcard:/ctests/` on the SD card.

The command syntax is the real native compiler's `main.c` syntax:

    compiler -i tfcard:/ctests/gui/01-control-panel.c -o tfcard:/ctests/gui/01-control-panel.app
    launch tfcard:/ctests/gui/01-control-panel.app

Make the output .app filename correspond to the input .c. Use `compiler -i
... -o ...` for every source. `BUILD-AND-RUN.txt` has all commands ready to
copy. Output directory must exist before compiling.

## Suggested test order

1. `gui/01-control-panel.c` (button, checkbox, slider, progress, callbacks).
2. `gui/02-menu-dialogs.c` (menus + dialog and infobox callbacks).
3. `gui/03-resize-layout.c` (resizing and repositioning gadgets).
4. `gui/04-text-tools.c` (textarea, textbox, insert/read, character buffers).
5. `hardware/01-joystick-ticks.c` (joystick reading, raw 32-bit getTicks).
6. `hardware/02-cpu-benchmark.c` (integer workload measured by getTicks).
7. `games/01-star-fighter.c` (software framebuffer, bullets, falling targets).
8. `games/02-raycaster.c` (3D-style maze, integer raycasts, joystick movement).
9. `games/03-particle-reactor.c` (140 trails and particles, joystick attractor).
10. `games/04-brick-breaker.c` (bricks, collision, joystick paddle).
11. `compile-only/01-raw-graphics-ebi.c` (**compile only**, see safety note).

All playable game programs create normal GUI windows and allocate **persistent
static indexed 8-bit pixel buffers**. They call `bitmapview_create`, pass a
row-major pixel array using `bitmapview_set_bitmap`, and repaint from a GUI
timer. They never take over the real LCD draw buffers. They use
`BVF_SRC_ROWMAJOR | BVF_PERSISTANT` so redraw remains in the window compositor.

### Hardware input bits

The SDK in the supplied IDE API defines:

    FIRE 0x01, FIRE2 0x02, UP 0x04, DOWN 0x08, LEFT 0x10, RIGHT 0x20

For game demos, input is read from the real `API.hwl->getjoyport()` EBI entry.
The hardware monitor also calls `API.hwl->getTicks()`.
`getTicks()` is reported as **raw ticks**, not milliseconds or CPU cycles,
because the API headers supplied do not document a precise time unit.

### Shutdown

Close the application's title-bar window. Game/timer programs cancel and free
their timer in the close-request callback **before** closing the window.
Please start with **one animated test at a time**, especially the 3D raycaster.

### Raw graphics safety

`compile-only/01-raw-graphics-ebi.c` contains a never-invoked function whose
body references the low-level `API.gfx->primatives` and `API.gfx->hgfx` calls.
It is meant to test that the compiler can generate code for these real EBI
paths. **Do not change main() to call the function or launch it as a graphics
application without an exclusive framebuffer/game-mode lease.** The SBAPI05
library does not expose a documented fullscreen lease. Direct drawing while the
GUI owns the LCD can corrupt the desktop or create buffer conflicts.

### Limitations / discoveries

* The on-device compiler currently requires one local variable declaration per
  declaration statement. The samples do not use `int a, b;`.
* The current parser does not support `?:`; the samples use if/else.
* Global byte buffers use the supported `static uint8_t array[LITERAL];` form.
* Some C string usages are deliberately avoided because the compiler's EBI
  accepts string literals or static byte arrays for many string parameters.
* All 11 sources pass **host compilation**, which is not proof of correct GUI
  appearance, FPS, input polarity, or framebuffer behaviour on real Sidbox.
* The game demos use the GUI compositor, so their performance is not a measure
  of maximum raw LCD/game-mode rendering speed.
* The API timer-set function returns `int` in the provided SDK, but its success
  value is not documented in those headers. These tests call it without
  assuming a particular success return convention.

There are no changes to firmware, the compiler itself, or `clibs.library`.
