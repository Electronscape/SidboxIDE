SIDBOX Stage 5.166.116.2 (30 October 2026) - Logic Input Compatibility/Diagnostic Hotfix

Full source is based on the complete Stage 5.166.116.1 (not a two-file patch over Stage 114).

What caused the screenshot's warning:
- Stage 114 gamevisualgraphlogic.h accepts @event:arrival:... but not
  @event:hit:... or @event:destroy:... . The newer Visual Nodes source
  can draw the ON DESTROY connection even if the older parser header is still
  in the installed source tree, and Save Graph + World will then reject it.
- Stage 115 and newer versions include the correct event kinds.
- Without the actual just-edited .sbgm file from the screenshot, an additional
  malformed stored input cannot be ruled out. This release makes that case
  diagnosable by reporting the exact INPUT index, kind, and id.

Fix:
- Distribute a COMPLETE, matched source tree with the Stage 116.1 picker,
  the Stage 115+ event-aware graph parser, exporter and runtime rule files.
- Improved graph parser errors now identify the offending input rather than
  suggesting your wiring is wrong.
- No gameplay, logic rules, save payload, or generated runtime behaviour changed.
- Splash build: 5.166.116.2.301026.

Testing:
- Focused source/regression checks including exact ON DESTROY + springer1
  two-input AND fixture (structural check).
- Full Qt GUI compilation was not available in this environment.

Usage:
1. Back up your IDE source/project.
2. Extract FULL archive to a clean directory; don't layer only the old ZIP.
3. Build in a clean CMake build directory.
4. Verify splash 5.166.116.2.301026.
5. Save the same graph, without changing wires.
If there is still an error, send the exact new INPUT diagnostic and the
world's latest .sbgm file so the malformed record can be inspected.
