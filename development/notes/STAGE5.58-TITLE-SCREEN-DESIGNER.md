# Stage 5.58.231026 — Title Screen Designer (editor-first pass)

This stage adds a new **Title Screen...** button beside **Logic Flow...** in Game Designer.

## What it does
- Opens a maximized, project-wide **Title Screen Designer** dialog.
- Saves project-local title-screen/menu data to `.sidbox-title-screen.json`.
- Lets the designer define:
  - whether the title screen is enabled,
  - game title, subtitle and title music path,
  - menu items in order,
  - menu actions: `Start Game`, `Load Game`, `Options`, `Quit`, and `Goto World`,
  - destination world and destination player-start name for `Goto World`.
- Starts with a sensible default menu if no saved data exists.

## Scope of this first pass
This is an **IDE workflow / project-intent** feature first. It does **not** yet generate or inject a complete SIDBOX menu runtime. The existing game can still launch directly into the first world if no runtime title-screen support is wired in yet.

The point of this stage is to let the project start defining title-screen structure now, so later runtime work can use saved data rather than inventing another format.

## Files changed
- `gamedesigner.cpp`
- `gametitlescreeneditor.cpp`
- `gametitlescreeneditor.h`
- `CMakeLists.txt`
- `splashscreenwidget.cpp`

## Validation notes
Source inspection confirms the button placement and new editor entry point. Full Qt6 compilation and runtime behaviour still need to be verified on the user's Fedora environment.
