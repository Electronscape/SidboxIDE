# SIDBOX GamerGirl — Stage 4.03: GUI tidy-up

Based on the uploaded IDE archive: `IDE - 19-10-2026-1843.tar.gz`.

## Changed production files

- `gameanimationeditor.cpp`: Player Animation Editor's sprite atlas now has middle-button grab panning and wheel-driven 1×–16× zoom. The existing Zoom spin box stays synchronized. Mouse-wheel zoom adjusts scrollbars to keep the sheet point under the mouse at the same screen position (except where scrollbar limits naturally clamp it). The mouse cursor is a closed hand during panning; ordinary left selection and double-click insertion remain unchanged.
- `gamedesigner.cpp`: World Canvas (.sbgm) wheel zoom selects the next/previous step in the existing 25%, 50%, 75%, 100%, 200%, 400% zoom list. It preserves the canvas point under the mouse when possible; middle-drag panning is untouched. The current .sbgm view zoom/centre save mechanism remains in use.
- `gamedesigner.cpp`: Game Object Properties heading includes a 40×40 nearest-neighbour drawing of the **existing** game-object tree icon, name, and 16×16 theme-text coloured previous/next arrow icons. Arrows follow only the configured objects from the **Game Objects** tree (not decoration-only sprites); end arrows are disabled. When clicking an arrow the existing OK commit path runs first and the next dialog opens on the next event-loop pass. Cancel does not commit. The page's modal validation stays in force.
- `gamedesigner.cpp`: Live Preview controls are 16×16 theme-text coloured Play, Pause and Stop icons. Pause holds the current frame. Stop pauses and rewinds to the first frame. Editing other preview controls does not accidentally resume after Pause/Stop; Play explicitly resumes. The existing 50Hz tick interval, loop and ping-pong modes are intact.

Everything remains sharp/square, including navigation and animation controls. Icon glyphs are painted from the active IDE theme, so no extra PNG/SVG assets or icon paths are needed.

## Install

Either extract the **complete source archive** over your IDE source tree, or copy the **two changed production .cpp files** from the changed-files archive over their exact same-named files in the IDE source root. Rebuild your IDE using your normal Qt6 build process.

No update to SIDBOX firmware, game runtime helpers, generated game C, `.sbgm`, `.sbanim`, or `.map` files is required.

## Checks

Run from IDE source root:

`python3 development/tests/test_stage403_gui_tidy.py`

Also run the existing Stage 3.93, 3.94, 3.99, 4.00, 4.01 and 4.02 Python source checks.

The source-level checks pass. A real Qt6 IDE compilation, interactive mouse testing and hardware testing could not be performed in the build environment supplied for this patch; please rebuild and test in Qt Creator before distributing.

## Manual test suggestions

1. Player Animation Editor: position an atlas cell in the centre of the view, zoom up and down by wheel, check that cell stays underneath the pointer. Middle-drag in both directions and watch the closed-hand pointer. Double-click a cell to verify frame insertion still works.
2. World Canvas: hover over an object, wheel up/down through the zoom presets, check the object stays near the mouse. Test middle-button pan afterward. Save/reopen the `.sbgm` and check view zoom/position is preserved.
3. Game Object Properties: modify a spring's setting, click Next to a second configured object, then Previous. Check the spring's setting was saved into the in-memory project (save .sbgm to disk as usual). At list ends, the impossible direction is disabled. Cancel should not save current uncommitted edits.
4. Preview: Play, Pause, modify Ticks (should remain paused), Play, Stop (should display the first frame). Repeat under light and dark themes.
