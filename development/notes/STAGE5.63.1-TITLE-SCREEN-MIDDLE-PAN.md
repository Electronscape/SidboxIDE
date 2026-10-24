# Stage 5.63.1.231026: Title Screen Middle-Mouse Pan

Starting point: Stage 5.63.231026.

## Change

Hold the middle mouse button and drag anywhere over the 480x320 Title Screen
preview to pan the view. Release it to stop. The cursor changes to a closed
hand while panning. This scrolls the view, not the artwork, and does not select
any title/menu graphic. The existing wheel zoom, Fit/100%, left-button drag,
undo/redo and snap settings are preserved.

Panning only has a visible effect when the canvas is larger than the viewport,
such as after zooming in. If the entire screen fits, there is nowhere to pan.

## Scope

Changed `gametitlescreeneditor.cpp`, `splashscreenwidget.cpp` and test files.
No .sbgm, generated C, palette, PPB, title JSON schema or runtime changes.
The IDE splash label is Build: 5.63.1.231026.

## Runtime readiness

The title-screen JSON includes text/PPB references, positions, menu actions,
selected-world/Player Start information, four selector styles and input intent.
The next substantial step is a generated, optional title-screen runtime that
loads its PPBs/music, navigates with D-pad + FIRE1/FIRE2, and starts the chosen
world without overwriting a user-owned main.c. Save/load progress must remain
separate until persistence (10 slots, player/inventory/stats/world state) is
implemented. Don't advertise Load Game as functional until then.

## Validation

The source regression runs, but a full Qt6 build and interactive pan check on
Fedora were not available in this environment.
