# CoderGirl Stage 5.41.1: Inventory HUD balances and Qt compilation hotfix

**Build:** `5.41.1.231026` (23 October 2026), based on Stage 5.41.

## Four Qt compiler errors fixed

`gameadventureeditor.cpp` mistakenly used `QVariant::toInt(8)` at four icon-atlas cell-size reads. Qt defines `QVariant::toInt(bool *ok = nullptr)`; `8` is not a valid `bool*` and the compiler correctly rejects it. Each location now explicitly uses `toInt()` for an existing value and **8** for an unset value. These are the four errors shown in the Stage 5.41 IDE build at lines 521, 1042, 1065 and 1196. `QJsonValue::toInt(8)` elsewhere is correct because its API really does accept an integer default.

## HUD shows the current amount owned for inventory-linked collectibles

- **Show in HUD + Show in Inventory:** after the player first collects the type, the HUD displays the current Adventure inventory amount for its `pickupKind`. USE, DROP, DESTROY, NPC TAKE/GIVE/hand-ins, and calls to `game_adventure_add/remove()` all immediately affect that balance. If two Adventure item definitions have the same `pickupKind`, their current amounts are summed. `Pickup Value` remains independent and does not multiply the quantity.
- **Show in HUD without Show in Inventory:** remains a lifetime collection counter, since there is no inventory amount to spend.
- The project-wide HUD keeps using `gameworlds_hud_total(kind)`. That function now queries `game_adventure_pickup_quantity(kind, &amount)` when the item is tracked in inventory, with a fallback to the original HUD counter if the current world has no matching Adventure definition. Persistent item definitions from Stage 5.41 continue to support travel between worlds.
- All tracking is reset on `gameworlds_shutdown()`, not at world transitions.

## Updating an existing game

1. Install the Stage 5.41.1 changed IDE sources over Stage 5.41 and rebuild CoderGirl.
2. Open **Update Game Project**. Accept upgraded generated `gameworlds.c/.h` and `gameadventureruntime.c/.h` helpers (backing up edited copies first) and rebuild your game `.app`.
3. Test a collectible with both **Show in Inventory** and **Show in HUD** enabled: collect, consume/drop/give, and revisit the world. The HUD should show the **current** inventory amount, not the lifetime collection tally.
4. No authored `main.c`, levels, resources or designs are replaced by this source update.

## Verification

- GCC `-std=c11 -Wall -Wextra -Werror` compiled/runs both the real Adventure runtime pickup-kind query and a two-world HUD test with simulated inventory spend/restore.
- Regression coverage checks all four Qt `QVariant::toInt(8)` misuses, HUD-only totals, pickup value independence, NPC exchanges, HUD designer source wiring and world/player integration.
- A complete Qt6 IDE build could not be run in this environment because Qt6 development headers/libraries are unavailable. Real SIDBOX acceptance remains to be tested.
