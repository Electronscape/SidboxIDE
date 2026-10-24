# SIDBOX / CoderGirl Stage 5.80 (24 October 2026)

Fix persistent inventory drops losing PPB icon artwork after a world round trip.

Root cause: `game_adventure_restore_drops()` restored the saved positions/item IDs, but the PPB loader ignored items whose backpack quantity was zero. Dropping the last Feather creates precisely that case.

The shared runtime now loads artwork for ACTIVE saved drops during world restoration, independently of backpack quantity. Backpack preloading remains limited to owned items, duplicate drop instances reuse the same PPB allocation, and the draw loop does no TFCard I/O. No persistence layout or save format change.

**IDE drop-in** (apply with IDE closed):
- `idelibs/codehelpers/game/adventureruntime.rulec`
- `idelibs/codehelpers/game/adventureruntime.ruleh` (documentation only)
- `splashscreenwidget.cpp` (`Build: 5.80.241026`)

**Current Platform3Test game drop-in** (apply with IDE/game closed):
- `gamehelpers/gameadventureruntime.c`
- `gamehelpers/gameadventureruntime.h` (documentation only)

Updating only the IDE does not patch a game binary that was already built. You can copy the game drop-in immediately, or rebuild the IDE then use Update Game Project to regenerate the game helper. Do not overwrite or modify user-owned `main.c`.

### Hardware test
1. Build game, take the last Feather from inventory in Forest and DROP it.
2. Leave Forest for World1, then return to Forest.
3. The Feather should remain on the ground with its 2x2 icon, and be collectible again after you step away and return.
4. Repeat twice and check that no crashes occur while rendering/transitioning.

Host regression (`development/tests/test_stage580_floor_drop_restore.py`) compiles and tests Forest -> World1 -> Forest, renders all four 2x2 cells, checks no TFCard I/O on each draw, and checks repeat restore doesn't reload the same PPB. `test_stage545_portable_icons.py` and `test_stage532_inventory_use.py` also passed.

Qt6 IDE compilation and STM32 hardware execution could not be performed in this environment; the reported intermittent crash has not yet been isolated independently of the missing image. If hardware still crashes after the fix, further tracing will be needed.
