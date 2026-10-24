# Stage 5.63.231026 — Title Screen selector, navigation, and edit history

Based on Stage 5.62 source. This release changes **only the design-time Title Screen Designer** and the IDE splash version. It does **not** generate a title-screen runtime, implement saves, or modify SIDBOX firmware / PPB files.

## Selector configuration

Under **Menu Selection (runtime)**, select one of four styles:

- **[   ] brackets** around the selected menu item.
- **Filled rectangle** behind the item.
- **> pointer** at the left of the item.
- **Underline** under the item.

Choose a **CLUT index** for the selector colour. The editor shows the selector on the currently selected menu row in the 480 × 320 preview. The item's own X/Y coordinates do not move. The filled rectangle is solid in the preview and is drawn behind the menu artwork.

The title JSON gains `menuSelector` and `selectorColour`. Later, the title-screen runtime generator should consume these fields to render the configured highlight. `controls.activate=fire1` and `controls.back=fire2` are now saved as design intent, but neither action is implemented in a runtime by this stage.

## Better editor navigation

- **Snap**: Off, 1px, 2px, 4px, or 8px. Dragged title, subtitle and menu graphics snap as they move, using an 8px grid by default. The setting is saved as `snapGrid` in `.sidbox-title-screen.json` when you click Save.
- **Mouse wheel**: zoom the preview around the pointer. Manual zoom survives a dialog resize.
- **Fit**: zoom to the whole 480 × 320 title screen.
- **100%**: return to native pixel scale.
- **Preview width**: the content/column proportions were revised (2 : 5 : 3, instead of 1 : 2 : 3), giving the preview more room and the right-hand properties panel less.

## Undo / redo

- **Undo** button / Ctrl+Z.
- **Redo** button / Ctrl+Y or Ctrl+Shift+Z.
- Tracks a bounded history (up to 256 snapshots) of title/subtitle text, graphics positions and properties, background, palette, menu entries/actions, selection style and snap setting.
- After undoing, a new edit discards the abandoned redo branch.
- Shortcut handling is queued until the current Qt event completes, avoiding destruction of an active in-place table editor while its key event is running.
- History is **in-session only**, not saved in the JSON.

## Compatibility / existing project data

Old Stage 5.58–5.62 `.sidbox-title-screen.json` files still load. The added selector defaults to brackets, index 15; snap defaults to 8px. The saved schema advances to `version: 5`. Existing PPB paths, per-element CLUT indices, SIDBOX font glyphs and font X/Y scaling remain unchanged.

## Files

- `gametitlescreeneditor.cpp` — Title Screen Designer updates
- `splashscreenwidget.cpp` — `Build: 5.63.231026`
- `development/tests/test_stage563_title_interactions.py` — new source checks
- Four existing title-screen regression scripts updated to match current version/retained implementation

## Verification

Source-level regressions pass for Stage 5.59, 5.60, 5.60.1, 5.61.1 and 5.63. The canonical GUI font table remains untouched. **No Qt6 development headers are available in this environment**, so a full IDE compile and mouse/keyboard behaviour must still be checked on Fedora.

## Suggested Fedora GUI check

1. Open Title Screen Designer and select a menu row. Try all four selectors. Confirm text and PPB positions remain fixed.
2. Select a coloured rectangle, change the CLUT index, save and reopen.
3. Move a menu item on the 8px grid; select 2px, move it again. Save/reopen and check grid selection.
4. Wheel zoom in/out, resize the IDE/dialog, press Fit, then 100%.
5. Edit text, drag an item, change an action. Undo/redo each action, including Ctrl+Z while the menu table is focused.
6. Click the title, subtitle and several menu items repeatedly to ensure the Stage 5.60 crash does not return.
