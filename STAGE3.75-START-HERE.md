# GamerGirl Stage 3.75 — PNG Importer Window Layout

Baseline: Stage 3.74a (the working Qt macro hotfix and clickable source-colour picker).

## What changed

The PNG import dialog is now arranged to use the entire window instead of squeezing the options into the top-left and the source swatches along the bottom.

- Three compact columns of import, palette, transparency and dithering settings at the top.
- Original and converted PNG previews stay side by side, with their existing pan/zoom behaviour preserved.
- The source PNG colour swatches now live in a vertical inspector to the **right** of the previews.
- A movable splitter between the previews and palette inspector lets you choose the balance between artwork and colour choices.
- Source swatch list grows and scrolls with the available height; no fixed 109-pixel swatch row.
- Ctrl+clicking an original PNG pixel now highlights its matching source colour swatch (if it is in the displayed list).
- Destination CLUT preview and summary remain visible along the bottom.
- All corners remain square.

## Files changed

- `pngpaletteimport.cpp` — editor layout and swatch selection only.
- `development/tests/test_stage375_png_layout.py` — layout and conversion-integrity test.

The header and converter (including exact RGB-to-index-0 mapping and preserving existing palette indices outside the chosen range) are unchanged. The V1 game helpers, game formats, and physics are all unchanged.

## Installation

Replace `pngpaletteimport.cpp` in your CoderGirl IDE source root, rebuild in Qt Creator, and open Game Designer → Import PNG.

Suggested test:

1. Select Foreground CLUT / Generate colours in selected range / indices 224–255.
2. Click PNG 7 or your magenta entry in the right-hand list and check that index 0 shows transparency.
3. Ctrl+click the original preview to pick a different colour and confirm its swatch becomes selected.
4. Drag the splitter left/right and zoom/pan both previews.
5. Save the indexed PPB and CLUT, confirming the result still looks correct on SIDBOX.

## Verification

Passed: Stage 3.75 source-layout/unchanged-conversion check, previous refactor integration checks, Stage 3.67 slope handoff C test, Stage 3.68 hitbox C test, Stage 3.72 loop-entry C test.

Qt6 development headers/libraries are not available in this container, so the actual GUI compilation and layout rendering still require your Qt Creator machine.
