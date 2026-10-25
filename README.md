# CoderGirl IDE — Stage 5.134.251026

**Flow Debugger wire-click crash hotfix (IDE-only).**

The Stage 5.133 Flow Debugger kept references to a temporary wire-pair lookup
created inside `redraw()`. Clicking a connector after drawing was finished
could dereference that expired lookup and crash in `FlowWireItem::mousePressEvent`.

Stage 5.134 captures the assigned edge index by value instead, then reads the
connection's current labels from the live edge list. Connections representing
multiple actions still display every action when clicked.

- Only production source changes: `gamefloweditor.cpp`, `splashscreenwidget.cpp`.
- Does **not** alter the UI layout, card styling, project world files,
  `.sidbox-flow-layout.json`, Adventure runtime, or game files.
- Rebuild the IDE only. No `main.c` changes or Update Game Project needed.
- Stage 5.133 NPC foot-anchor fixes remain included in the full source.

Read `INSTALL-STAGE5.134.txt` for installation and testing.
