# CoderGirl IDE: Stage 5.21 + 5.22

**Build: 5.22.221026** (22 October 2026)

**Base:** Stage 5.20 (the user's already-working Goto World build). Stage 5.21 was being finalised when Stage 5.22 was requested, so this delivery contains both changes together.

## Stage 5.21: Remember individual worlds

- When leaving a world, save its dynamic object state before unloading that world's resources.
- Restore the previous object state after entering the world and reconstructing its sprites. Includes collectables, enemies, damage/defeat, breakables, switches, moving world objects, reward drops and Adventure conversation/flag progression as supported by the generated modules.
- No raw world pointers are retained in the saved data. Data lasts while the APP runs; this does **not** create TFCard save games or persist across a full game restart.
- Shared player/inventory/score mechanics remain separate from world history.
- The user's working `main.c` **does not need changing** for this feature.

## Stage 5.22: Multiple Player Starts

The Game Resources tree now contains:

    Player Starts
      Default start
      Door 1 start
      Door 2 start
      ...

- Right-click **Player Starts** or any child and select **Add Player Start...**.
- Double-click a child to edit its name, X, Y and facing; named entrances are also draggable on the map (cyan labels). Default Start uses the existing player editor and remains mandatory.
- Right-click a non-default child to **Remove Player Start...** (confirmation required). Default cannot be removed.
- Extra starts are stored in the destination world's `.sbgm` as `playerStarts[]`, each with a stable ID. Renaming doesn't break an existing door reference.
- **Goto World** Game Object Properties now shows **Arrival location**, populated from the destination world's saved `.sbgm`, alongside Destination world and Enter using. Each door stores `gotoStartId`, defaulting to `default` for backward compatibility.
- Exports validate referenced entrances; a deleted start causes a clear generation error rather than silently teleporting to the wrong place.
- The generated world manager now provides `gameworlds_request_at("forest", "<id>")`, retains `gameworlds_request("forest")` for the default, and returns the chosen spawn via the **existing** `gameworlds_player_start()` call. No manual `main.c` edit required.
- The generated tables store only positions, facing and stable IDs, not duplicate player graphics.

## How to test

1. Replace the Stage 5.20 IDE sources with **all 16** changed files from this package, preserving their relative paths, then rebuild the Qt6 IDE.
2. Open **Forest**, add Door 1 start and Door 2 start under **Player Starts**. Edit/drag them to widely separated positions. **Save Forest first**.
3. Open **World 1**, configure two Goto World doors targeting **Forest**. Set their **Arrival location** selectors to Door 1 start and Door 2 start respectively; save World 1.
4. If a world is already open when you create a new start in the other world, saving that other world is sufficient; reopen the door's **Game Object Properties** to refresh its dropdown. No need to close world tabs.
5. Run **Update Game Project** for all worlds and compile the APP. Test each door arrives at its own position and facing. Test the existing default start and the FIRE2 activation method as well.
6. Defeat one enemy or collect a pickup in Forest, travel to World 1, return to Forest, and check the changed state was preserved. Restart the entire APP to verify world-state storage is only in RAM.
7. Delete a non-default entrance and confirm that an old door pointing to it produces an export error until you select a valid replacement. Try deleting the default: no Remove action should be offered.

## Tested here

- Host GCC C11 runtime test: two named entrances to Forest, a separate entry in World 1, invalid-ID rejection, default fallback, repeated travel: **passed**.
- Host GCC C11 world memory save/restore test over 3 transitions: **passed**.
- Source-generated world object state and Adventure progress syntax checked against the original Forest/World 1 generated C: **passed**.
- GUI and persistence source checks: **passed**.
- Qt6 IDE **not compiled in this environment**; SIDBOX hardware test pending.

**Notes:** User-owned `main.c` is left untouched. All four start/arrival choices are project runtime state, not a disk save-game system. Screens and tree controls stay square-cornered. Splash: `Build: 5.22.221026`.
