# Stage 3.92a — Hazard property redeclaration compile hotfix

**Based on:** Stage 3.92 Murder Objects / Behind Tiles release.

## Symptoms

Qt Creator reports multiple `redeclaration of ... SidboxGameDesigner::Resource::...` errors in `gamedesigner.h`, beginning at about line 113. This is a Stage 3.92 source packaging mistake, not a problem with your Qt Creator installation.

## Fix

The `SidboxGameDesigner::Resource` struct in `gamedesigner.h` accidentally declared the following members twice: `drawBehindTiles`, `hazardDamage`, `hazardKickX`, `hazardKickY`, `hazardKick`, `hazardHurtAnimation`, `hazardFlash`, `hazardFlashColour`, `hazardFlashCount`, and `hazardFlashFrames`. The three sound IDs `sfxHazardHit`, `sfxHazardBounce`, and `sfxHazardAmbient` were also repeated.

Removed only those duplicated declarations, keeping one copy of each with their Stage 3.92 defaults. No runtime or editor implementation has changed.

## Install

Copy the replacement `gamedesigner.h` into the **root of the IDE source** (next to `gamedesigner.cpp`), overwriting the Stage 3.92 header. Then rebuild in Qt Creator.

You do **not** need to use F5 / Update Project or change any generated game files solely for this header-only hotfix.

## Checks

- `development/tests/test_stage392a_resource_members.py`: all fields in the `Resource` struct unique; 13 relevant members present exactly once.
- Native C host tests: Stage 3.92 hazard contact/flash, Stage 3.91 breakable audio, Stage 3.90 intentional stomp, Stage 3.89 breakables, Stage 3.68 world objects — all pass.
- Source integration tests: Stage 3.92 hazard/save/export, Stage 3.91 audio, Stage 3.89 previews, Stage 3.81 platform animation, Stage 3.85a loading popup, Stage 3.80 loop momentum, Stage 3.79 F5 reminder — all pass.

Qt6 build is unavailable in this execution environment. Final Qt Creator compilation must still be checked on Fedora.
