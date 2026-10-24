# Stage 5.50.231026 — Design-time Logic Flow

Open a Game Designer tab and click **Logic Flow...**, immediately to the right of HUD Editor.

The window starts maximized and presents a read-only project-wide graph created directly from the **saved** `.sbgm` design files in the game project root. It does not connect to SIDBOX, modify the design, produce new PPBs, or update any generated C code.

## Cards and connections

- Worlds and their default / named Player Starts
- Goto World objects and **destination-world Player Start** connections
- Gameplay objects, target-object enable/disable/toggle relationships, and breakable drops
- Spline paths linked to objects using them
- Collectable objects and their matching inventory-item definitions
- Inventory USE actions linked to player statistics
- NPCs and their starting/completed dialogue nodes
- Dialogue nodes, choices, success/missing branches, item requirements, item gives/takes, exchanges, and object actions
- Red **Missing** cards and diagnostic counts when a referenced world, Player Start, object, spline, dialogue node, or inventory index cannot be resolved from the saved designs

Only gameplay sprite objects become object cards. Ordinary scenery, backgrounds, palettes, sounds and music are not graphed as independent cards in Phase 1. Custom handwritten C callbacks cannot be reconstructed from `.sbgm` and are not shown as explicit connections.

## Controls

- **World:** choose All Worlds or just one world
- **Find:** dim nonmatching cards while preserving their positions and connections
- **Highlight selected links:** dim unrelated cards and edges
- **Card click:** view stable identifiers, properties and incoming/outgoing references in the right-hand panel
- **Drag empty canvas:** pan
- **+**, **-:** zoom; **Fit Graph:** show the whole graph
- **Reload Saved Worlds:** re-read `.sbgm` designs after saving edits

Node badges are simple sharp-corner coloured strips, not bitmap icons. No icons exceed 16×16 because none are required.

## Limitations and safety

- The graph is a **design reference visualizer**, not a live debugger or script/node programming language.
- Graph relations come from saved JSON; save each modified Game Designer world before using Reload.
- The canvas does not move game objects or change references. Edit those in their existing IDE panels.
- Broken-reference warnings are advisory. Custom C-based behaviours and conditional runtime state cannot be inferred.
- The full Qt6 IDE compile and interactive rendering still require verification on a Fedora Qt6 development machine; this environment has no Qt6 development libraries.

Files changed/added: `gamedesigner.cpp`, `gamefloweditor.cpp`, `gamefloweditor.h`, `CMakeLists.txt`, `splashscreenwidget.cpp`.
