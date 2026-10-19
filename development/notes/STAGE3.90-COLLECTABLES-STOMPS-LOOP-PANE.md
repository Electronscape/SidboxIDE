# Stage 3.90 — Collectable Tutorial, Deliberate Stomps, Compact Loop Track UI

Based on **Stage 3.89** with no other production changes.

## 1. Beginner guidance in generated `maingame.c.txt`

When the level contains collectables and player tile physics, Game Designer now writes a section above `static uint32_t score` and `on_pickup()` explaining their purposes: what `item` and `item->value` refer to; why the callback receives `void *user`; how `&score` passes the original variable by address; and that the callback is the user's place for game-specific score/key/health rules. The frame-loop `gameworlditems_check(...)` invocation also gains an in-source tutorial: one call per frame **after movement**, live WORLD coordinates, x100/y100 fixed-point conversion, rectangular hitbox offsets and fallback sizes, callback and user-data parameters.

This updates the **generated example only**. Existing hand-written, user-owned `main.c` is **not** overwritten. Users can copy the revised tutorial and callback into their own `main.c` if desired.

## 2. Breakable Object: only intentional jumps count as stomps

Previously **every falling top landing** incremented a stomp-mode breakable and activated its bounce (including simply walking onto a breakable from nearby ground). That confused a passive landing with a stomp.

Now the `game_world_player_t` adapter retains `break_stomp_armed` across frames. It arms only on the player's **real new jump press plus upward takeoff** during the physics step; it does *not* arm just because the player falls. A successful landing on a stomp-mode breakable counts a hit only while armed. Without a valid stomp, the breakable still behaves as a one-way platform and does not bounce or lose hits.

When bounce is enabled, a successful stomp retains the armed state throughout that bounce, allowing repeated landings on the same object until all requested hits are reached. Without bounce, landing consumes the armed state, so the player needs to jump again. Touch-mode breakables are unchanged and can be hit simply by contacting them and separating again.

**Hand-written projects:** bind `world_player.jump_held` to the *live* player's jump button state. Generated projects already bind this. Without the live binding the helper intentionally cannot infer user-initiated jumping, so no stomp-mode hits occur; touch mode is still available.

## 3. Compact, resizable Tilemap Editor right panel

- Removed the redundant Loop Tracks heading that contained a third-party game name.
- Center **X and Y** fields now share a single row; Radius spinner and its slider likewise share a row.
- Shortened form labels, checkbox wording and the status note.
- Longer instructions moved into contextual tooltips.
- The right tab pane has a 250-pixel floor and an `Ignored` horizontal size policy, so the splitter can be pulled inward instead of honouring an inflated contents-derived preferred width.
- Loop behaviour, existing field names, storage, export and physics have not otherwise changed.

## Files modified

- `gamedesigner_export.cpp` — new tutorial comments, generated world-object guide clarification
- `idelibs/codehelpers/game/worldobjects.c` — per-player intentional stomp arming and bounce gate
- `idelibs/codehelpers/game/worldobjects.h` — persistent stomp intent bit in the player adapter
- `idelibs/codehelpers/game/worldobjects.txt` — hand-coded project setup documentation
- `gametilemap.cpp` — Loop Tracks layout and pane resizing
- `development/tests/test_stage389_breakable_objects.c` — revised to simulate real Jump presses
- `development/tests/test_stage390_breakable_jump_intent.c` — walk/fall/press/bounce/touch regression
- `development/tests/test_stage390_editor_and_collectables.py` — source wiring checks

## Testing

Native C world-object tests and original Stage 3.89 tests pass with strict warnings enabled. The Stage 3.89 UI/export static checks, Stage 3.88 falloff export checks, Stage 3.81 platform animation order and Stage 3.85a splash checks also pass. **The Qt6 IDE GUI could not be compiled or interactively checked in this container.** Test on Fedora, especially dragging the right divider narrower, while keeping all X/Y value boxes legible.

Rebuild the IDE for the generator/Tilemap Editor changes. **F5 → Update and Compile** regenerates `maingame.c.txt` and copies the revised `worldobjects.c/.h` helper to the game project. Existing `main.c` is preserved.
