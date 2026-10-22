# Stage 5.18: Editable Player Movement Physics (22 Oct 2026)

## Source changes

- `gamedesigner.cpp`: **Create / Edit Player > Movement & Physics** now has a profile bank, Add, Remove with confirmation, editable name, behaviour, walk speed, jump speed, gravity, maximum fall speed and drag, plus a starting-profile selector and stable numeric ID display.
- `gameplayerprofile.h`: stores the bank in the project-shared `players/player.sbpi` (not in each world). Existing `.sbpi` version-1 profiles without a bank automatically start with seven original physics behaviours and values. The generated player code validates profile IDs and numbers.
- `idelibs/codehelpers/game/gameplayer.rulec/.ruleh`: emits a single shared const profile table plus `gameplayer_apply_physics(game_tile_player_t*, uint8_t profile_id)`. This calls the ORIGINAL `game_tile_player_set_physics` and overrides walk/jump/gravity/max-fall/momentum drag only; ICE/Jetpack, collisions, springs, slopes and loop logic remain inside the original game tilemap engine.
- `idelibs/codehelpers/game/maingame.rulec`: the **new generated starter main** calls `gameplayer_apply_physics` to select the starting profile.
- `splashscreenwidget.cpp`: `Build: 5.18.221026`.

## VERY IMPORTANT: your existing Platformer3Testing/main.c

Your custom `main.c` belongs to YOU. CoderGirl will not overwrite it. It currently uses a hardcoded physics switch, so **editing the values will not take effect at startup** until you replace that switch in YOUR game's `main.c`.

In `main.c`, inside `main()` just after `game_tile_player_start()` and hitbox setup, replace the ENTIRE old block:

```c
switch (gameplayer_defaults.physics_preset) {
    case 1: game_tile_player_set_physics_ice(&player_physics); break;
    case 2: game_tile_player_set_physics_water(&player_physics); break;
    case 3: game_tile_player_set_physics_space(&player_physics); break;
    case 4: game_tile_player_set_physics_floating(&player_physics); break;
    default: break;
}
```

with:

```c
if (!gameplayer_apply_physics(&player_physics, gameplayer_defaults.physics_preset)) {
    result = 4;
    goto cleanup;
}
```

The new helper is declared by the generated `gamehelpers/gameplayer.h`, which the demo already includes.

## What this does / does not do

- **Yes:** project-wide editable physics profile definitions, persistent in `players/player.sbpi`, inherited by all worlds using the same shared player.
- **Yes:** source-generated profile table shared across worlds, and C code may switch profiles at runtime by their stable ID: `gameplayer_apply_physics(&player_physics, 7);` (for an example custom profile with ID 7).
- **No automatic per-world selection yet:** the **starting** profile is selected once at game startup. A world transition or zone can call `gameplayer_apply_physics` explicitly to choose a different profile. This does not silently change existing world-transition code.
- **No rewrite** of tilemap engine or `tilemap.c/.h`: physics behaviours are still the same.
- Removing a profile does not renumber surviving IDs. You must update any hand-written code referring to a removed ID.
- The default profiles are Normal (0), Ice (1), Water (2), Slow (3), Space (4), Floating (5), Jetpack (6). Old `.sbpi` `physicsPreset` strings migrate to the corresponding stable ID when opened/saved in Edit Player.
- New profiles use the first available ID >= 7, up to 64 total bank entries.

## Testing

1. Install the six changed IDE source/template files and rebuild IDE.
2. Edit Player > Movement & Physics: change Normal gravity, add a profile, change its name/values and choose it as Starting. Save.
3. Reopen Edit Player and check changes persisted. Close/reopen IDE and check again.
4. Update Game Project to regenerate `gamehelpers/gameplayer.c/.h`.
5. **Patch your hand-owned `main.c` switch as shown above** (once only). Compile for SIDBOX.
6. Change gravity/walk speed and check hardware behaviour. Try ICE and JETPACK to check movement-mode behaviour is retained.

Source and GCC mock-runtime regressions passed here. Native Qt6 compilation and real SIDBOX testing remain to be done by you.
