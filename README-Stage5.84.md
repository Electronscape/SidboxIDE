# SIDBOX CoderGirl Stage 5.84 | Pickup Stat and Player Inventory integration
24 October 2026 | splash Build: 5.84.241026

## Problem addressed
- "Show in Inventory" created an Adventure inventory item but did not offer to include it in `players/player.sbpi` → Player → Inventory.
- The cross-world auto-registration code required **Persistent collectible** to be ticked, incorrectly tying *the world's object respawn policy* to *the backpack's quantity persistence*.
- A default **Health** pickup type did not automatically increase the player's actual persistent Health stat, so non-inventory Health pickups only ran a user callback (the supplied `main.c` callback currently increases **Score**, not Health).

## Game Object Properties
- An **Apply pickup value to** choice appears in the Collectable section: None, Player Health, Player Lives, Player Score, plus custom stats from `players/player.sbpi`.
- A Health pickup (type 2) defaults to **Player Health**. Existing saved properties missing this new value are handled when regenerating, so revisiting and resaving every Health object is unnecessary.
- This effect applies only with **Show in Inventory OFF**. It adds **Pickup Value** to the selected persistent player stat. With Show in Inventory ON, the collectible instead updates the backpack, and direct-stat changes are disabled.
- **Persistent collectible** continues to control only whether an already collected placed object stays gone on return to its world. It has no bearing on the quantity of items already in the backpack.
- When saving a collectible with Show in Inventory ON, the editor creates its Adventure Inventory item if absent, then **offers to add the same named item** (starting at zero) to `players/player.sbpi` → Player Inventory, without overwriting existing entries. The action can be declined/cancelled; the `.sbpi` is written atomically on acceptance.

## Runtime and compatibility
- Inventory pickup types from saved `.sbgm` files automatically appear in other generated worlds, **whether or not the collectible object itself is persistent**. Global quantities still move between worlds by stable item name.
- Stat-only pickups bypass the backpack slot-limit check; inventory pickups remain limited, and legacy untracked breakable rewards keep Stage 5.83 protection.
- The world manager clamps increasing health/lives/score to `UINT32_MAX`, and named custom stats to `INT32_MAX`.
- Existing legacy `on_pickup()` callbacks remain. Automatically managed pickups suppress old `game_adventure_collect(kind)` calls from that callback to prevent a stat-only pickup also silently entering the backpack. **Custom callbacks can still independently add Score or apply other rules.** Your current `main.c` adds Score for every pickup; this remains unchanged, so a Health pickup also earns its existing callback Score. Selecting automatic *Score* while that callback also adds Score can double-count: edit your own callback if needed.
- The user-owned `main.c`, `.sbgm`, `.sbpi`, project graphics, and save data were NOT modified.

## Install
1. Close the IDE. Extract `IDE/` into your IDE source root, keeping relative paths; rebuild the IDE.
2. Extract `Platform3Test/` into the Platform3Test game project root, keeping relative paths.
3. Launch the rebuilt IDE. Save the Game Object Properties for any modified pickups; accept or decline the Player Inventory registration prompt.
4. **Update Game Project** and regenerate the *complete multiworld project*, so Forest and World1 both receive the new shared Inventory definitions. Rebuild the V1 game.
5. Test a Health pickup with Show in Inventory OFF and Persistent collectible OFF: health should increase by Pickup Value even when the backpack is full. Then test an inventory pickup on World1 → Forest → World1 without the Persistent collectible checkbox; its backpack quantity should survive. Test revisiting an ordinary nonpersistent pickup to verify its object-respawn behaviour remains as authored.

## Files changed
IDE:
- `gamedesigner.cpp`, `gamedesigner.h`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`
- `idelibs/codehelpers/game/collectables.c`, `.h`
- `idelibs/codehelpers/game/gameworlditems.rulec`, `gameworlds.rulec`
- `splashscreenwidget.cpp`

Game:
- `gamehelpers/gamecollectables.c`, `.h`, `gameworlds.c`
- `worlds/world1/gamehelpers/gameworlditems.c`
- `worlds/forest/gamehelpers/gameworlditems.c`

## Tests performed
- Native GCC compiled extracted *actual* game-world pickup bridge: Health, Lives, Score saturation, custom-stat saturation, inventory-vs-stat routing (PASS).
- Native GCC Stage 5.83 full-backpack breakable reward regression (PASS).
- Native GCC Stage 5.84 stat pickup/full-backpack and reward-protection regression (PASS).
- ZIP structural/CRC verification (PASS).
- Qt6 compilation and real hardware tests: NOT performed in this environment (Qt6 SDK unavailable).
