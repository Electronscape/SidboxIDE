# CoderGirl Stage 5.99: Dialogue Glyph Scaling and Z-order

## What changed

In Adventure Editor -> Dialogue Position, the Dialogue box placement panel now has **Font scale X** and **Font scale Y** settings, and the Thought bubble placement panel has its own independent **Font scale X/Y** settings. Each axis can use 1x, 2x, 4x or 8x (native SIDBOX glyphs are 8x8 pixels).

The new **Frontmost box** selector chooses **Thought bubble above dialogue** (the previous behaviour) or **Main dialogue above thought bubble**. When frames overlap in the live preview, mouse dragging selects the uppermost frame.

The right-hand 480x320 preview uses the existing CoderGirl font glyphs via `GuiDesignerDetail::drawCoderGirlText`, with the same native-font reduction and nearest-neighbour scaling as the Title Screen editor. It also uses the selected text and outline foreground colours, and recalculates wrapping and box heights at the chosen scales.

The shared Adventure runtime uses `gfx_drawtextf` for scaled text, updates wrapping/height calculations for **both** dialogue and thoughts, and draws the frames in the configured order. The default 1x2 scale deliberately uses the existing `gfx_drawtext` path to preserve older games' text appearance. Unrelated inventory menus remain unchanged.

Each world's settings are stored in its own `.sbgm` Adventure data, exported with `gameadventuregen.cpp`, and installed after the world starts via `gameadventure.rulec`; there are no game-specific names or changes to user-owned `main.c`.

## New saved Adventure fields

- `dialogFontScaleX`: default 1
- `dialogFontScaleY`: default 2
- `thoughtFontScaleX`: default 1
- `thoughtFontScaleY`: default 2
- `thoughtAboveDialog`: default 1

## Installation

Copy the files in the ZIP into your IDE source root, preserving paths. Rebuild the Qt6 IDE. Open Adventure Editor -> Dialogue Position, configure both text scales and the frontmost box, then save the world. Run **Update Game Project** and rebuild the game before testing the new runtime appearance on SIDBOX.

## Testing

Passed native GCC tests: Stage 5.99 scaled typography/z-order/world reset; Stage 5.98 simultaneous thoughts; Stage 5.97 message sequences; Stage 5.96 single/full dialogue; Stage 5.94 reward and trigger outcomes. Stage 5.99 and Stage 5.98 editor/source pipeline checks passed. **Qt6 compilation and visual hardware testing have not been performed in this environment.**

No changes to `main.c`, world files, game assets, or the Title Screen editor.
