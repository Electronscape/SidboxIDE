# Stage 5.47 (23 October 2026): HUD collectable artwork

## Bug
`gamehudeditor.cpp` always cropped `(0,0)` of each collectable sprite PPB for the
"Show in HUD collectables (all worlds)" list, the placed HUD preview, and
exported `gamehelpers/gamehud.c`. It ignored the collectable's selected
Inventory Items atlas and cell, 2×2 stamp, placed sprite frame, or Sprite Stamp.
Several collectables pointing at one PPB therefore displayed identical icons.

## Fix
- Look up every HUD-enabled pickup kind in saved `*.sbgm` worlds.
- Prefer the corresponding Adventure Inventory Items artwork, including its
  `iconAtlasId`/`iconPpbPath`, `icon`, `iconTileSize`, `icon2x2` and `iconCells`.
- If no Inventory Items icon was selected, use the collectable's Game Object
  sprite frame or (if present) its `spriteStamp` 8×8 cell arrangement with
  individual X/Y flips.
- When multiple worlds contain the same pickup kind, prefer a valid explicit
  Inventory Items icon to a generic world sprite frame. One pickup-kind counter
  remains project-wide.
- Sample the existing indexed PPB bytes directly into the HUD icon; no PPB
  file copies, index remapping, palette quantisation, or atlas registration.
- Embed icon lookup metadata with HUD counters in `gamehud.sbhud`. Version 1
  remains backward compatible. Old placed counters are refreshed on opening
  the HUD Editor and when "Update Game Project" regenerates the shared HUD.
- Keep the original foreground CLUT preview and export semantics.

## Installation and test
1. Apply the drop-in to Stage 5.46 IDE sources and rebuild.
2. Save the relevant Adventure Inventory Items selections and Game Object
   `Show in HUD` settings in each source world first.
3. Open the shared HUD Editor and check the collectable list and placed icons.
4. Save the HUD. Run "Update Game Project" and rebuild the game.
5. Test at least two items on the same PPB with different cell indices, and
   a 2×2 icon; also test a Game Object Sprite Stamp with X/Y cell flips.

The installed Qt6 GUI and STM32 runtime must still be tested on real hardware.
The existing native Stage 5.45 (portable inventory) and Stage 5.46 (transitions)
regressions pass. HUD-specific source checks pass. This environment has no Qt6
headers, so the IDE itself could not be compiled here.
