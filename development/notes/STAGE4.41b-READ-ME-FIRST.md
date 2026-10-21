# GamerGirl Stage 4.41b — IDE source/header sync fix

## What went wrong

My Stage 4.41a ZIP included `gamedesigner.cpp` **only**. That `.cpp` references
`Resource::enemyStompSideKick` and `Resource::enemyAttackDirection` added by
Stage 4.41. If your local `gamedesigner.h` still comes from Stage 4.40 or older,
the build fails with "has no member named ..." at multiple lines.

## Install

1. **Back up your IDE source directory.** Stop GamerGirl before replacing files.
2. Unzip this package **into the IDE's source root**, not your platformer game
   directory; preserve the directory structure. Overwrite the matching files.
3. This installs these *matching* Stage 4.41a / 4.41 source files:
   - `gamedesigner.cpp` (includes Stage 4.41a separate reward-speed rows)
   - `gamedesigner.h` (**the missing Resource fields**)
   - `gamedesigner_project.cpp` (saves/loads the new fields)
   - `gamedesigner_export.cpp` (generates the new fields)
   - `idelibs/codehelpers/game/worldobjects.c` and `.h` (matching template for
     future Update Game Project exports)
4. Rebuild the IDE using your usual Fedora Qt6 build procedure. If it still
   reports the *same missing members*, check that the compiler is building the
   IDE source directory you actually updated. For CMake, also consider doing a
   clean rebuild when switching versions.

## What is NOT changed

No changes to your platformer's `main.c`, `gamehelpers/gameworldobjects.c/.h`,
world design `.sbgm`, or generated gameplay files. Your existing reward-drop
and enemy physics running on SIDBOX are **not modified** by this fix.

## Validation

Source-level Python consistency tests passed. **Qt6 is not installed in this
runtime**, so a complete Qt/Fedora compile still needs testing on your machine.
