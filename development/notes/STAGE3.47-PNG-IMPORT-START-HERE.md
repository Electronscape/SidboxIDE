# GamerGirl Stage 3.47 — Palette-aware PNG Import

Built on the Stage 3.46 Tile Atlases release. No change to firmware, game helper ABI, tilemap formats or existing saved game designs.

## New UI

Right-click **Game Resources** (or Sprites / Tile Atlases / Backgrounds) > **Convert PNG → PPB...**.

The dialog supports:

- Destination: **Tile Atlases** (no canvas sprite), **Sprites**, or **Backgrounds**.
- Foreground/background bank: locked to foreground for Tile Atlases; locked to the relevant plane for Backgrounds. In a single-plane game everything uses foreground; in a two-plane game Backgrounds use background. Sprites may choose either plane in two-plane mode.
- Palette index range: configurable **1 to 255** (0 is always reserved for transparent pixels).
- **Generate colours in selected range**: start from the active CLUT or a blank CLUT, quantise only the selected range and preserve its other entries; save the palette explicitly as .pal.
- **Match existing palette colours**: map pixels into the selected indices without modifying any palette file. Requires an active project CLUT for the selected bank.
- Dithering: **None**, **Floyd–Steinberg**, **Ordered 4×4**, **Noise**.
- Side-by-side original/converted preview, transparent checker pattern, index-colour strip and status.
- Alpha < 128 maps to **index 0**; source PNG remains unchanged. Other pixels are treated as opaque. This is an indexed, 8-bit PPB, so partial alpha is not retained.
- The preview is downsampled (max 340×240) to remain interactive. The conversion saved to disk uses **the full-resolution input** on a worker thread and the existing PPB writer.
- Both 1024-byte single-bank and 2048-byte two-bank .pal files are supported for output. When updating one bank of a 2048-byte .pal, the other bank's 256 entries remain unchanged.
- Palette resources are automatically linked/selected in Game Resources when a new palette file is saved, so a subsequent PNG import can build on that same shared CLUT.
- `F8 > Game Engines > Advanced Platformer > 40` describes the whole workflow.

## Example: incremental palette building

1. Convert `hero.png`. Select Sprites, Generate colours, range **1–15**, None, then save `hero.ppb` and `gamepalettes/png_import_foreground.pal`.
2. Convert `tiles.png`. Select Tile Atlases, Generate colours, range **16–23**, None, keep the existing CLUT, save `tiles.ppb`, **choose the SAME .pal file** for the updated shared foreground CLUT and approve its explicit update prompt.
3. The first 15 colour slots remain unchanged; only slots 16–23 are assigned/quantised from `tiles.png`.
4. Select `tiles.ppb` in Tilemap Editor, save your `.sbgm`, and regenerate game assets as usual.

**Important:** The palette holds absolute colour indices. Reusing an occupied slot on a later import *can recolour an existing PPB that uses it*. Choose non-overlapping ranges or make backups. Neither Undo nor Ctrl+Z undoes file overwrites. For an existing palette, import asks before writing anything to that palette file.

The PNG->PPB conversion supports **PNG only** by design; no GIF, BMP or JPEG importer is added.

## Changed source files relative to Stage 3.46

- `pngpaletteimport.h` — new palette converter options and dialog declaration.
- `pngpaletteimport.cpp` — conversion (exact short palettes/weighted median cut), mapping/dithering, preview, dialog.
- `gamedesigner.cpp` — integrate the import, asset destination, worker, dual-bank .pal handling, palette resource selection.
- `gamedesigner.h` — accept resource-tree context for PNG import.
- `CMakeLists.txt` — add the new source files to Qt IDE build.
- `idelibs/docs/cheatsheet.json` — Guide 40.

## Testing and limitations

Source structural checks and cheatsheet JSON validation passed. The complete native Qt6 IDE was **not compiled or UI-tested** in this environment because Qt 6.5+ development files are missing (`Qt6Config.cmake` not found). Please compile with the normal Fedora Qt6 setup and test visually before relying on this for important existing artwork.

Individual PPB/.pal writes are atomic through existing QSaveFile writers, but a *pair* of writes (PPB and palette) is not one cross-file transaction. If the palette write fails after the PPB succeeded, the program reports this explicitly. Keep backups before overwriting any valuable files.
