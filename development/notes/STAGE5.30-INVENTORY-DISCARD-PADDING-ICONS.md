# Stage 5.30: Inventory Discard, Dialogue Padding, and 2×2 Icons

Baseline: Stage 5.29, released 22 Oct 2026.

## Inventory: selection and safe discarding

- FIRE2 away from NPC/FIRE2 door continues to open inventory.
- UP/DOWN highlights an owned item and scrolls the list.
- FIRE (the first fire button) on a highlighted **discardable** item opens a
  yes/no confirmation, initially **NO**. UP/DOWN switches between NO and YES;
  FIRE2 commits the selection. Selecting YES destroys **one** copy.
- In Adventure Editor > Inventory Items, **Can discard?** is OFF by default.
  Existing item definitions therefore remain protected.
- An item referenced by a dialogue choice's **Requires** or **Take** is automatically
  protected, even if the matching NPC is in another saved `.sbgm` world. The
  generator matches normalized item NAMES across saved worlds, not item indexes.
- A starred item (`*`) in the inventory is protected from discarding.
- Because the generator consults *saved* worlds for cross-world puzzle use,
  save edited world designs before Update Game Project. The setting is
  recomputed at generation, so an NPC link added after editing the item still
  protects it as long as its world has been saved.

## Inventory icons: per-item 2×2 stamps

- Open Adventure Editor > Inventory Items, double-click an item's **Icon artwork**.
- Choose **Single atlas cell** (existing format), or **2×2 stamp**.
- In 2×2 mode, pick TL/TR/BL/BR independently using the existing atlas picker.
- The editor previews the composite and the inventory table has taller rows.
- Four cell IDs are saved in the item's `iconCells` array; `icon2x2` selects
  whether they are used. The old single `icon` value stays present.
- Runtime draws all four cells directly from the existing atlas. With 8×8
  atlas cells, the resulting icon is 16×16. Larger tile sizes produce larger
  composites with automatically expanded inventory row spacing.
- There is **no** new PPB or runtime icon allocation.

## Dialogue text padding

- Adventure Editor > Dialogue Position: **Text padding** selector (Off, 8 pixels).
- Affects the NPC dialogue body, speaker, choices, and the player's reply bubble.
- The preview and runtime use corresponding layout calculations. The per-world
  selection is saved as `dialogPadding` in `.sbgm`.
- Per-world `gameadventure_setup()` applies the setting during world loading.

## API compatibility

Existing `game_adventure_item_t` retains its original five fields. The new icon
and discard data are in a **separate, optional** `game_adventure_item_style_t`
array, registered with `game_adventure_item_styles()` by regenerated
`gameadventure.c`. This keeps old hand-written C initializers valid.

## Installing

Apply changed files over the Stage 5.29 IDE source, preserving paths. Rebuild
CoderGirl; open Adventure Editor and save desired changes; run **Update Game
Project**, then rebuild your SIDBOX game. **Do not modify user-owned main.c**.

## Tests

- Host-GCC `-std=c11 -Wall -Wextra -Werror`: explicit 2×2 atlas cells,
  protected items, NO/YES confirmation, one-copy discard, and default-safe
  behaviour all passed.
- Prior Stage 5.25/5.27/5.28 Adventure behaviour and Stage 5.4g inventory
  visibility/scrolling regressions passed.
- Two-world generated story style integration test passed after updating its
  old fixture for the new style/padding API.
- Qt6 IDE compilation and real SIDBOX testing are **not** available in this
  environment and remain to be verified on Fedora/hardware.

Splash build: `5.30.221026`.
