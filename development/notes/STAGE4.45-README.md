# Stage 4.45 — World Items rule templates (first phase)

Starting point: IDE-Stage4.44-WorldObjects-Rules.tar.gz. This includes the Qt deprecated-match enum replacement.

## Files

- `idelibs/codehelpers/game/gameworlditems.ruleh` — header layout, count placeholders, optional includes and declarations.
- `idelibs/codehelpers/game/gameworlditems.rulec` — C file layout, includes, audio positioning slot and runtime slot.
- `idelibs/codehelpers/game/gameworlditems.audio.inc` — fixed audio positioning C routines, inserted only when needed.
- `gamedesigner_export.cpp` — obtains validated project-specific values and renders strict `@IDE{...}` fields.
- `gamedesigner.cpp` and `gamedesigner_update.cpp` — exclude World Items rule templates from the list of ordinary, installable SDK helpers.
- `gamehelpertemplates.h` — Qt AnchorAtOffsetMatchOption warning fix.

## Current limit — IMPORTANT

This is a first-phase rule conversion: conditional includes, header layout, public signatures,
audio positioning functions, and the C file wrapper are controlled by templates.
**The body of object initialization/update/draw and sound wrapper generation still lives
in gamedesigner_export.cpp** and is inserted using `@IDE{GENERATED_RUNTIME}`.
A complete migration of every C function out of the Qt generator is not yet done.

No .map format or public APIs intentionally changed. The optional zero-objects stub remains
unchanged and does not require rule files.

## Test

1. Back up IDE and game project.
2. Rebuild Qt IDE (Qt >= 6.5 required; unavailable in this environment).
3. Generate world items in a project using pickups, springs and sounds.
4. Confirm gamehelpers/gameworlditems.h and .c have no unresolved @IDE markers.
5. Compare output with your last working build, then compile/run SIDBOX.
6. Confirm Update Game Project does not offer or install `gamegameworlditems.c/.h`.

Here, static substitution checks passed for several combinations of pickups, worlds,
triggers, splines, tilemap and audio. Qt build and SIDBOX tests were not run.
