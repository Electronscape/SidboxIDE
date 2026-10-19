# GamerGirl Stage 3.80 — Loop Track Momentum Add + 16×16 Icon

Built from Stage **3.79b** (which includes the **3.79a tab-close segfault fix**, and F5 full backed-up **Update Project** integration).

## Install

Back up your IDE and either unpack the full Stage 3.80 archive into a new folder or replace the following files from the changed-files archive, keeping their **relative paths**:

| File | Purpose |
|---|---|
| `gametilemap.cpp` | Loop slider/readout, 16×16 icons, undo/change detection, level C export and validation |
| `gametilemap.h` | Loop design-time momentum setting |
| `gametilemapmodel.cpp` | Save/load loop momentum in `.sbgm`; old maps use zero |
| `idelibs/codehelpers/game/tilemap.c` | Runtime downhill acceleration, directional symmetry, existing 32 px/frame cap |
| `idelibs/codehelpers/game/tilemap.h` | Extra per-loop field in generated game-level data |
| `idelibs/codehelpers/game/tilemap.txt` | Updated helper instructions |

The archive also includes C/Python regression tests. Rebuild the **IDE** in Qt Creator.

## Test in GamerGirl

1. Open your V1 game design and Tilemap Editor → **Loop Tracks** tab.
2. Select any loop: it now has a **16×16 circular icon** in the list (also on the tab).
3. Move **Momentum Add** slider. The label shows `+0.00` to `+2.00 px/frame²`, in 0.01 increments.
   - **0.00**: **old loop physics**, unchanged; gravity slows climbing, downhill gravity assists, normal loop drag applies.
   - **Above 0**: **arcade boost mode**. Uphill retains existing speed (unless player steers or external forces act). On the **descending half, starting at the top**, gravity and the configured additional speed are applied. Works entering from either left or right.
   - Physics retains the **32 px/frame** speed cap; sufficiently slow players can still leave the track.
4. Try `+0.20` to `+0.40 px/frame²` first. Save, close, reopen and check the slider value persisted. Undo/redo should also track the edit.
5. Press F5 → **Update and Compile** → **Back Up and Update**. This is important: the full update copies **new `gametilemap.c/.h`** and regenerates **`gamelevels/level1.c`** so both runtime and generated data agree. Verify the automatic ZIP backup exists before building your hardware test.
6. Test a lap in **both directions**, and ensure the player exits faster with the boost than without. Previously saved maps and zero-boost loops should behave just as before.

## How the acceleration works

The runtime already tracks a circular `loop_phase`: starting at 0 at the bottom, around through ±32768 at the top, then back to ±65536 at the bottom.

- With boost **zero** the original gravity/steer/drag calculation is followed.
- With boost **nonzero**, **uphill** has no gravity slowdown or friction; **downhill** adds `downhill_boost100 / 100` px/frame of tangent speed **every game-physics tick** (in addition to gravity), with matching sign for the direction of travel.
- Existing `game_tile_player_run()` and `game_tile_loop_t` interfaces are preserved except for a new **last** `downhill_boost100` member in the loop struct.
- `.map` file layout is **unchanged**; the additional value lives in `.sbgm` and generated C. You **must** regenerate and update the helper header together or you can get a mismatched loop-structure layout.
- There is no need to edit `main.c`, spring code, slope code, or animation code.

## Verified here

**Passed native C regression tests:** `test_stage372_loop_entry.c`, `test_stage368_player_hitbox.c`, and `test_stage380_loop_momentum.c` (both directions, old mode, uphill hold, downhill boost, speed cap, complete entry-to-exit traversal).

**Passed source checks:** Stage 3.69–3.71 refactors, Stage 3.75 PNG layout, Stage 3.76 Tile Atlas, Stage 3.77 protected colours, Stage 3.77a pixel picker, Stage 3.78 background replacement, Stage 3.79b full Update Project prompt, and `test_stage380_loop_momentum_export.py`.

**Not tested here:** Qt6 IDE compilation (Qt6 SDK unavailable) or SIDBOX hardware. Please report any compile errors and hardware issues exactly as shown, before altering game physics further.
