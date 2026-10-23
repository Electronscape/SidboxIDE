# Stage 5.32: Border-aware padding, Inventory USE, fixed action brackets

Based on Stage 5.31 (22 Oct 2026). This update changes generated code templates and the Adventure Editor, not the game's hand-authored `main.c`.

## Padding / runtime
- Inventory always reserves 8 clear pixels *inside* the selected decorative frame's inner edge. The inset is `actual_border_tile_size + 8` for 8/16/32-pixel skins. A plain box gets 8 px.
- NPC dialogue body, title, answer choices and player reply balloons obey the design-time `Dialogue box padding` selection (Off = 0 or On = 8), also measured **after** any decorative frame border.
- DESTROY confirmation box uses the same skin-relative inner padding.

## Inventory item USE
- Each Adventure Editor -> Items row now has a **USE effect** button.
- Select Health, Lives, Score, or a custom stat name loaded from `players/player.sbpi`, then enter a signed stat change (such as Health +15 or Magic -4) and whether one item is consumed after successful use. An empty stat or amount 0 disables USE for that item.
- The runtime shows **USE** only on rows configured with a nonzero USE effect. Protected quest items can be used even when they cannot be discarded.
- LEFT/RIGHT navigates available actions in order: USE, DROP, DESTROY. DROP and DESTROY are displayed only when the item is marked discardable.
- The stat callback determines whether the action succeeded; unsuccessful use never consumes the item. There are no dynamic allocations.
- Generated world code implements `gameadventure_apply_item_stat(const char *stat, int32_t delta)` as a weak callback. Its default updates `gameworlds_state()->health/lives/score`, or, where available, the shared player's custom stat via `gameplayer_stat_get/set`.
- **Important for custom main.c:** Your own live health, score, lives variables may be distinct from `gameworlds_state()`. In that case the default handler updates the saved/shared world state but **not** those separate locals immediately. You can override `gameadventure_apply_item_stat` in your own source to keep your runtime variables synchronised. We have not changed your main.c.

## Fixed text positioning
- Action labels are always painted at one fixed X-coordinate. Selection draws `[` and `]` immediately outside them, instead of replacing `DROP` with `[DROP]` at the same origin and shifting the D by one character.
- DESTROY YES/NO confirmation uses the same approach.

## Update steps
1. Back up your source and install the Stage 5.32 changed files over Stage 5.31, retaining directory layout.
2. Rebuild the CoderGirl IDE.
3. Open Adventure Editor -> Items, press **Set USE...** for an item, pick a stat, enter amount and whether to consume an item. Save the world.
4. Run **Update Game Project** so `gameadventureruntime.c/h` and each `gameadventure.c` are regenerated. Do **not** overwrite `main.c`.
5. Compile and test on physical SIDBOX.

## Validation performed
- Generated C runtime compiled under host-GCC `-std=c11 -Wall -Wextra -Werror`.
- Functional host-GCC inventory USE: success, failure, one-copy consumption, protected item usage, bracket coordinates.
- Generated story C compiled under strict GCC with and without shared player support (synthetic templates).
- Stage 5.32 frame padding coordinate tests (8/16/32-pixel skin tiles; off/on; inventory, NPC dialogue, reply bubbles).
- Stage 5.31 inventory/drop/world integration tests and Stage 5.30 icon/destroy tests were updated for the new, wider action layout and passed.
- Qt6 full GUI compile and physical SIDBOX test not performed here (Qt6 dev packages unavailable). Real shared-player/live-health integration remains to be checked with the user's customised main.c.
