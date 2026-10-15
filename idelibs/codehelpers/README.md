# CoderGirl V1 helper templates

Add more helpers by placing matching `.c` and `.h` files in `game/` or `gui/`.
The Game Resources → Add Helper Code menu discovers these pairs when opened.
Both files are copied into each game's `gamehelpers/` directory.

**No IDE rebuild is needed to add a new helper template.** Open the Game
Resources context menu again and the IDE will list all matching `.c`/`.h`
pairs. For example, to add a `bounce` helper, place these two files in
`idelibs/codehelpers/game/`:

- `bounce.c` (use `#include "bounce.h"`)
- `bounce.h`

It appears under **Game → Bounce...** and is copied into a project's
`gamehelpers/` folder as `gamebounce.c` and `gamebounce.h` (with its local
`#include "bounce.h"` updated automatically).

For a friendlier name, tooltip and message after copying, optionally add
`bounce.ini` in the same directory:

```ini
[Helper]
name=Sprite Bounce
description=Move a sprite up and down over time.
after_install=Open gamehelpers/gamebounce.c for the usage example.
```

`name`, `description` and `after_install` are optional. The `.ini` file stays in the IDE's
library and is not copied to the game project. New helpers are picked up on the
next context-menu opening, not only when the IDE first launches.

For backwards compatibility with the first built-in tween helper, game helpers
are installed with `game` prefixed to their names:
- `game/tween.c` and `tween.h` become `gamehelpers/gametween.c` and `.h`
- `game/spline.c` and `spline.h` become `gamehelpers/gamespline.c` and `.h`
- `game/animation.c` and `animation.h` become `gamehelpers/gameanimation.c` and `.h`

The template C source should `#include` its installed header (e.g. `gamespline.h`).
Helper code belongs to the game and is **not overwritten by gameassets generation**.
Replacing an existing helper requires confirmation.

The `.sbgm` stores editable spline points. Export Spline Paths from the canvas
creates the project-specific `gamehelpers/splinepaths.c/.h` alongside the helper.
After this first export, saving the design refreshes the generated splinepaths
files so changes to dragged points reach the game. Those two path data files
are generated: edit paths in the canvas, not in splinepaths.c.

Sprite Animation works with an already-initialised `gfxbob_t`. It changes
only the atlas `index`, so the same sprite can move using tween or spline.
See the commented beginner example at the bottom of `gameanimation.c` after
installing the helper into a game project. Playback is VBlank/frame-counted:
loop, play once, and ping-pong are supported. No firmware changes are needed.

Platformer Starter is a beginner-friendly V1 game helper. Install it from
**Game Resources → Add Helper Code → Game → Platformer Starter**. It becomes
`gamehelpers/gameplatformer.c` and `gamehelpers/gameplatformer.h`. It supports
left/right walking, jump on UP or FIRE, gravity, solid rectangular collisions,
one-way jump-through ledges and player respawn. The rectangle collision areas
are specified in your game's C code; they are not drawn automatically or
editable on the Game Designer canvas yet. To get started, read the commented
beginner example at the bottom of `gameplatformer.c`. This template works
with an existing TOP-LEFT, 100%-scale `gfxbob_t` from `gameassets_init()`.
It can combine with Sprite Animation, but don't run Tween/Spline on the same
sprite simultaneously since both systems would set its position.

## Advanced Tilemap + Platformer — Stage 1.1 foreground ring

Two maps remain separate: 1 graphics ID byte + 1 collision type byte per tile.
For horizontal scrolling, the **foreground** now uses two mirrored halves of
480x320 in a 960x320 buffer. The background is a separate static 480x320
backdrop. The world can be 1600 pixels or larger, without allocating a
1600-wide graphics buffer. Only newly revealed pixel columns are painted.

The Stage 1 helper stored in an existing game's `gamehelpers/gametilemap.c/.h`
**must be replaced manually**; exporting never overwrites user-edited helper
files. See `TILEMAP-START-HERE.md` for setup, code, sprite restoring and
hardware checkpoints. Horizontal only; actual SIDBOX hardware testing pending.
