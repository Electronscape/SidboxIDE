# CoderGirl Stage 5.19: Starting Physics Per World (22 October 2026)

## Source and runtime behaviour

- Edit Player > Movement & Physics now has **World** and **Starting physics for this world** dropdowns. Its profile bank remains global, and each world can use a chosen profile by **stable numeric ID**. "Use default physics" inherits the project default.
- Assignments are saved in `players/player.sbpi` under `worldPhysics`: an object from sanitized `.sbgm` world name to numeric profile ID. The player file format remains version 1.
- F5 / Update Game Project embeds each world's resolved profile ID in the generated `gamehelpers/gameworlds.c` registry alongside spawn coordinates. No world-specific copy of player profiles is generated.
- New `gameworlds_bind_player_physics(game_tile_player_t*)` binds an initialised player after `game_tile_player_start`, applies the first world's selected physics, and automatically reapplies each destination world's physics when the manager successfully enters it. The existing engine's slope, loop, spring and ICE/Jetpack behaviours are unchanged.
- `gameworlds_physics_profile()` returns the selected ID for the active world, for optional custom game logic.
- Deleted profiles retain stable survivor IDs; world assignments referencing a removed profile revert to the default when edited. The generator rejects invalid IDs instead of silently selecting the wrong physics.
- Splash build: **5.19.221026**.

## IMPORTANT: Existing Platformer3Testing/main.c manual one-line replacement

The real `main.c` belongs to the programmer and is never overwritten. To enable automatic world physics on the old game, edit **`Platformer3Testing/main.c`**, inside **`main()`**, immediately after `game_tile_player_start` and hitbox setup.

Replace the Stage 5.18 call:

```c
if (!gameplayer_apply_physics(&player_physics, gameplayer_defaults.physics_preset)) {
    result = 4;
    goto cleanup;
}
```

with:

```c
if (!gameworlds_bind_player_physics(&player_physics)) {
    result = 4;
    goto cleanup;
}
```

This is one function-call replacement, **not** a separate extra call. The generated starter template uses it automatically for new projects. `gameworlds_start()` must have completed, and `game_tile_player_start()` must have initialized `player_physics`, before binding.

## Test plan

1. Replace seven changed source/template files from the Stage 5.18 IDE and rebuild the Qt6 IDE.
2. Open Forest / Edit Player / Movement & Physics. Choose Forest in the World selector; assign **Normal**.
3. Choose World 1 in the World selector; assign **Ice**, or an edited custom profile. Save Player, close/reopen IDE and confirm both selections persist independently.
4. Run **Update Game Project** for the saved worlds to rebuild `gameworlds.c` and `gameplayer.c` from the new templates. `gameworlds.c` stores the selected profile ID per published world. No runtime `.sbpi` file is required on TFCard.
5. Make the one-line change to the existing user-owned `main.c` above (if already using the Stage 5.18 call). Build and run on SIDBOX.
6. Verify Forest starts with Normal. Enter World 1 with the world manager and verify Ice/custom physics. Return to Forest and verify Normal returns. Unassigned worlds use the default physics setting.
7. Delete a custom profile used by one world and confirm the editor resets the assignment to the default rather than reusing a different profile's ID.

## Validation

- GCC-generated world registry runtime test compiled with `-Wall -Wextra -Werror`; initial binding, world switching, switching back and stale-binding cleanup all passed.
- Legacy world-manager/player tests updated for the new generated record field and passed; existing shared-player, Tile Stamp, Adventure, object-copy and tab-icon source regressions passed.
- Qt6 development libraries are unavailable here: Qt6 GUI build and SIDBOX hardware acceptance still require on-device testing.
