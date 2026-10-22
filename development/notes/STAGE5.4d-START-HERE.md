# GamerGirl Stage 5.4d — Player Editor Lists & Player Start Label

Based on **Stage 5.4c** (Shared Player Animation Preview). No V2 GUI changes.

## Changed files

- `gamedesigner.cpp` — Initial Stats now offers Add Stat/Remove Selected with editable names and starting values, Inventory offers Add Item/Remove Selected with editable names and quantity spinboxes; Player Start text is a smaller magenta label centred above the draggable player (existing dark outline retained); no change to Hitbox override or Starting Physics Preset.
- `gameplayerprofile.h` — `.sbpi` now supports optional `customStats` entries `{ "name": "Mana", "initial": 70 }`. Existing `inventory` `{ "name": "Key", "initial": 1 }` is unchanged. Validate max 64, unique nonempty names. Older profiles lacking `customStats` still load.
- `idelibs/codehelpers/game/gameplayer.rulec` and `.ruleh` — generate a persistent, game-owned named-stat array and C API. Custom stats initialise once at gameplayer_init, persist across gameworlds transitions, and reset when gameplayer_init is invoked again after full shutdown.
- `idelibs/codehelpers/game/maingame.rulec` — documents custom stat API in the generated main example. No gameplay flow change.
- `stage54d_tests/test_shared_player_stage54d.py` — GCC host test for zero and multiple custom stats/inventory plus editor/source integration checks.

## Install

Replace the files above at the same paths in your backed-up IDE source tree; rebuild the IDE. Then in Create / Edit Player, edit or add custom stats and inventory, save `players/player.sbpi`, and run **Update Game Project** (or the normal F5 regeneration) to regenerate `gamehelpers/gameplayer.c` and `.h`.

**Your user-owned `main.c` must not be replaced.** Existing `.sbpi` inventory rows are preserved, but are presented as rows rather than a `name=quantity` textbox. Hitbox override and starting physics are unchanged. The new Player Start label is designer-only; no additional SIDBOX memory/BOB is needed.

## C game code for custom stats

```c
#include "gamehelpers/gameplayer.h"
int32_t mana;
if (gameplayer_stat_get("Mana", &mana)) {
    gameplayer_stat_set("Mana", mana + 5);
}
```

`gameplayer_stat_get`/`gameplayer_stat_set` return 0 if the named stat is unknown, 1 if found. `gameplayer_custom_stat_count()` and `gameplayer_custom_stat_name(index)` support listing them. Values are signed integers between -1,000,000,000 and +1,000,000,000 on initial setup. The runtime API stores int32 values.

**NPC item requirements:** The Adventure Editor currently owns its own item definitions. Give the Adventure inventory item the **same name** as the shared player's item entry, then choose that item under a dialogue choice's `Requires this item`. This stage does not automatically sync/create Adventure definitions or modify existing NPC choices. The world manager retains named inventory values across worlds.

## Test performed

Host GCC with -std=c11 -Wall -Wextra -Werror successfully compiled and executed generated gameplayer code with zero and multiple custom stats, and verified reads, writes, unknown names and existing inventory counts. Source-level checks cover the new tables, Player Start label and generated rules. **The actual Qt6 IDE build and ARM/SIDBOX run could not be performed here.**
