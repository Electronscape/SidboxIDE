# GamerGirl Stage 5.4g — Backpack: Show Only Owned Items

Based on **Stage 5.4f (NPC Item Picker and Hidden Backpack Entries)**. V1 game only; no V2 GUI Designer or user-owned `main.c` changes.

## New backpack display rules

- Quantity **0**: omit item entirely from in-game inventory window and its scroll list.
- Quantity **1 or more**: show item with its current quantity, including any item tagged **Secret / quest item** in the shared player editor.
- A secret or quest item is therefore discovered in the backpack as soon as it has been obtained; removing its last unit hides it again.
- The secret/hidden boolean is retained in `player.sbpi` for source compatibility and authoring metadata, but **does not suppress any owned item** in the backpack. Existing `.sbpi` files are supported unchanged.
- NPC Requires/Give/Take, pickups, persistent inventory counts and dialogue logic are unaffected.
- Backpack scrolling is clamped when an item count falls to zero while the inventory is open, avoiding empty rows after using up an item.

## Changed files

- `idelibs/codehelpers/game/adventureruntime.rulec`: quantity-driven displayed rows + scroll offset clamping.
- `idelibs/codehelpers/game/adventureruntime.ruleh`: clarify the compatibility visibility hook and the new quantity rule.
- `idelibs/codehelpers/game/gameplayer.ruleh`: document the secret tag as metadata rather than permanent invisibility.
- `gamedesigner.cpp`: inventory table heading becomes **Secret / quest item**, with accurate descriptions/tooltips; JSON key `hidden` remains intact.
- New tests: `development/tests/test_stage54g_inventory_reveal.py` and `.c`.
- Updated Stage 5.4f inventory display test to follow the new behaviour while leaving its original entry-point filename available.

## Install and test

1. Replace the source files at the paths shown, build the Qt6 IDE.
2. Open **Create / Edit Player** if you want to see the clearer inventory hint and renamed checkbox. **Do not delete/recreate your player profile.**
3. Run **Update Game Project** (or F5 updating all worlds) so the new `adventureruntime.rulec` generates the updated runtime C.
4. Build your APP. Test with a normal item at 0, a secret item at 0, and a secret item at 1. Both zero items should be absent; the owned secret should be shown. Pickup/use the item and verify it appears/disappears without blank scrolling rows.
5. Test a dialogue that Requires or Takes that item: game logic and inventory quantities should behave as before.

Note: The Adventure inventory screen currently lists items defined in that world's Adventure item registry. A player profile name that is **not** in that registry will not automatically be added as a new row by this stage. The project-wide NPC picker helps authors keep those names consistent.

## Verification

Strict host GCC C11 tests passed with -Wall -Wextra -Werror, including an owned secret hidden by the earlier metadata filter, zero-count rows, scroll, changing quantities, and the complete empty display. Stage 5.2 world manager, mixed worlds, Stage 5.3 shared player, and Stage 5.4f integration regressions passed. Source contract checks passed. Full Qt6 IDE compilation and hardware APP test remain for the user.
