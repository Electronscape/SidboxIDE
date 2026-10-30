SIDBOX CoderGirl IDE, Stage 5.166.111.291026 (29 October 2026)
ON ARRIVAL -> existing independent Logic -> existing Toggle action

BASELINE
Full Stage 5.166.110 game object event release. Apply either the complete
archive or just the changed production files to Stage 5.166.110.

WHAT THIS DOES
- Moving Platform ON ARRIVAL (gold output) can now create a Boolean, AND,
  OR or NOT logic node by dragging to empty space and selecting Logic.
- The event is an instant, one-frame pulse, NOT the platform's enabled
  state. Existing teal STATE sockets retain their original meaning.
- Lift-owned independent logic is persisted in the .sbgm's logicNodes
  just like Trigger- and Enemy-owned independent logic. Both Visual Nodes
  and Game Object Properties display/edit the same stored graph.
- The C generator detects lift arrivals, evaluates the existing DAG once
  per event, and dispatches its existing TRUE/FALSE action commands.
- Existing action Toggle is already a flip-flop equivalent for a target's
  enabled/disabled state. No new flip-flop node, save payload, runtime state
  or Boolean operator has been added.
- Startup/save-load initial logic sync does not fire a lift event branch.
- A later unrelated Trigger call cannot replay an earlier arrival pulse.
- Copying a lift to another world remaps its OWN ON ARRIVAL event ID to
  the copied lift's newly generated UUID.

HOW TO USE
A. Simple alternating light: Lift ON ARRIVAL -> Decoration or switch.
   Right-click the golden action wire -> Toggle. Each arrival reverses it.
   (This direct-action Toggle was already available in Stage 110.)
B. Conditional alternating light: Drag Lift ON ARRIVAL gold socket to empty
   graph space -> Logic -> AND. Add a second input from your switch's teal
   STATE socket. Connect the AND TRUE output to your Decoration and set
   that action wire to Toggle.
   Arrival with switch inactive: no change. Arrival with switch active:
   reverse Decoration. A later change to the switch alone does nothing.
C. Boolean ON ARRIVAL -> TRUE Toggle is useful when no extra condition is
   needed but you want a logic card for subsequent branching or dialogue.

IMPORTANT SEMANTICS
- ON ARRIVAL pulses only at spline knot/segment arrival, not every frame
  the lift is stopped at an endpoint.
- An OR node containing ON ARRIVAL is necessarily TRUE each time arrival
  evaluates; for a gated action use AND instead.
- The output of Toggle is the toggled object's persistent active state.
  There is no additional stateful flip-flop node.
- Stage 5.166.109 v3 save identity and dual-bank behaviour are unchanged.
- Full Fedora Qt compilation and hardware acceptance still need checking.

VERIFICATION
31 selected Python/native-C regression tests passed, including 5 new
arrival-logic tests. Source literal scan passed. The native C microtest
models ON ARRIVAL gating and one-time Toggle; it is not a full generated
C or actual STM32H743 hardware run.

MODIFIED PRODUCTION FILES
gamedesigner.cpp
  Game Object Properties sees lift-owned logic and ON ARRIVAL input.
  Copy/paste remaps a lift's own event input UUID.
gamedesigner_export.cpp
  Validates the lift's event source; emits pulse-driven conditional actions;
  allows a lift-owned logic DAG; prevents its replay during save-load.
gamedesigner_project.cpp
  Retains lift-owned logicNodes on a normal .sbgm world save.
gamevisualgraphlogic.h
  Adds an event input type to existing Boolean/AND/OR/NOT parser/evaluator.
gamevisualnodes.cpp
  Gold socket -> existing Logic menu and live wiring; saved links and
  object cards reload, with lift graph ownership support.
splashscreenwidget.cpp
  Build label: 5.166.111.291026.

NOTE ON COPY/PASTE
The original graph's other referenced objects must be present in the
new world, as with older Trigger/Enemy graph copies. The self-event UUID
is remapped; this patch is not a general cross-world dependency importer.
