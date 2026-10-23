# Stage 5.34: NPC GIVE inventory + AND/OR quest logic

**Date:** 22 October 2026. **Base:** Stage 5.33. **Build:** 5.34.221026.

## How to use

1. In the **Adventure Editor**, edit a dialogue node and the **choice** whose answer should offer an item.
2. Under **NPC item exchange**, choose **Configure GIVE inventory / AND-OR requirements...**.
3. Enable **Selecting this answer opens inventory in GIVE mode**, then select up to four distinct requested items.
4. Choose **ALL (AND)** or **ANY (OR)**. For ALL, choose whether to accept items **one at a time**, remembering partial deliveries, or require all items **at once**. Enable/disable **Consume accepted items**.
5. Pick **Wrong item → dialogue** and **Still missing items → dialogue**. Either may remain on the current NPC dialogue. Independently select an optional custom event or Game Object action for each outcome.
6. Back in the main choice settings, **Next**, **Event / resource**, **NPC gives** and **Mark this NPC as helped** govern successful completion. For a GIVE exchange, the new **Consume accepted items** switch governs removal of requested items, so don't configure a redundant **Take** action for the same item.
7. Save Adventure settings, run **Update Game Project**, rebuild your game, and test on SIDBOX.

## Player controls

- FIRE2 near NPC opens the conversation as before.
- Choosing a configured GIVE answer opens the normal inventory artwork in **GIVE** mode, showing *all owned items*, without marking correct/incorrect items.
- UP/DOWN selects an item, FIRE1 offers it, FIRE2 cancels GIVE and returns to dialogue.
- Wrong item: no item is consumed; optional wrong-item event fires and the NPC displays the configured wrong dialogue immediately.
- Correct item with ANY: immediate success, optionally consuming the selected item.
- Correct item with ALL-at-once: the whole group must be present in inventory; if missing another item, **Still missing** response occurs and no item is consumed. If all are present, all are optionally consumed together.
- Correct item with incremental ALL: the NPC optionally consumes one item, remembers it, and gives **Still missing** response until all parts have been delivered. Already delivered parts do not count twice. Final delivery triggers success.
- Success follows the configured choice's existing player reply/Next route, item reward, event, and once-only/NPC-completed flags.

## Persistence and compatibility

- The item exchange configuration lives inside each dialogue choice's `exchange` JSON object in its existing world `.sbgm` file.
- All previous `.sbgm` files remain compatible. Older choices without enabled exchange keep their previous behaviour.
- Four local item IDs per exchange; groups are single-level ALL or ANY rather than arbitrary nested Boolean expressions. This intentionally keeps the designer simple and the C runtime bounded.
- Progress uses one 4-bit mask per node/choice, in a static **768-byte** buffer in the runtime. Each world also preserves its own **768-byte** progress snapshot with the existing world-save hooks. Partial deliveries survive world switches during the same run; they do **not** persist across power cycles.
- Required GIVE items are treated as quest items in inventory protection checks, including cross-world saved requirements.
- No dynamic allocation, no firmware changes, no change to `game_adventure_choice_t` layout, no changes to the user's customized `main.c`.

## Verification

- New strict host-GCC `-Wall -Wextra -Werror` test: wrong gift, OR, atomic AND, incremental AND, saving/restoring partial progress, repeated delivery safety.
- Existing Stage 5.25, 5.27, 5.31, 5.32 and 5.33 runtime regressions passed.
- The previous much older `test_stage54i_world_adventure_style.py` has a baseline-incompatible placeholder assertion that also fails unchanged on Stage 5.33; it is not counted as a new failure.
- **Fedora Qt6 build and physical SIDBOX tests remain pending.** Please back up your current working 5.33 source and `.sbgm` worlds before upgrading.
