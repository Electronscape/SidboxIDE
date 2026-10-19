# GamerGirl Stage 3.72 — Loop Track Entry Height Fix

Baseline: **Stage 3.71a** (compiled and tested by user on real SIDBOX).
Only the V1 game tilemap helper has changed. No Qt6 refactor, IDE UI, map format,
collision slope, animation editor, or generated game code changed.

## Bug

On entering a loop with a rectangular hitbox, the player briefly dropped
below the surface of the loop. The loop tick used a single circular inset:

    inset = min(hitboxWidth, hitboxHeight)/2

for BOTH X and Y placement. A 26x32 collision box consequently had its feet
approximately 3px too low at the bottom. A 16x32 hitbox was 8px too low.
The exit snap, however, used the complete height, so the positions disagreed.

## Correction

In `idelibs/codehelpers/game/tilemap.c`, `cg_loop_tick()` now uses the
physical hitbox width for the horizontal normal offset, and the physical
hitbox height for the vertical normal offset. The offsets are still applied
relative to the actual hitbox origin, preserving visible BOB position.

Both entry and exit now use the same physical bottom-of-feet position.
Square hitbox behaviour is unchanged. The existing +/-5px loop attachment
position tolerance is unchanged too; loops whose bottom is deliberately
misaligned with the physical ground by several pixels can still visibly snap.

## Installing in the IDE

Replace `idelibs/codehelpers/game/tilemap.c` with the one from the delta
archive. There are no IDE CMake changes. For new/update V1 projects, run
**Update Game Project** to copy the latest helper into the project and
rebuild the game.

## Installing in an existing V1 game quickly

The game drop-in archive contains `gamehelpers/gametilemap.c` with the correct
include spelling (`gametilemap.h`). Extract that into your existing game and
rebuild. This does NOT change your game's main.c or level files.

**Do not copy the IDE's tilemap.c directly over gametilemap.c** unless you
also fix its first `#include` to the game's header filename.

## Test results

- New native C test: square 32x32, actual 26x32 custom hitbox with 64x64 BOB,
  16x32 box, taller 32x52 hitbox, and 64x64 fallback. Bottom entry positioning
  and end-of-lap exit positioning verified. The test fails on Stage 3.71a.
- Existing slope/Bezier/cliff-edge and Stage 3.68 hitbox C tests pass.
- Stage 3.69/3.70/3.71 source layout and generated animation/hitbox checks pass.
- Actual SIDBOX loop entry is not verified until hardware testing.

## Recommended hardware test

Walk into the same loop with (a) your existing player hitbox and (b) a very
narrow/tall hitbox. Watch the bottom entry on normal movement and spring entry.
Also run one complete loop and check for a jump at exit. If entry still shifts
by a few pixels, compare the physical **feet Y** with `center_y + radius` in
that level: the entry trigger intentionally tolerates a +/-5px discrepancy.
