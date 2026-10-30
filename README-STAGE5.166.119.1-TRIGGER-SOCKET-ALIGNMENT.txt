SIDBOX / CoderGirl IDE Stage 5.166.119.1 (30 October 2026)
Trigger virtual-switch socket alignment hotfix (editor only)

BASELINE: Stage 5.166.119.301026, whose event/action/dialogue queues were
successfully tested on SIDBOX hardware.

FIX:
- Trigger card height grows from 272 to 298, giving STATE ON and STATE OFF
  individual rows below the embedded Trigger settings panel.
- Both text labels are vertically centred using their measured Qt text bounds,
  exactly on the same centreY coordinate as their corresponding socket.
- Both labels right-align consistently with a 15.5px gap before the socket.
- Logic-input wire fallback anchors use the new centres (243/273); the normal
  path still resolves the real scene position by stable virtual socket ID.
- Updated splash build version.

UNCHANGED:
- .sbgm and .vsgm formats, saved graph IDs, trigger virtual-switch semantics.
- Stage 119 event/action/dialogue queues and all generated runtime files.
- TFCard save/load format and multi-world state.

INSTALL:
- Easiest: extract SIDBOX1191-Full.zip into a fresh directory, build your IDE.
- Existing Stage 119 source: overwrite gamevisualnodes.cpp and
  splashscreenwidget.cpp from SIDBOX1191-Visual-Fix.zip and rebuild.

VERIFY:
- Splash: Build: 5.166.119.1.301026
- Open Visual Nodes on your stopLift + AND graph; check STATE ON/OFF text
  appears centred with each circle and the teal wire joins the right circle.
- Fold/unfold and drag stopLift and check that the wire follows the socket.

TESTS:
- 19 tests passed: 5 new socket alignment checks, 5 Stage 119 queue checks,
  4 updated legacy trigger-label checks and 5 wire-geometry checks.
- Full Qt compilation and visual tests not possible in this container.
