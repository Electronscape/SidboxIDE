# GamerGirl Stage 3.76 — Tilemap Editor Tile Atlas resource selector

Baseline: Stage 3.75 (PNG importer layout and Stage 3.72 loop physics).

## Problem

The tilemap editor's Tile Atlas dropdown could list a Sprite resource, such as `mover1`, if the map's saved atlas path referenced that Sprite. If a Sprite and Tile Atlas resource shared the same PPB path, the Sprite could also occupy the one displayed entry and hide the actual Tile Atlas name.

## What changed

- **Game Designer -> Tilemap Editor -> Tile Atlas** now gathers entries ONLY from Game Resources -> **Tile Atlases** (PPB files).
- Every Tile Atlas resource is shown by its *friendly resource name*, including multiple resources that point at one PPB.
- If the current tilemap still references an older PPB outside the Tile Atlases bank, the editor keeps loading and displaying it, with the explicit dropdown label `Current map PPB (not in Tile Atlases): filename.ppb`. Nothing changes until you choose a Tile Atlas resource.
- Selecting the proper Tile Atlas updates the map's `atlasPath` without modifying tile IDs, graphics layers, collision stamps, slopes, springs or physics.
- Tooltips explain that the dropdown uses the Tile Atlases bank.

## What to do if an imported PPB is under Sprites

The PNG importer offers `Import into: Sprites (on game canvas)` and `Import into: Tile Atlases (resource only)`. If you imported it as a Sprite, in the Game Designer tree right-click that Sprite resource and choose **Move to Tile Atlases (stop drawing)**. Alternatively reimport the PNG and choose `Tile Atlases (resource only)`.

Then open the Tilemap Editor, select the correct atlas name from the Tile Atlas dropdown, and **Save** the tilemap/design. Ensure the new atlas keeps the same tile dimensions and tile order if the old map has existing graphic IDs.

## Installation

Replace both project-root source files `gamedesigner.cpp` and `gametilemap.cpp` from the changed-files archive; then rebuild the Qt6 IDE. Or use the complete Stage 3.76 source archive. No game project helper update or map regeneration is necessary for the selector fix itself.

## Verification

- Stage 3.76 tile atlas resource-selector static regression check: passed.
- Stage 3.69–3.71 refactor structural regressions: passed.
- Stage 3.75 PNG conversion/layout safety check: passed.
- Runtime game tilemap helper: unchanged SHA256.
- Qt6 IDE compilation and interactive selection test: **not available in this environment; test in Qt Creator**.
