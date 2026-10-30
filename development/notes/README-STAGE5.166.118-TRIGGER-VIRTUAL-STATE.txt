SIDBOX / CoderGirl IDE
Stage 5.166.118.301026 - Virtual Trigger ON/OFF state (TEST BUILD)

Baseline: Complete Stage 5.166.117.301026

THE PROBLEM
The trigger's old gold output issues actions (ON ACTIVATE). The Trigger's
physical active flag means 'enabled to fire', NOT 'the player activated it'.
It cannot safely stand in for an AND gate's remembered condition.

THE CHANGE
Every ordinary Trigger card now has two teal READ-ONLY condition sockets:
  STATE ON  - its virtual switch is ON
  STATE OFF - its virtual switch is OFF
The virtual switch begins OFF; each SUCCESSFUL trigger activation toggles it.
No visible decoration, sprite, resource or new Game Object type is created.
The gold action output and original action links are unchanged.

To build a gate owned by another Game Object:
  1. On the Trigger card, drag teal STATE ON or STATE OFF.
  2. Drop onto an existing AND/OR/NOT input, or create a new logic gate.
  3. Add other STATE/event inputs as usual.
  4. A gate's original INPUT 1/2/3 names show 'stopLift (ON/OFF)'.

A one-shot Trigger usually stays ON after its only activation, unless another
supported action re-enables that Trigger. The virtual state is *not* an
ON PRESS / ON RELEASE pulse. Repeated activation alternates ON and OFF.

RUNTIME / SAVE
- Each world has a compact virtual switch state array, indexed by its existing
  generated objects. Successful Trigger activations toggle the latch before
  independent logic evaluates. Gates on other objects are notified of it.
- The array persists across world unload/reload, TFCard save/load and is reset
  to OFF by New Game.
- The disk payload size changes for worlds with Triggers. Previous saves of
  those worlds are incompatible and should be backed up first. The existing
  v3 save-header identity/size checks and two-bank implementation are unchanged.
- RESULT cannot assign directly to the virtual Trigger switch. It is a
  read-only condition source, driven by its owning Trigger's activation.
- Cross-world graph logic is still not a global DAG: only local-world
  Trigger state sources are supported.

TESTS RUN
- New Stage118 focused tests: 4 passed, including native C latch semantics.
- Existing Stage110 rule-template combinations: 1 passed.
- Existing Stage117 logic source contracts: 8 passed (version-only test skipped).
- Qt6 full build and SIDBOX hardware validation are NOT available here.

Recommended hardware test:
  - Keep Stage117 backup and archive old save slots.
  - Connect stopLift STATE ON to your kim ON PICKUP AND gate (INPUT 2).
  - Before activating stopLift, picking kim should not run the TRUE branch.
  - After activating stopLift, picking kim should run the TRUE branch.
  - Test STATE OFF with a second trigger activation and a repeatable test item.
  - Test saving/loading the state and New Game reset.

Changed files:
  gamevisualnodes.cpp
  gamedesigner.cpp
  gamedesigner_export.cpp
  gamevisualgraphlogic.h
  idelibs/codehelpers/game/gameworlditems.rulec
  splashscreenwidget.cpp

New tests: development/tests/test_stage5166_118_trigger_virtual_state.py
