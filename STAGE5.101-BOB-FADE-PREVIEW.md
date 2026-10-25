# CoderGirl Stage 5.101 - BOB patterned fade editor preview

## Install
Copy `gamedesigner.cpp` and `splashscreenwidget.cpp` into the Qt IDE source root. Rebuild the IDE.
You do NOT need to regenerate your game for this editor-only change. Existing Stage 5.100.1 game fade exports remain intact.

## New behaviour
- The game designer canvas displays patterned transparency for each placed Sprite / Game Object with a BOB fade greater than 0%.
- Changing the 0-100% fade slider updates the Game Object Properties sprite preview, collision preview, and underlying canvas item immediately, without saving.
- Cancel returns the canvas item to the saved fade percentage. Prev/Next navigation continues to commit each object as before.
- Animation, palette-cycling, mirroring, zoom/scaling and movement refresh the faded canvas pixmaps.
- 100% fade is invisible but the item retains a selectable bounding rectangle (you can still find it in the resource tree).
- Existing 0% sprites follow the original fast preview path; no new per-frame game code.
- All styles remain square-cornered, existing IDE threshold remains 2048 KB.

## Accuracy limitation
The supplied IDE archive includes the BOB API flags and fade percentage, but NOT the firmware Core's per-pixel fade routine. The Qt preview uses a conventional 4x4 Bayer threshold matrix as a **visual approximation**. It is deliberately NOT RGB opacity, but its exact dot locations / percentage thresholds may differ from the firmware. The real SIDBOX renderer and generated BOB fade percentage have NOT been altered. To match the hardware precisely, we need the firmware blitter's actual 4x4 threshold routine.

## Verification
Stage 5.101 static/model checks passed for percent thresholds, 4x4 pattern phase, image masking, editor update call sites, modal preview and Cancel restoration. This environment lacks Qt6 development headers, so this stage is not claimed to have compiled here. Compile on Fedora and check the canvas preview, sliders and hardware side by side.

Build: 5.101.251026
