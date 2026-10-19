# GamerGirl Stage 3.68 — Animation Hitbox Becomes Real Physics

Based on the verified **Stage 3.67** IDE, including its working slippery-slope joins.

## What changed

When a Sprite named `player` has a configured animation:

1. In **Game Designer → Player Animations**, edit **Hitbox X / Y / W / H**.
2. **Save Animations**, then choose **Yes** to update `gameanimations/player_anim.h`.
3. The header now defines `PLAYER_ANIM_HITBOX_X`, `_Y`, `_W`, `_H`.
4. In newly generated V1 `main.c`, with `GAMERGIRL_PLAYER_ANIMATIONS` set to 1, the starter calls `game_tile_player_set_hitbox(...)` **after** `game_tile_player_start(...)`.
5. Physics uses that box for solid walls, slopes, Bezier curves, hazard/zone contact and loop attachment. Generated world object movement and springs also use the physical box and its offset; pickup interactions use it too. **Drawing still uses the original sprite origin and entire BOB.**

**Fallback:** If animation is absent/disabled, physics still uses `sprite.width × sprite.height` and zero offsets, with no new header required. No effect on other non-player sprites.

The hitbox must fit entirely inside the atlas cell. W/H must each be at least 1px; X+W must be at most cell width, and Y+H at most cell height. Invalid settings are rejected in the editor and by the C API. To align the player's shoes with the ground, usually make `Y+H` equal the cell height (e.g. 64px art with X=16, Y=12, W=32, H=52).

The **Foot X/Y anchor** is still preview-only. The physical rectangle is independently configured with Hitbox X/Y/W/H.

## Installing

- Replace the Stage 3.68 files under their exact relative paths, and rebuild the Qt IDE.
- Open the Player Animations editor, inspect the hitbox, click **Save Animations**, answer **Yes** to updating `player_anim.h`.
- **Update Game Project** to copy the new `gamehelpers/gametilemap.c/.h` and `gamehelpers/gameworldobjects.c/.h` into the game. New generated game code also uses the updated collision box for World Objects and pickups.
- Recompile the V1 game.

**Critical:** if your game has a user-owned `main.c`, Game Designer does not overwrite it. The original uploaded game had a custom `main.c` with space/water behaviour; we have prepared a separate *game drop-in archive* with those edits preserved and the new one-time hitbox setup wired in. Use that game drop-in rather than expecting `Update Game Project` to edit a user-owned `main.c`.

For users wiring their own game, call this after `game_tile_player_start()` and before game frame 1:

```c
if (!game_tile_player_set_hitbox(&player_physics,
        PLAYER_ANIM_HITBOX_X, PLAYER_ANIM_HITBOX_Y,
        PLAYER_ANIM_HITBOX_W, PLAYER_ANIM_HITBOX_H)) {
    /* Abort level initialisation: invalid geometry. */
}
```

Only include these macros when the newly generated `player_anim.h` is present. A disabled animation setup should not call the setter; full BOB bounds remain the default.

## Testing

- Host C99/C11 syntax and game integration checked; Qt6 SDK unavailable for compiling/testing the UI here.
- Regression tests: existing Stage 3.60–3.67 slopes, edge balance, high/low damping, real 16px slope joins; new 32/48/64px BOB with identical physics box, offset rendering, 64px atlas with taller hitbox, spring/lift contacts and guided loop contact.
- SIDBOX real hardware test outstanding.
- No changes to the exported `.map` format, sprite PPB graphics, animation frame timing or existing BOB flipping.
