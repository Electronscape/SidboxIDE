# CoderGirl Stage 5.40: HUD editor interaction polish (23 October 2026)

Build: `5.40.231026`. Based on Stage 5.39. This is **an IDE-only upgrade**; no changes to the C game rules or user-owned `main.c`.

## Fixes

- **Grab and drag existing HUD icons and text.** A saved mouse grab-offset keeps the object under the cursor at the point you originally grabbed. Clicking an item no longer snaps it to the mouse position or to the top-left.
- **Hide text and items (paint tiles underneath)** checkbox above the canvas temporarily hides labels and collectable icons *in the HUD editor*. Their saved data and generated SIDBOX HUD remain unchanged. While hidden, overlay hit-testing and item drops are disabled, letting you paint or erase underlying tiles normally. Untick to restore normal editing.
- **Right-click-and-drag eraser.** Right-button strokes erase tilemap cells continuously, interpolating over grid cells that might otherwise get missed when the mouse moves quickly. While overlays are visible, a right-click on an item/text still removes that overlay.
- **Separate text palette source** dropdown above the foreground/outline index fields. Choose a project `.pal` or `.act` foreground CLUT, independently of the PPB tile atlas. The old atlas-colour preview remains an option for existing HUDs. Choosing a source changes the **preview**; runtime text is still drawn using numeric foreground palette indices already active in the game.
- **256-colour palette index pickers** for foreground and outline, each with index and colour-code tooltips and square swatch buttons. Saves selected colour indices (0–255) as before. Palette source path is saved under optional `textPalette` in `gamehud.sbhud` version 1. Old projects load normally.
- **One-shot label placement.** Typing in the Label field automatically arms placing a label. Click the canvas once, and the label is placed, input text is cleared, and the placing mode turns off. Existing labels can still be dragged, renamed by double-click and deleted by right-click.

## Installation

Install changed files over Stage 5.39, rebuild CoderGirl, and open **HUD Editor...**. Your existing `gamehud.sbhud` loads without conversion. Save the HUD when happy. If you only changed palette-source preview or interaction settings, no game recompilation is necessary; if you changed actual labels, indices, positions or artwork, use **Update Game Project** and rebuild as usual.

**No authored game files, level files, PPBs, `main.c`, template main game, or runtime helpers are changed.**

## Palette reminder

Runtime text uses the **foreground CLUT already loaded by the game**. The selected `.pal` helps you pick exact indices visually. Using a different palette file than your actual game foreground CLUT will give misleading previews, but will not modify any graphics or palette. The selected source must exist and contain 256 colours when saving.

## Verification

Pass: `development/tests/test_stage540_hud_interactions.py` (source-level contracts plus offset and brush-stroke algorithm checks).

Pass: Stage 5.39 and Stage 5.38 HUD source/strict-host-C tests; Stage 5.37 collectible tests; Stage 5.34 NPC exchange and FIRE1 hand-off tests.

Patch is applied independently against the Stage 5.39 source and contents compared before release. **Qt6 GUI compilation and real SIDBOX testing still need acceptance on the user's Fedora/SIDBOX.**
