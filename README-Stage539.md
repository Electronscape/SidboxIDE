# CoderGirl Stage 5.39: Shared HUD polish (23 October 2026)

Build: `5.39.231026`. Based on Stage 5.38.

## Changes

* Fixed HUD generated counter format: uses `%u` (32-bit unsigned) rather than the escaped `%%lu` that displayed the literal `%lu` on SIDBOX.
* Separate **Text foreground**, **Outline text** and **Outline colour** palette indices; runtime matches Adventure's four-direction, one-pixel text outline. Text colour/outline apply to static labels AND live counters.
* HUD text preview uses fixed **8×16 character spacing** (Qt mono-glyph approximation).
* Atlas selector lists PPBs from all saved world resources, plus other `.ppb` files in the project, including sprite atlases and HUD-only sheets. The picker shows the entire source with scrollbars.
* Mouse wheel zooms both atlas picker and HUD painting canvas (1× to 10×); existing scrollbars allow panning.
* Cell Width/Height changes NO LONGER delete the arranged HUD tiles. **Important:** changing a cell size changes how original atlas indices map to pixels. Composition is retained, but some artwork may look different and require reassignment.
* Interactive **480×320 HUD placement preview**: click or drag the outline to set the shared HUD origin, or edit X/Y spin boxes. Saved as `hudX`/`hudY` in project-level `gamehud.sbhud` (compatible with Stage 5.38 files).
* `game_show_hud(0,0)` uses the saved HUD screen position. Any call with nonzero x or y instead uses that explicit origin. `game_show_hud_at(x,y)` ALWAYS uses the supplied absolute position, including `(0,0)`.
* Updated `maingame.rulec` documentation only. No modifications to authored `main.c`, dialogue, world maps or game assets.

## Install

Install changed files over Stage 5.38, rebuild Qt6 IDE, open HUD Editor, save the shared design, and **Update Game Project** to regenerate `gamehelpers/gamehud.c/.h`. Rebuild the game's `.app`. No new TFCard artwork is required unless you selected a new atlas resource.

Existing `gamehud.sbhud` files remain readable, with default position `(0,0)` and outline disabled.

## Testing

`python3 development/tests/test_stage539_hud_polish.py`: static/editor contracts and strict host-GCC C smoke test (count, outline, default/explicit positions).

`python3 development/tests/test_stage538_hud_designer.py`: older HUD integration and C test, updated current build assertion.

Full Qt6 build and real STM32H743 testing still need Fedora/SIDBOX acceptance.
