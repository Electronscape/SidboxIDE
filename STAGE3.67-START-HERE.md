# GamerGirl Stage 3.67 — Slippery-slope stamp handoff

**Based on Stage 3.66.** Diagnosed using the actual game archive uploaded
18 October 2026 (`Archive.tar(20261018-145959).gz`). This is a change to
one production C physics helper only; game animations, atlas, map format,
level geometry, editor UI, springs and loops have not been edited.

## What was actually broken

The game has a **32 × 32 player collision box** and several **16-pixel-wide**
passive downhill point-slope stamps connected end-to-end. Stage 3.66 checked
whether the player's **centre feet** were inside the **same stamp** currently
supporting the rear foot. At a join, the centre is already over the next,
lower stamp, while the rear foot is still supported by the previous stamp.
Gravity/damping were therefore disabled mid-slide; normal damping slowed
all movement to a halt.

The fix requires the player's foot centre to be over *some* eligible passive
stamp when beginning a slide; it gets the downhill force from the stamp
**actually supporting** the full-width collision. Once already sliding,
contact with the end of the supporting stamp can continue the movement until
the rear foot actually leaves it. Flat-ledge support still vetoes the passive
force. The Bezier centre-tangent selection remains for one continuous curve.

## Game installation (fastest, exact paths)

Back up your current game first. From the *game-only* archive, replace:

`gamehelpers/gametilemap.c`

This replacement already includes `#include "gametilemap.h"` so it can be
dropped directly into the user's exported V1 game. Recompile the V1 game,
then copy/run the new `.app` as you normally do.

For future **Update Game Project** operations, also replace in your IDE
source tree (from the *IDE changed files* archive):

`idelibs/codehelpers/game/tilemap.c`

Alternatively, use the complete Stage 3.67 IDE archive, rebuild the IDE,
then Update Game Project to refresh the game helper and recompile.

**No `main.c`, game-level `.map`, `.sbanim`, or `player_anim.h` edits needed.**

## Important existing level settings

The uploaded `gamelevels/level1.c` contains four stamp definitions:

- shape 0: passive OFF
- shape 1: passive OFF
- shape 2: passive ON, 2% damping (16px down ramp)
- shape 3: passive ON, 2% damping (large Bezier curve)

Only stamps using definitions 2 and 3 can slide under their own gravity.
If another stamp should slide, switch it on in the Tilemap Editor and
re-export the level. No re-export is needed for the physics fix itself.

## Validation

- The genuine game level and 32x32 player reproduce Stage 3.66's failure:
  a long 16px-segment downhill ramp slides just 4px then stalls.
- With Stage 3.67, the same game data advances from X=2752 to X=2872
  in 40 frames with **no input**, continuing across multiple stamps.
- Another short single-stamp test (game X=448) now slides to X=482 after
  40 frames, then slows on ordinary flat terrain as expected.
- New synthetic test of adjacent 16px stamps with a 32px player fails on
  Stage 3.66 and passes with Stage 3.67.
- Stage 3.60–3.66 slope / cliff-edge / mirror / Bezier C regression tests
  pass; selected tests pass with UBSan; game's helper passes C syntax test.

Still needs the owner's **actual SIDBOX hardware test**. This is not a
claim that the complete game or Qt IDE has been hardware-tested here.
