# Stage 3.87 — Loop Coasting: Leave Cliffs Under Gravity

## Baseline
Stage 3.86 (Loop Coasting), based on the user-provided IDE 19-10-2026-1025 archive.

## Bug
A player who completed a loop with **Ignore friction after exit** enabled
keeps fast horizontal momentum. While the player was marked grounded, the
tilemap solver also moved the player down up to two pixels **for every
horizontal pixel** to follow descending terrain. At 21 px/frame this could
snap the player ~8 px down in one frame, rather than launching off the lip
and beginning to fall under gravity.

## Fix
In `idelibs/codehelpers/game/tilemap.c`, horizontal ground-following now
checks the transient `loop_coast_active` flag:

- On ordinary ground, during walking, or after a steering input, the old
  slope-following physics is unchanged.
- During friction-free loop coasting, the player may still follow *upward*
  terrain, but if the supporting floor drops away or disappears, she
  becomes airborne and stops snapping down to surfaces for the rest of
  that horizontal sweep.
- The normal gravity and vertical collision pass computes the fall. The
  horizontal impulse continues, still friction-free until wall collision or
  left/right input.
- No extra jump impulse is invented for a **flat** cliff. A powered ramp
  launch (upward trajectory derived from slope angle) would be a separate
  optional enhancement and has **not** been added here.
- Zero gravity behaves normally: if gravity is zero, the airborne player
  travels horizontally without falling.
- No player/map struct changes, map format changes, Designer UI changes,
  or physics changes for unticked loops.

## Modified production file
- `idelibs/codehelpers/game/tilemap.c`

## New native regression test
- `development/tests/test_stage387_loop_coast_cliff.c`

Test cases: right-moving downhill transition, left-moving mirrored downhill,
flat cliff with subsequent gravity, unchanged normal downhill follow,
continued friction-free horizontal speed, continued ascent support.

## Installing on Fedora
1. Copy the replacement template to `idelibs/codehelpers/game/tilemap.c`
   inside your installed IDE source tree.
2. Open your existing GamerGirl project in the IDE.
3. Press **F5 > Update and Compile** and accept the full Update Project
   backup/overwrite prompt. That copies the updated template into your
   project's `gamehelpers/gametilemap.c` and recompiles the game.
4. Transfer/reload the rebuilt game on the SIDBOX.
5. Test a completed loop coast down a hill/cliff, steer to restore drag,
   and hit a wall to ensure coasting stops as before.

**No IDE rebuild is necessary solely for this C helper-template change**.
The existing Qt GUI uses this code as a template copied during Update Project.

## Verification
- `test_stage387_loop_coast_cliff.c`: PASS.
- Existing Stage 3.86 loop-coasting test: PASS.
- Stage 3.80 loop-momentum test: PASS.
- Stage 3.72 loop-entry test: PASS.
- Stage 3.68 hitbox test: PASS.
- Stage 3.61/3.63/3.65/3.66/3.67 slope tests: PASS.
- No Qt6 build or real SIDBOX test in this environment.
