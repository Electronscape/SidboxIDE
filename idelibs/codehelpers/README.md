# CoderGirl V1 helper templates

Add more helpers by placing matching `.c` and `.h` files in `game/` or `gui/`.
The Game Resources → Add Helper Code menu discovers these pairs when opened.
Both files are copied into each game's `gamehelpers/` directory.

For backwards compatibility with the first built-in tween helper, game helpers
are installed with `game` prefixed to their names:
- `game/tween.c` and `tween.h` become `gamehelpers/gametween.c` and `.h`
- `game/spline.c` and `spline.h` become `gamehelpers/gamespline.c` and `.h`

The template C source should `#include` its installed header (e.g. `gamespline.h`).
Helper code belongs to the game and is **not overwritten by gameassets generation**.
Replacing an existing helper requires confirmation.

The `.sbgm` stores editable spline points. Export Spline Paths from the canvas
creates the project-specific `gamehelpers/splinepaths.c/.h` alongside the helper.
After this first export, saving the design refreshes the generated splinepaths
files so changes to dragged points reach the game. Those two path data files
are generated: edit paths in the canvas, not in splinepaths.c.
