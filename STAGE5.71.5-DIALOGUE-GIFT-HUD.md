# SIDBOX / CoderGirl Stage 5.71.5 (24 October 2026)

## Symptom confirmed on hardware

Future Kim's dialogue-close gift was successfully added to inventory, but the Dildos HUD stayed at zero. Picking up one Dildo from the floor then displayed 2, and a second pickup displayed 3. This establishes that the inventory was correct but the HUD source was not linked until the first physical pickup.

## Root cause

`gameworlds_hud_total(kind)` intentionally distinguishes independent HUD-only pickup totals from current Adventure inventory. Previously, `gameworlds_hud_inventory_kinds[kind]` was set during a *managed floor pickup* or explicit `gameworlds_adjust_pickup()`, but NOT during Adventure startup or `game_adventure_add()` (used by dialogue gifts). Until the first floor pickup, the HUD returned the independent lifetime total (zero) instead of the backpack quantity.

## Fix

- `idelibs/codehelpers/game/adventureruntime.rulec` now registers each inventory item's pickup-kind with an optional weak `game_adventure_inventory_kind_changed(uint16_t)` callback when the Adventure world is started and when its quantity increases.
- `idelibs/codehelpers/game/gameworlds.rulec` supplies the strong callback, marking the kind as inventory-linked immediately.
- `gameworlds_hud_total()` remains unchanged, including its direct current-inventory result for linked kinds and its independent HUD-only counter fallback.
- Pickup kind zero remains ignored, as before. No new per-frame callbacks, rendering passes, TFCard operations, or changes to the game loop.

## Hardware test to perform

1. Apply Stage 5.71.5 over Stage 5.71.4 and rebuild CoderGirl IDE.
2. Open the game, run **Update Game Project**, and rebuild your game. Verify generated `gamehelpers/gameworlds.c` and `gamehelpers/gameadventureruntime.c` have changed.
3. Fresh play session: offer Future Kim the feather until the final dialogue closes. When she gives the Dildo, the **Dildos HUD should immediately show 1**.
4. Pick up a Dildo from the floor: the HUD should show 2. Pick up another: it should show 3.
5. Optionally leave world1 and return: current inventory should remain reflected on the HUD.

Do not overwrite your handwritten `main.c`. Your current `world1.sbgm`, dialogue ID 9 and gift item ID 3 are already correctly configured.

## Verification

All 11 targeted host-side tests passed, including the new `test_stage5715_gift_hud.py`, Stage 5.37/5.41 pickup and cross-world tests, and Stage 5.69–5.71.4 Adventure regressions. Full Qt6 GUI compilation and real SIDBOX hardware testing of Stage 5.71.5 are still pending.

Splash label: `Build: 5.71.5.241026`.
