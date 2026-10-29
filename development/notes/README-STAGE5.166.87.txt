SIDBOX / CoderGirl IDE Stage 5.166.87 (29 October 2026)
Connection Focus / Visual Wire Tracing

INSTALL
  Back up your Stage 5.166.86 IDE source and game project.
  Extract this full source archive over Stage 5.166.86 and rebuild CoderGirl.
  Splash build: 5.166.87.291026.
  This is an IDE-only update. Regenerating the game is not necessary.

VISUAL NODES
  - Left-click a card (including its header) to highlight every incident
    input and output wire and outline the connected endpoint cards.
  - Left-click the visible part of a wire to select that exact connection.
    Its two endpoint cards are outlined; the other wires fade to 12% opacity.
  - The details panel shows the chosen route and source/destination IDs.
  - Click empty canvas or press Esc (with canvas focused) to clear focus.
  - Right-click on wires still offers their original edit/disconnect menu.
  - Wire hit testing retains its generous 20px invisible stroke.
  - Selection survives a redraw when moving, collapsing or expanding cards.
  - Original route colours/dashes and wire layering behind cards are retained.

SAFETY
  Visual highlighting is transient UI state only, not saved as gameplay data.
  No gameplay exporter changes, world format changes, or main.c modifications.
  Existing link semantics, including loops and GIVE response routes, remain.

VALIDATION
  20 focused source-level regression tests passed (Stages 5.166.70-87).
  Actual Qt desktop compilation and mouse interaction need user verification.

FILES
  gamevisualnodes.cpp
  splashscreenwidget.cpp
  development/tests/test_stage5166_87_connection_focus.py
  existing source tests updated for splash build number
