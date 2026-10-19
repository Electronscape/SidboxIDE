# GamerGirl Stage 3.81 — Idle/Walk animation while riding moving platforms

Built directly from **Stage 3.80**, including its loop-momentum feature, full Update Project on F5, and tab-close crash fix.

## Cause

Previously generated `maingame.c.txt` chose Jump/Fall **immediately after** `game_tile_player_run()`. That is too early for a moving platform: the platform's `gameworlditems_after()` collision pass runs **later**, setting `player_physics.on_ground = 1` when the character is supported by the lift/conveyor. The old animation code therefore sees a temporary mid-frame airborne state and incorrectly chooses Jump or Fall.

## Fix

Generated frame loop now runs in this order:

1. `gameworlditems_update(1)` (if game has objects)
2. `gameworlditems_before(&world_player)`
3. `game_tile_player_run(&player_physics, player_buttons, 1)`
4. **`gameworlditems_after(&world_player)`**
5. **Choose `player_anim_state`, then call `player_anim_step()`**
6. Draw as before

The selection is `Idle` when standing/riding without LEFT or RIGHT, `Walk` when LEFT/RIGHT is held while grounded, `Jump` when `vy100 < 0` and airborne, and `Fall` when `vy100 >= 0` and airborne. A spring launch from world objects is now visible on the launch frame too. No physics, world objects, loop boost, collision, or animation playback functions were altered.

## Installation

For Stage 3.80 users, replace only `gamedesigner_export.cpp` in the **IDE source root** from the changed-files archive. Rebuild in Qt Creator.

## VERY IMPORTANT — Existing user-owned game `main.c`

**Update Project / F5 does not overwrite your existing customised `main.c`.** It writes the corrected starter example to `maingame.c.txt`, but your compiled game continues to use `main.c` unless you manually copy the corrected order across.

In your game `main.c` find the animation `#if GAMERGIRL_PLAYER_ANIMATIONS` block between the tile physics call and `gameworlditems_after(&world_player);`. Move **only** `gameworlditems_after(&world_player);` directly above the `#if` animation block, like this:

```c
/* world-object positions updated first as before */
gameworlditems_before(&world_player);
const uint8_t player_buttons = getjoyport();
game_tile_player_run(&player_physics, player_buttons, 1);
gameworlditems_after(&world_player);  /* MOVED: resolve lift contact first */

#if GAMERGIRL_PLAYER_ANIMATIONS
/* Existing facing/state-selection/player_anim_step code stays unchanged here. */
#endif
```

This is a placement example, **not a complete replacement `main.c`**; preserve your customised game loop, existing `gameworlditems_update(1)` call, `player_anim_step()` call, camera and drawing code, plus any guards that the project actually uses.

If your game already selects animations **after** `gameworlditems_after()`, there's nothing to edit in `main.c`.

After making the change, compile and test on SIDBOX:
- Ride a moving platform without direction input: **Idle**
- Press LEFT/RIGHT while on it: **Walk**
- Jump off: **Jump**, then **Fall**
- Land again: **Idle**
- Trigger a spring: **Jump** on the launch frame

## Verification

- Native C99 compile/run of generated animation state logic with animations both ON and OFF: passed (idle/walk on lift, spring launch, regular jump/fall, facing).
- Generator output order/source check: passed.
- Previous Stage 3.80 loop acceleration test: passed.
- Stage 3.68 hitbox and moving-object/spring tests: passed.
- Previous source regression checks: passed.
- **Qt6 IDE compilation and SIDBOX hardware behaviour still require your test.**
