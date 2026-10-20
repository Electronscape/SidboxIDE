# Stage 4.01 — Tilemap and World Editor control styling

Based on the user-tested Stage 4.00 GamerGirl source.

## What changed

- New shared `gameeditorcontrolstyle.h`: a theme-derived, square-corner
  control stylesheet for the World Designer and Tilemap Editor.
- `gametilemap.cpp`: buttons, checkboxes, radio controls, dropdowns,
  spin/number inputs, slider handles, tabs, scrollbars and group boxes now
  follow the same visual language as Player Animation and Game Object Properties.
  The Stage 4.00 bordered stamp and loop selections remain unchanged.
  Scrollable/elided tabs protect the 250px resizable right pane.
- `gamedesigner.cpp`: applies the same styled controls in the main World
  Designer (including tree selections). Theme colours and popup highlight
  text are computed for both light and dark themes.
- Only IDE appearance is affected. There are no changes to engine helpers,
  .sbgm fields, editor logic, or generated C files.

## Installation

For the smaller changed-files package, copy **all three production files**
into the IDE source root, preserving their original filenames:

- `gameeditorcontrolstyle.h` (NEW)
- `gametilemap.cpp`
- `gamedesigner.cpp`

Then rebuild the Qt6 IDE using Qt Creator. Do **not** use F5 Update Project;
no generated game code changed.

## Recommended Fedora visual checks

1. Set a light theme. Open the Tilemap Editor, confirm buttons, spin boxes,
   dropdowns, sliders, tabs, scrollbars and checkboxes show correct colours.
2. Change the IDE accent and reopen both editors. Verify selected tab/control
   states follow the new accent and all text remains readable.
3. Shrink the Tilemap right pane toward 250px: tab titles may scroll/elide but
   the stamp sidebar must not force the map canvas wider.
4. Click/paint with the Tile Stamp and Collision Stamp bank, and select a Loop
   Track. Their cards and existing interactions must be unchanged.
5. Open the World Editor and Game Object Properties; test selection, buttons,
   dropdowns and a couple of existing property saves.

## Verification

- Stage 4.01 shared stylesheet regression test passes.
- Stage 4.00 selection-card and Stage 3.99 World Canvas tests pass.
- Stage 3.93–3.98 relevant property/theme/save tests pass.
- Qt6 SDK is unavailable in this build environment, so the final compilation
  and visual/interaction checks remain on the user's Fedora setup.
