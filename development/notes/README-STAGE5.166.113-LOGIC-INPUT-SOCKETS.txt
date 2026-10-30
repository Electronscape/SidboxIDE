SIDBOX IDE — Stage 5.166.113.291026 — Dynamic Logic Input Sockets
29 October 2026

Baseline: Complete Stage 5.166.112.291026.

Visual Nodes now displays independent logic inputs as individually numbered teal
squares instead of stacking every incoming wire on a single input socket.

  BOOLEAN / NOT: one socket
  OR:            two sockets (exactly two inputs required by existing parser)
  AND:           two initial sockets; one additional empty socket appears
                 whenever the previous spare is connected, up to sixteen.
                 After a disconnect, unused extra sockets are removed.

Input labels identify the connected Game Object or upstream logic source.
Wires terminate on the corresponding indexed socket. Cards grow vertically
as inputs increase, and the RESULT/TRUE/FALSE outputs plus Logic control
move with the expanded card. Collapsing and re-expanding preserves the ports.

Pure visual/editor change:
  * No modifications to .sbgm, .vsgm, generated runtime C, save identity,
    object state semantics, and existing action/logic operator limits.
  * Wire creation/removal remains the same: drag to an input square; right-
    click the connected wire to Remove Connection.
  * AND/OR still require at least two actual connections before the graph
    can be successfully saved/exported. A visible empty socket isn't an input.

Changed production files:
  gamevisualnodes.cpp       Logic card layout, routing, resizing and tooltip
  splashscreenwidget.cpp    Build: 5.166.113.291026

Tests:
  development/tests/test_stage5166_113_logic_input_sockets.py

Local validation:
  * 5 focused geometry/behaviour-source tests passed.
  * 37 selected regression tests passed after modernising version expectations.
  * 4 historical Stage 108/111 source-literal assertions are outdated since
    Stage 112, and aren't used for this release's acceptance.
  * Qt6 compiler libraries were unavailable in this environment; Fedora
    Qt compilation and UI/SIDBOX acceptance remain to be performed.

Smoke test:
  1. Open Visual Nodes, create an AND from Springer STATE.
  2. Observe INPUT 1 connected and INPUT 2 available.
  3. Connect another state source: INPUT 2 fills and INPUT 3 appears.
  4. Connect a third state source: INPUT 4 appears.
  5. Right-click a wire and Remove Connection: extra ports disappear.
  6. Save, close, reopen: same connections/ports; outputs stay aligned.
  7. Toggle the lift and test the existing AND TRUE branch on hardware.
