SIDBOX CoderGirl IDE - Stage 5.166.117.301026
UNIVERSAL GAME OBJECT STATE / EVENT LOGIC (SOURCE TEST BUILD)

BASE: the complete Stage 5.166.116.4 release, not a mixture of individual hotfixes.

CHANGED FILES:
  gamevisualnodes.cpp
  gamevisualgraphlogic.h
  gamedesigner.cpp
  gamedesigner_export.cpp
  idelibs/codehelpers/game/gameworlditems.rulec
  splashscreenwidget.cpp

Scope
- Existing Boolean / AND / OR / NOT cards and numbered INPUT N: name sockets remain.
- Logical state (teal) is distinct from one-frame event (gold). A branch's
  Enable / Disable / Toggle operation remains on its action wire.
- Gates can now be created from Trigger activation, Enemy ON DEFEAT and the
  named event outputs of Breakable, Enemy ON HIT, Hazard, World Door,
  Checkpoint, Moving Platform and Collectable. Every new event uses the
  same serialized event-input schema and existing graph scheduler.
- Collectables can own independent graphs; the exporter processes pickup
  owners using the existing world graph run/dispatch pipeline.
- Game Object Properties exposes the same event-input options; editing
  properties preserves saved per-input inversion.
- Named event flags are generated even for event-to-logic connections with
  no direct action wire. A Collectable-only world has a dedicated graph
  dispatcher when it needs one.
- Event-dependent nodes only dispatch when an event really happens. Their
  TRUE/FALSE branches never run during initial save-load synchronization.
- AND remains 2..16, OR 2..8, NOT/Boolean exactly one input. Switching a
  many-input graph to a one-input op warns rather than silently discarding data.
- .sbgm logic schema and the save-game identity/payload layout are unchanged.

KNOWN ARCHITECTURAL BOUNDARY
- Graph-to-graph RESULT links are still limited to gates owned by the same
  Game Object, because each owner's graph has its own runtime DAG schedule.
  A new GLOBAL scheduler is needed before direct cross-owner logic-node edges
  can safely be enabled.
- NPC Conversation and PLAYER action nodes are sinks, not Boolean state
  sources. They have no meaningful generic 'active' output to expose without
  a new state/event specification.
- A World Door's ON ENTER occurs near a world transition. Test dialogue and
  effects across the transition, as the current destination flow may override
  anything intended to persist after unload.

ACCEPTANCE TESTS (Fedora Qt build then SIDBOX hardware)
1. Existing Stage 116.4: bonkCollect ON DESTROY + Springer STATE => AND TRUE
   => BONK dialogue. Ensure it still fires once.
2. Lift ON ARRIVAL -> AND with switch STATE -> Toggle a Spring.
   Check successive arrivals and no action during save load.
3. Hazard ON PLAYER HIT -> Boolean TRUE -> Dialogue, without a direct
   ON PLAYER HIT action wire.
4. Collectable ON PICKUP -> Boolean TRUE -> change a Decoration, also in a
   world containing only Collectables. No duplicate action next frame.
5. Enemy ON DEFEAT -> AND -> toggle target; ON HIT is distinct from defeat.
6. Checkpoint ON SAVE fires only when a confirmed write succeeds.
7. Trigger activation -> AND (another input) -> dialogue.
8. Make eight OR inputs; ensure ninth rejected. Check AND up to sixteen.
9. Edit a graph in Game Object Properties then reopen Visual Nodes. Check
   names, inputs, event IDs, positions, and true/false output actions.
10. Multi-world generation, save/load and TFCard compatibility check.

VERIFICATION HERE
- Source-level and existing template render tests pass.
- Qt development libraries are NOT available here: full IDE compilation,
  generated multiworld C compilation, and real SIDBOX hardware run remain
  unverified. Please build this as a TEST release, not your stable baseline.
