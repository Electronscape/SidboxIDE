# Stage 5.100 (25 Oct 2026): SIDBOX BOB alpha blend

## Purpose
Expose the existing firmware BOB flag `BLIT_FLAG_ALPHABLEND` (0x02) for each placed sprite and Game Object, without introducing software blending or extra per-frame work.

## In the editor
Select a placed sprite (or any Game Object) and choose **Configure Game Object**. Under **Visual & Movements / Sprite effect**, tick **4x4 alpha blend (SIDBOX BOB effect)**. Save the world and use **Update Game Project** to regenerate. Existing sprites remain unblended by default.

This is an ON/OFF hardware patterned blend. It is **not** an opacity percentage. The Game Designer continues showing source artwork, as the actual 4x4 blend mask was not available in the supplied archives. Hardware is the authoritative preview.

## Data and generator
- `.sbgm`: each sprite saves `objectAlphaBlend` (bool); absent/old defaults false.
- `gamedesigner_export.cpp`: maps that field onto the per-sprite gameasset record.
- `gamecodegen.cpp`: emits `BLIT_FLAG_ALPHABLEND` for the selected BOB during asset initialisation (once per world load).
- `gameassets.rulec`: clears/reapplies only the blend bit, preserving other BOB flags.
- Existing object/animation/flip/stamp draw paths copy or preserve the BOB flags. State-frame rendering inherits the same flag.
- No change to the firmware, game logic, physics, Tilemap, or `main.c`.

## Testing
- `python3 development/tests/test_stage5100_bob_alpha_blend.py`: native GCC checks for flag enabled/disabled, flip and copy preservation, plus static wiring checks.
- Stage 5.97 Trigger dialogue, Stage 3.99 World Canvas, and Stage 4.44 world-object regression scripts passed.
- Qt6 compilation and SIDBOX hardware rendering **not available** here. Exact visual pattern and combinations with flashing must be checked on SIDBOX.

## Install
Copy the updated source paths into the existing IDE tree, preserving the `idelibs/codehelpers/game` directory. Rebuild the IDE. Tick the desired sprite(s), save the world, run **Update Game Project**, rebuild the game and test on hardware.

## Changed files
- `gamedesigner.h`
- `gamedesigner.cpp`
- `gamedesigner_project.cpp`
- `gamedesigner_export.cpp`
- `gamecodegen.h`
- `gamecodegen.cpp`
- `idelibs/codehelpers/game/gameassets.rulec`
- `splashscreenwidget.cpp`
- `development/tests/test_stage5100_bob_alpha_blend.py`
