SIDBOX CoderGirl Stage 5.166.111.1.291026 - ON ARRIVAL Logic Picker Visibility

This is an IDE-only discoverability fix based on Stage 5.166.111.

The reported picker with ONLY Game Objects / NPC Conversations / PLAYER
exactly matches the previous Stage 5.166.110 executable. In Stage 111,
Logic was already added, but last in the collapsed tree.

Changes:
* Drag the GOLD ON ARRIVAL output to EMPTY canvas: Logic now appears FIRST,
  already expanded with Boolean, AND, OR and NOT choices.
* A small help line explains the existing direct Toggle action alternative.
* Tooltip distinguishes gold ON ARRIVAL from teal STATE.
* No runtime/export changes, object schema changes, or new flip-flop node.
* Splash screen identifies Stage 5.166.111.1.291026.

HOW TO USE
1. Close the old IDE and compile/run THIS source. Confirm splash build.
2. Visual Nodes: drag the GOLD ON ARRIVAL socket of a lift to EMPTY canvas.
3. Choose Logic -> Boolean, then connect TRUE to a Decoration.
4. Right-click the new action wire -> Toggle.
5. Alternatively draw ON ARRIVAL straight to the Decoration and Toggle
   that wire, with no logic needed.

SOURCE PATCH: gamevisualnodes.cpp, splashscreenwidget.cpp only.
Qt compilation unavailable in author environment; run your Fedora Qt build.
