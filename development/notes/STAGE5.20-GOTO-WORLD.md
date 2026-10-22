# Stage 5.20: Goto World game object, 22 October 2026

Build: **5.20.221026**. Based on Stage 5.19.

## What changed

- `Game Object Properties` lists **Goto World** directly beneath **Stompable Enemy**.
- Select **Destination world** and **Enter using: Touch door / Press FIRE2 while touching**.
- Destination is stored in the world `.sbgm` as `gotoWorldName`; activation setting is `gotoPress`. No global .proj changes.
- The generated world object reuses the existing intangible trigger-sensor contacts; it calls `gameworlds_request("worldname")` when activated. Loading is deferred until the following frame boundary. The destination must be another `.sbgm` in the same project.
- `maingame.c.txt` now contains the actual safe world-change flow. The shared sprite remains loaded; physics is restarted against the newly loaded collision map, new world's starting physics selected, position/facing set to Player Start, animation/reset/background refreshed.
- No fade or transition effect at this stage. Inventory and player-owned static values can persist. Defeated enemies, pickups, and changed world objects will reset on re-entry for now (later persistence stage).

## Files changed

`gamedesigner.h`, `gamedesigner.cpp`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`, `idelibs/codehelpers/game/gameworlditems.rulec`, `idelibs/codehelpers/game/maingame.rulec`, `splashscreenwidget.cpp`, and associated regression tests.

## Test in IDE

1. Rebuild and run the IDE. Open **Forest** and **World 1**.
2. Place a PPB sprite for a door (scale 100%), right-click, Game Object Properties -> **Goto World**.
3. Select **World 1** and **Touch door**. Save Forest.
4. Put a second Goto World object in World 1 targeting **Forest**, set **Press FIRE2 while touching**. Save World 1.
5. Run **Update Game Project** for both worlds. Review the generated world `gameworlditems.c` and refreshed `maingame.c.txt`.
6. Apply the **existing `main.c` change below** before compiling, otherwise the old guard exits when a different world becomes active.
7. Compile, boot SIDBOX, walk through the door, and use FIRE2 to come back. Confirm destination Player Start and selected physics for each world.

## Existing Platformer3Testing/main.c: exact changes

The user owns `main.c`; the IDE **must not overwrite it**. The snippet below matches the names in the user's original Platformer3Testing upload. If the file has changed since then, adapt only the shown section and preserve custom code, including `on_custom_zone()` and the existing player physics and animation code.

**A. Immediately before `while (1)` in `main()`, insert:**

```c
const char *running_world = gameworlds_active();
```

**B. Inside `main()` replace the old block immediately following `gfx_lcdwait()`**, starting with the call to `gameworlds_apply_pending()` and ending with the `strcmp(gameworlds_active(), WORLDLEVEL)` stop guard, with this full block:

```c
if (!gameworlds_apply_pending()) { result = 6; goto cleanup; }
const char *new_world = gameworlds_active();
if (!new_world) { result = 7; goto cleanup; }
if (!running_world || strcmp(running_world, new_world) != 0) {
    running_world = new_world;
    map = (game_tilemap_t *)gameworlds_map();
    gameworlds_spawn_t destination = {0};
    if (!map || !gameworlds_player_start(&destination)) {
        result = 7; goto cleanup;
    }
    active_player_sprite->drawx = destination.x;
    active_player_sprite->drawy = destination.y;
    active_player_sprite->flags = (uint8_t)(
        (active_player_sprite->flags & (uint8_t)~BLIT_FLAG_FLIP_X)
        | (destination.facing ? 0 : BLIT_FLAG_FLIP_X));
    player_anim_facing = destination.facing ? PLAYER_ANIM_DIR_RIGHT : PLAYER_ANIM_DIR_LEFT;
    if (!game_tile_player_start(&player_physics, map, active_player_sprite)) {
        result = 7; goto cleanup;
    }
    if (gameplayer_defaults.custom_hitbox) {
        if (!game_tile_player_set_hitbox(&player_physics,
                (uint16_t)gameplayer_defaults.hitbox_x,
                (uint16_t)gameplayer_defaults.hitbox_y,
                gameplayer_defaults.hitbox_w, gameplayer_defaults.hitbox_h)) {
            result = 7; goto cleanup;
        }
    } else {
        if (!game_tile_player_set_hitbox(&player_physics,
                PLAYER_ANIM_HITBOX_X, PLAYER_ANIM_HITBOX_Y,
                PLAYER_ANIM_HITBOX_W, PLAYER_ANIM_HITBOX_H)) {
            result = 7; goto cleanup;
        }
    }
    if (!gameworlds_bind_player_physics(&player_physics)) {
        result = 7; goto cleanup;
    }
    world_player.width = player_physics.hitbox_w ? player_physics.hitbox_w : active_player_sprite->width;
    world_player.height = player_physics.hitbox_h ? player_physics.hitbox_h : active_player_sprite->height;
    world_player.offset_x = player_physics.hitbox_x;
    world_player.offset_y = player_physics.hitbox_y;
    in_space = 0;
    in_water = 0;
    game_tilemap_animation_reset();
    gameworlds_show_background();
    gfx_scrollb(0, 0);
    gfx_scrollf(0, 0);
}
```

**C. Ensure** the Stage 5.19 initial-world physics bind already exists (`gameworlds_bind_player_physics(&player_physics)` after first `game_tile_player_start()`) in place of the old hard-coded `switch`. Do not call both.

Caveat: This snippet assumes the test game's existing `active_player_sprite`, `player_anim_facing`, `world_player`, `in_space`, `in_water`, and `map` names remain as in the uploaded `main.c` (22 October 08:35). It intentionally preserves all of that game's other behaviour.

## Verification scope

- Stage 5.20 source-level assertions passed.
- Stage 5.19 generated-world-manager host-GCC test passed, as did Stage 5.18 physics profiles, Stage 5.4f integration, Stage 5.13 object clipboard, Stage 5.14 reward integration, and Stage 4.44 object rule tests.
- Qt6 libraries are not installed here, so **neither the Qt IDE build nor real SIDBOX execution was performed**. Those tests are still required.
