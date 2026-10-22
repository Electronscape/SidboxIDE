# Stage 5.13: Copy Game Objects Between Worlds

**Baseline:** Stage 5.12.

## Editor workflow

1. Open the original world in CoderGirl's Game Designer.
2. Under **Game Objects**, right-click an object and choose **Copy Game Object** (or select a sprite/object and press Ctrl+C in the resource tree or world canvas).
3. Switch to another world **in the same project**, without closing either tab.
4. Right-click the destination's Game Resources tree and choose **Paste Game Object**, or focus its canvas/tree and press Ctrl+V.
5. Move the pasted item as desired, then **Save Design**. Regenerate/update the game project before hardware testing.

## What paste does

- Copies the complete placed sprite and game-object behaviour/physics settings, including enemy animation and defeat settings.
- Automatically registers referenced sounds/music, a linked spline, and other referenced objects such as breakable reward collectables or trigger targets in the destination world.
- Keeps original PPB and audio files as **shared project files**. World-specific resource entries are added, not redundant physical files. Relative paths are rebased against the destination `.sbgm`.
- Carries an explicit `.sbanim` sidecar or an existing default ID-based `.sbanim` sidecar.
- Assigns new stable resource IDs, remapping sound/trigger/reward references; reuses destination audio entries only when their file AND playback settings match.
- Copies referenced spline geometry to the new world, moving it with the object when paste position must move to stay visible.
- Pastes an out-of-view object into the destination's visible canvas. This matters for the demo's `baguy` enemy at X=1700 and the smaller `forest` map.
- A single Ctrl+Z reverts the pasted object, imported resource entries, and spline; Ctrl+Y redoes them.
- Missing referenced files or links produce an error **before modifying** the destination.

## Constraints

- Only cross-world within one project (the `.sbgm` files in the same project directory). Cross-project transfer is not implemented.
- An imported object will use the **destination world's foreground CLUT**. We do **not** override the destination palette; the original sprite indices remain unchanged. Review appearance if worlds use different palette banks.
- Game Object runtime and world generator are unchanged. Paste/save edits the world design and requires normal regeneration to update runtime C.

## Source changes

- `gamedesigner.h`: application-wide clipboard state, undo tracking for imported splines.
- `gamedesigner.cpp`: context-menu commands, cross-world import/remapping/path resolution, destination-visible placement, object/spline undo.
- `gamedesigner_project.cpp`: reset per-world history on load without clearing the shared clipboard.

## Validation

- Source contract test: `python development/tests/test_stage513_cross_world_object_clipboard.py` **PASS**.
- Existing Stage 5.7, 5.8, 5.9, 5.10, 5.11, world manager and player integration tests **PASS**.
- Existing Stage 3.94 visual style test and Stage 3.98 `worldobjects` runtime test fail on the unchanged Stage 5.12 baseline too (retired CSS literal/removed legacy runtime files); **not new failures**.
- **Not compiled under Qt6** in this environment. IDE UI and SIDBOX hardware remain **untested**.

## Suggested real test

In World 1, copy `baguy` to Forest. The enemy's PPB resource and physics should appear. Because `baguy` references `magicFlower[0]` as a defeat reward in the test backup, that collectable should also be imported with a fresh ID and the reference remapped. Forest should not receive the enemy outside its 800-pixel-wide map. Save the Forest `.sbgm`, regenerate the world, and run on SIDBOX.
