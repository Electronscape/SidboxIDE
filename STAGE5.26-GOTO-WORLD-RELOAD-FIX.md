# Stage 5.26 — Goto World object survives IDE restart

Based on Stage 5.25.

## Issue

Goto World doors worked in the generated SIDBOX game but reappeared as plain
sprite decorations after closing and reopening the IDE, making them disappear
from the list of Game Objects. The per-world `.sbgm` save wrote the `goto_world`
type and its destination/arrival/action fields correctly, but the
`SidboxGameDesigner::loadDesign()` type allowlist did not contain `goto_world`.
The loader silently kept the default `decoration` type.

**World Game Objects belong in each world's `.sbgm` file**, not the top-level
`.proj` manifest. The project manifest only references worlds and contains
project-global banks.

## Permanent fix

- `gamedesigner_project.cpp`: add `goto_world` to the recognised Game Object
  type list in `SidboxGameDesigner::loadDesign()`. Existing destination,
  arrival-start and activation fields are already saved/loaded.
- `splashscreenwidget.cpp`: update to `Build: 5.26.221026`.
- `development/tests/test_stage526_goto_world_persistence.py`: add an explicit
  type round-trip source contract regression to catch this oversight.

## Installing

1. Replace the two IDE source files from the Stage 5.26 changed bundle.
2. Rebuild the CoderGirl IDE and restart it.
3. Reopen the project and the world editor; check each Goto World object's
   destination, arrival and touch/FIRE2 selection.
4. Save the affected worlds and restart again to confirm doors persist.
5. If needed, run Update Game Project after the world editor settings are
   confirmed.

No manual changes to your working game `main.c` or SIDBOX firmware are needed.

## Recovering existing doors

- If you reopened the world in the older IDE but **did not save the world**, the
  correct `gameObject.type` and `gotoWorldName` should still exist in its
  `.sbgm`. The patched IDE can recover them when it reloads the design.
- If you saved the world **after** the old IDE had silently converted the
  Goto World object to `decoration`, that save may have overwritten its original
  `gameObject` properties. Restore a previous `.sbgm` backup or manually
  reconfigure that sprite as Goto World.

Avoid overwriting old world files until you have a backup.

## Verification

Stage 5.26 source contract test passed, and selected existing IDE/project
regressions passed. Qt6 libraries are unavailable in this test environment,
so actual Qt6 rebuilding and GUI restart verification remain for the user.
