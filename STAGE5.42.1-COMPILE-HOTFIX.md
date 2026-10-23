# SIDBOX / CoderGirl IDE Stage 5.42.1 (23 October 2026)

Fix for the three Qt IDE compiler errors reported in `gamedesigner.cpp` lines
7155, 7158 and 7159 (`draftSpriteStamp` not captured).

## Changes
- `gamedesigner.cpp`: `updatePreview` now explicitly captures `&draftSpriteStamp`.
- `gamedesigner.cpp`: Sprite Stamp help now correctly says the runtime renders
  from the existing PPB with cell references; no additional PPB is created.
- `gamehudeditor.cpp`: replaces deprecated `QImage::mirrored(bool,bool)`
  with `QImage::flipped(Qt::Orientations)` preserving X and Y flag behaviour.
- `splashscreenwidget.cpp`: build label updated to `5.42.1.231026`.
- `development/tests/test_stage542_stamps_and_inventory.py`: adds a regression
  assertion for the missing preview-lambda capture.

## Install
Place the drop-in archive contents in your IDE **source root** (where
`CMakeLists.txt` and `gamedesigner.cpp` live), overwriting those files.
Then recompile the IDE. No regenerated game project files are needed for this
**compile hotfix** beyond the ordinary game-project refresh after Stage 5.42.

## Validation
- Stage 5.42 source-PPB stamp drawing + inventory atlas tests: **PASS**.
- Stage 5.41 C++ source-literal lint + feature contracts: **PASS**.
- Stage 5.41.1 HUD palette contract tests: **PASS**.
- Full Qt6 IDE compilation: **NOT available** in this environment (Qt6 SDK missing).
- Real SIDBOX hardware: **not run**.

Older tests that assert obsolete exact splash-screen versions are not relevant
to this hotfix.
