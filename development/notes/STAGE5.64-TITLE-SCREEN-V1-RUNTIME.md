# Stage 5.64.231026 — First playable SIDBOX title screen (V1)

This is a FIRST HARDWARE-TEST runtime, not the eventual save-game/options UI.
Existing game-world sources and user-authored `main.c` are not overwritten.

## What the generated game does

- Shows the optional `.sidbox-title-screen.json` design before the first world loads.
- Loads the title's existing PPB images (including shared PPB atlas cells) from TFCard, validating PPB header dimensions and pixel reads.
- Displays title and subtitle, positions, 8×16 SIDBOX text, independent size X/Y, foreground CLUT colours and optional outlines.
- Handles sprite/blit, prepared direct and converted direct PPB backgrounds. Larger direct backgrounds are cropped from their upper-left corner; their original pixel data is never modified.
- Renders the configured CLUT-coloured menu selector: brackets, rectangle, pointer or underline, without moving text coordinates.
- Handles UP/DOWN on button PRESS, FIRE1 activates Start Game / Goto World, and Quit returns to desktop.
- Passes the chosen *world and named Player Start ID* to `gameworlds_request_at()` before the initial world is loaded.
- FIRE2 is reserved for Back on future submenus.
- Load Game and Options deliberately do NOTHING in this release.
- Optionally starts the selected music file for the title; stops it when entering a world.

## Generated files

Update Game Project (or F5 → Update and Compile) generates:

- `gamehelpers/gametitle.c`
- `gamehelpers/gametitle.h`
- `maingame.c.txt` with conditional title startup

The generator runs only if `Enable project title screen` is checked. `gamehelpers/gametitle.c/.h` are generator-owned output; regenerate them rather than hand-editing.

Your **hand-owned main.c is not replaced**. The generated startup is visible in `maingame.c.txt`. For an existing manually authored main.c, the precise changes are:

1. Include `"gamehelpers/gametitle.h"` with the other gameheaders.
2. Immediately AFTER `gfx_mode(...)`, but BEFORE `gameworlds_start()` and before loading the shared player/world resources, add:

```c
const char *title_world = "world1"; /* your chosen fallback world */
const char *title_start = "default";
if (!gametitle_run(&title_world, &title_start)) goto cleanup;
```

3. Replace the **initial** `gameworlds_start("world1")` with:

```c
if (!gameworlds_request_at(title_world, title_start) ||
    !gameworlds_apply_pending()) { result = 1; goto cleanup; }
```

4. Do NOT change world-travel code later in your game loop. Keep the existing `gameworlds_player_start(...)` call after world activation: this reads the selected spawn's X/Y/facing.

The example has the exact placement and your own active-world fallback value. Re-copy from the newly generated `maingame.c.txt` rather than blindly using the illustrative `world1` above.

## TFCard setup

The generated C loads title PPBs and selected music using **project-relative paths**, for example `graphics/background.ppb` and `audio/music1.spc`. Copy the corresponding unchanged files onto the TFCard at those paths, in addition to the existing world files. The runtime does NOT write converted PPBs or bake artwork.

The title runs on the foreground CLUT. A single 256-entry foreground palette is used for ALL title graphics/text, because the hardware does not have a per-sprite palette. Choose a consistent text/title palette in the editor if combining differently coloured PPBs. The editor previews that shared palette, without remapping saved pixel indices.

## Failure and constraints

- If a configured title PPB is missing/corrupt on TFCard or memory allocation fails, the title exits to the desktop rather than running with invalid image pointers. Check TFCard assets when debugging.
- PPB atlas frame uses the hardware BOB's 8-bit index, so selectable cell indices for runtime must be 0–255.
- Up/Down are press-edge navigation (release before pressing again); held-key repeat is for a later stage.
- Save slots, Load Game, Options and FIRE2 back-navigation await their own feature passes.
- The Title Screen enable setting is applied automatically to IDE-owned main.c. For **user-owned main.c**, add/remove the title startup manually when enabling/disabling it.
- The title runtime uses SDK graphics and music APIs. No framebuffer/PPB source is changed.

## Tested

- Runtime C syntax checks against the real supplied `idelibs/api/apis.h` on a host compiler: PASS.
- Simulated runtime menu input (Load/Options no-op, Start returns named Player Start, Quit): PASS.
- Title generation, initial world handoff, older preview-selection-crash, glyph and middle-pan **source regressions**: PASS.
- Full Qt6 compile, ARM link, actual SIDBOX LCD rendering, TFCard read/music and real joystick tests: **NOT AVAILABLE HERE; need your Fedora and SIDBOX acceptance.**
