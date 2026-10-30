SIDBOX CoderGirl IDE — Stage 5.166.114.291026
================================================
Base: full Stage 5.166.113.1 (Qt compiler hotfix retained).

Visual Nodes / Independent Logic:
- OR now accepts 2 through 8 state / result / arrival-event inputs (previously exactly 2).
- Numbered OR input sockets start at 2 and automatically add one spare while below 8;
  they shrink when inputs are disconnected. AND retains its existing 2..16 limit.
- A ninth OR input is refused with an explanation. Existing input order is preserved.
- Switching a gate with >8 connected inputs to OR prompts to disconnect some first;
  no input wires are silently dropped.

Legacy Trigger state logic:
- OR now accepts 2..8 unique local Game Object inputs in the Trigger properties,
  visual state card and game exporter. The generated expression uses || across all.
- Existing Boolean/AND limits and semantics are unchanged.

No new node type, no schema change, no change to save-game format, object identity
fingerprinting or dual-bank saves. Existing two-input OR graphs remain valid.

Files changed:
  gamevisualnodes.cpp
  gamevisualgraphlogic.h
  gamedesigner.cpp
  gamedesigner_export.cpp
  splashscreenwidget.cpp
  development/tests/test_stage5166_113_logic_input_sockets.py (updated expectation)
  development/tests/test_stage5166_114_or_eight_inputs.py (new regression tests)

Verification:
- Source/contract tests and standalone C++ socket-math compile tests pass.
- Full Qt build not available in this environment (no Qt6Widgets dev package).
- Hardware operation on SIDBOX remains to be confirmed by the user.

Suggested quick test: create OR from a state output, add three (then eight)
independent inputs, ensure wires occupy separate numbered squares and the gate
passes when ANY input is active. Disconnect one and verify the card shrinks.
