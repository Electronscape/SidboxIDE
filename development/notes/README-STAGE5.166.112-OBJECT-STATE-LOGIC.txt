SIDBOX CoderGirl IDE - Stage 5.166.112.291026
Object STATE -> independent Visual Node logic

Baseline: complete Stage 5.166.111.1 source, including the arrival picker,
independent enemy logic and Stage 5.166.109 save identity protection.

FIX
- Teal STATE output on stateful Game Objects (e.g. Spring) can create and
  own Boolean, NOT, AND, OR logic directly. No unrelated Trigger or Stompable
  Enemy activation/owner is needed.
- For source STATE drags, Logic is first and expanded in the connection picker.
- Object-hosted graphs are saved in the world .sbgm, restored in Visual Nodes,
  visible in Game Object Properties, and preserved by an ordinary world save.
- Export validates and emits the graphs on world Game Objects, including Spring.
  An arrival action that toggles a Spring is a change event for any graph
  reading the Spring. The existing event dispatcher runs this graph once.
- The original ON ARRIVAL pulse and direct Toggle action are unchanged.
- Removing the last logic node clears the persisted graph from the owner.
- Cross-world copy remaps a state input referencing the newly copied owner.

NOTES
- This is event-driven logic, not a free-running per-frame logic VM.
  Actions/events that update an input trigger evaluation. The initial world
  sync is restricted to safe state bindings/idempotent actions as before.
- Collectable state is not a graph host in this release, since it belongs to
  the separate pickup runtime array. Its ON PICKUP action remains supported.
- Existing in-world saved slots are still governed by the same v3 save identity
  compatibility logic. The schema was not changed by this patch.
- Direct ON ARRIVAL -> Springer with Set Toggle works without any logic node.

FIRST HARDWARE TEST
1. Drag from Springer's teal STATE -> Logic -> AND.
2. Connect a second input, e.g. enabled switch. An AND needs 2 inputs.
3. Connect TRUE -> a decoration or other compatible target, choose Enable or
   Toggle on the action wire as appropriate.
4. Connect Lifty ON ARRIVAL -> Springer, choose Set Toggle.
5. Save world; reopen Visual Nodes to check both wires and graph persist.
6. Generate/rebuild game and verify gate reacts to arrival state transitions.

VERIFICATION
- 5 focused regression tests passed, including a native C arrival/toggle/AND
  simulation and source-based generator/persistence checks.
- The existing Stage 110 template renderer smoke test passed.
- A complete Qt build and SIDBOX hardware test were not possible here.
