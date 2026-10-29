SIDBOX / CoderGirl IDE - Stage 5.166.88 (29 October 2026)
LIVE WIRE FOLLOW DURING NODE DRAG

Install
-------
1. Back up your working Stage 5.166.87 IDE source and project.
2. Extract this complete source archive over Stage 5.166.87.
3. Rebuild the IDE and verify splash Build: 5.166.88.291026.
4. Open Visual Nodes in a busy world, drag a conversation, GIVE or logic
   node rapidly; the associated lines should stay attached throughout.
5. Test self-loops, a selected highlighted wire and normal undo/redo.

Changes
-------
File: gamevisualnodes.cpp
- Eliminated the 20ms wire redraw debounce that restarted after every move.
- A card's ItemPositionHasChanged callback immediately updates only wires
  belonging to that card, using stable source/destination IDs.
- Cubic endpoints and neighbouring tangent handles move together. A self-loop
  translates as one complete path, so it stays attached to its own card.
- Cached incident-wire lists are rebuilt after each full redraw and cleared
  before old wire items are destroyed (including Undo/Redo scene rebuilds).
- Exactly one full geometric redraw occurs when the left-button node drag
  finishes, preserving the previous curve maths and styles.
- Scrollable scene bounds expand mid-drag only if needed.
- Wire selection, highlight/dim treatment and right-click disconnect stay.

File: splashscreenwidget.cpp
- Updated splash build to 5.166.88.291026.

Test notes
----------
- The new Stage 5.166.88 source contract test passes, as do 14 adjacent
  Visual Nodes stage tests (5.166.75-5.166.87).
- The full Qt GUI is not available to build/run in this environment; actual
  drag smoothness must be checked in the Linux Qt IDE.
- No .sbgm/.vsgm schema changes. No generated-game exporter or runtime
  changes. No changes to hand-maintained main.c. No game regeneration needed.
