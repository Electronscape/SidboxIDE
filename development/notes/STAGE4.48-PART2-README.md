# GamerGirl Stage 4.48 — Part 2: Main Game Rules

Baseline: Stage 4.48 Part 1 (reported compiling and running on SIDBOX).

Changed files:
- gamedesigner_export.cpp
- idelibs/codehelpers/game/maingame.rulec

No changes to the generated game's public APIs, helper sources, firmware,
or project main.c ownership logic.

The `maingame.rulec` file now owns:
- All conditional include directives (from Part 1).
- Standard VIEW_W / VIEW_H / foreground buffers and conditional player/world-player globals.
- The main() function entry and SIDBOX system/audio/display startup.
- Game asset, map, atlas, adventure and world-object initialization.
- Framebuffer validation, background-plane initialization and initial scrolling.
- Camera-follow and level-bound clamping.
- Frame display/swap, music_update and cleanup/shutdown.

The Qt generator supplies boolean @IDE_IF choices and expands the requested
section of the same .rulec using strict rendering; no .inc files are added.

Still hardcoded in Qt (subsequent migration):
- Explanatory resource-specific comments and custom zone/spline examples.
- Player physics binding and frame update, animation selection.
- Per-resource decoration placements, render ordering, foreground layers.
- Generated player hazard and collectable callbacks.

Verification: Checked all rule directive brackets, field presence, and 640
conditional/section combinations statically. IDE compilation and actual SIDBOX
gameplay were NOT possible here: Qt6 development package (>=6.5) unavailable.

Suggested hardware checks:
1. Build the IDE from the whole archive, or replace the two changed files.
2. Keep a backup of the existing, working main.c and game project.
3. Update Game Project and inspect maingame.c.txt for unexpanded @IDE markers.
4. Rebuild and run: springs, pickups, objects, music, camera, map and cleanup.
5. Try a simple no-map/no-player project to verify optional sections.

The current ownership protection remains: user-modified main.c must never be overwritten.
