# GamerGirl Stage 3.99 — World Canvas pan, 400% zoom and Animation States styling

## What changed

- `gamedesigner_project.cpp`: the `.sbgm` now writes `worldViewCenterX` and `worldViewCenterY` in world/scene coordinates. These are **editor viewport** values, independent of the game's cameraX/cameraY values and independent of the Tilemap Editor's `viewPanX/viewPanY`. Older `.sbgm` files still open with their existing default view.
- `gamedesigner.h/.cpp`: the World Canvas restores its centre on first show, after Qt has given the canvas a real viewport and scrollbar geometry. Middle-button panning, mouse-wheel scrolling and scrollbar slider moves mark the `.sbgm` dirty, making the viewport change eligible for normal Save. The 400% zoom setting uses the existing ComboBox and smooth-transformation-off pixel-art rendering.
- `gameanimationeditor.cpp`: **Animation States only** now uses the same 43px bordered selection cards as the Game Object Properties type list, with 16–20px state icons, theme-accent borders and contrast-aware selected text. The frame timeline, existing animation data, and generated runtime code were not modified.

## Installation

Replace these four IDE source files:

1. `gamedesigner.cpp`
2. `gamedesigner.h`
3. `gamedesigner_project.cpp`
4. `gameanimationeditor.cpp`

Rebuild the IDE with Qt Creator on Fedora. No game `F5 → Update and Compile` is required for this IDE-only release.

## Manual test on Fedora

1. Open a large `.sbgm` design. Pan the **WORLD CANVAS** with the middle mouse button to a recognisable cluster of Game Objects. Press **Save Design**. Close and reopen its tab: the canvas should be centred at the same part of the world. Save and close/reopen the IDE and repeat.
2. In the World Canvas zoom dropdown, select **400%**, move the pan again, save, close/reopen the design. Verify that both zoom and pan are restored.
3. Check that the dashed LCD game camera remains unchanged by panning the editor. The Tilemap Editor should still remember its own independently stored pan.
4. Open the Player Animation Editor under both light and dark IDE themes; check that Animation States display bordered 43px rows, correctly coloured selection background/text and unchanged icons/animation actions.
5. Open an older `.sbgm` with no `worldViewCenterX/Y`: it should still open normally at the previous default position.

## Verification scope

Python source-integration and native spline/reward regressions passed in this environment. Qt6 development libraries are not installed here, so Qt Creator GUI compilation, live panning and real screen rendering still need Fedora verification. No SIDBOX runtime/helper files have been changed.
