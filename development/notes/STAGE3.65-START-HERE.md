# GamerGirl Stage 3.65 — slope/bowl contact and one-click animation header

Based on the **user-supplied IDE dated 18-10-2026 15:24**, not an older archive.

## A. Passive surfaces: smoother bowl transitions

File: `idelibs/codehelpers/game/tilemap.c`

The Stage 3.63 contact test looked at a contact segment per tile, then used
that segment's tangent to apply sliding force. On a Bezier bowl, a character
straddling the bottom can have its **centre** on the opposite slope from the
segment which physically supports its full-width collision rectangle.
As a result, slope gravity could push the wrong way at the curve transition,
which can feel like friction or a loss of momentum.

Stage 3.65 checks that the *whole-footprint support height* matches the ground,
but uses the *centre-foot tangent* to direct the sliding force. The centre-foot
coverage gate from Stage 3.63 is retained to avoid cliff-edge suction. No
change to the surface damping settings, serialised map data, firmware, or
other forces/loops/springs.

To install with the changed-files archive: replace the file above, use
**Update Game Project** to refresh the V1 `gamehelpers/gametilemap.c`,
then recompile the game. You do **not** need to regenerate the `.map`.

**Limit:** We did not have the user's actual level/map in this IDE archive, so
this fixes a proven bowl-direction regression but cannot guarantee every
instance of "slopes feel sticky" is solved. If it persists, send the .map
and the player hitbox dimensions / location for an exact reproduction.

## B. Save Animations offers to update its game header

Files: `gameanimationeditor.cpp`, `gameanimationeditor.h`, `gamedesigner.cpp`.

1. Open **Game Designer** and select the Sprite named `player`.
2. Open **Player Animations...** and edit animation frames/timings.
3. Click **Save Animations**. It writes the `.sbanim` definition and asks:
   **Create/Update the V1 game header?**
4. Choose **Yes** to generate `gameanimations/player_anim.h` right in the
   directory of the `.sbgm` project. No separate Export dialog is needed.
5. Choose **No** if you only want to save the `.sbanim` without changing the
   game header. Existing `player_anim.h` is never overwritten without asking.

The file is replaced atomically with `QSaveFile`; other sprites get a separate
`gameanimations/<resource-id>_anim.h`, so they cannot accidentally overwrite
the player's header. The **Export V1 C Header...** button remains available,
and now initially suggests the same default path.

Already enabled `GAMERGIRL_PLAYER_ANIMATIONS` in your own main.c? You don't
need to change anything there, simply rebuild the game after updating the
header. Otherwise enable it once in the generated main.c template as in
Stage 3.64. **Update Game Project** will not overwrite user-owned main.c.

## Tests

- Host C11 compilation with `-Wall -Wextra -Werror` and runtime assertions:
  Stage 3.60, Stage 3.61, Stage 3.63 and Stage 3.65 slope tests.
- Stage 3.65 test confirms a real earlier wrong-direction case in the bowl:
  old solver returns +8, updated solver returns -8 when the feet centre
  crosses the bottom (right half must accelerate left). Also checks mirrored,
  zero damping, sticky damping and wide actor footprints.
- Python/C99 playback and generated main.c integration tests from Stages
  3.62/3.64.
- Static source workflow test for the new save-header UI.
- Qt6 build / GUI integration and real SIDBOX hardware **not tested here**;
  build the IDE in Qt Creator, verify both Yes and No paths and run on hardware.
