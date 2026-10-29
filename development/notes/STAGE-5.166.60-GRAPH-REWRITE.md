# Stage 5.166.60 - Independent visual logic graph (experimental)

This stage adds **actual independent, chainable logic nodes** to the `.sbgm` game data.
It does NOT require a graph VM on the SIDBOX. The IDE generates ordinary C code.
The pre-existing `toggleState*` Trigger condition is retained for compatibility.
Do not remove it from an existing world until the new graph has been tested.

## Model

Every Trigger may own a `gameObject.logicNodes` array. Each entry has a stable
`id`, `op` (boolean, not, and, or), an ordered `inputs` array (`kind: object`
with a Game Object resource ID, or `kind: node` with another local logic ID),
and its own TRUE/FALSE actions and dialogue references. Every node is independent.

- Drag a Game Object state output onto blank canvas → Logic → Boolean / AND / OR / NOT.
- Drag another Game Object onto a logic card to add an input.
- Drag a logic RESULT socket to another logic card, or onto blank space to
  create a further logic node. This produces real node-to-node links.
- Drag a TRUE/FALSE socket to a Game Object and use the wire context menu to
  set Enable/Disable/Toggle. Drag it onto empty space → Dialogue Actions to
  choose an Adventure dialogue. Purple cards reuse familiar speaker/message controls.
- Delete and right-click Remove Connection remove the graph connections, not the
  Game Objects or dialogue resources.
- The usual collapsed Game Object Properties panels show the matching independent
  nodes on the owning Trigger and on Game Objects feeding those nodes. These panels
  also edit operator, state/logic inputs, TRUE/FALSE dialogue IDs and object actions.

An AND requires at least 2 inputs and OR requires exactly 2 inputs before **Save Graph + World** will allow
it. Boolean / NOT require exactly one input. Cycles and references to deleted
objects/nodes are rejected by both the graph editor and the export compiler.
Maximum 64 logic nodes per Trigger, 16 inputs per node and 64 actions per branch.

## Evaluation semantics

Graph conditions are evaluated only when the owning Trigger activates (not
continuously). Normal Trigger actions run first. All graph Boolean results are
then computed in topological order from the resulting states; finally their
TRUE/FALSE actions and single-message dialogue events execute in that order.
NOT inverts a single input. A logic node RESULT is a Boolean value and can feed
other logic nodes. TRUE/FALSE sockets are event/action outputs, not values.

Legacy single-condition fields stay intact and continue to execute separately.
Right-click an old Boolean card and choose **Convert to Independent Logic Node...**
to migrate that individual condition explicitly, retaining its action/dialogue IDs.
Creating new graph nodes does not silently convert or replace them. If a Trigger
has legacy and new logic both configured, both will execute. Inspect the world
before deleting an old condition.

## Files and safety

- `gamevisualgraphlogic.h`: shared schema validation, cycle detection and
  topological sorting, with C expression generation.
- `gamedesigner.h`, `gamedesigner_project.cpp`: lossless `.sbgm` persistence.
- `gamedesigner_export.cpp`: validates and generates the DAG C expressions.
- `gamevisualnodes.cpp`: independent draggable cards and source/branch wires.
- `gamedesigner.cpp`: editable collapsed properties for the same graph records.
- `splashscreenwidget.cpp`: build stamp.

No changes to `.map`, player saves, title/new/load game, or your hand-owned `main.c`.
Keep a backup of the `.sbgm` while testing this experimental new graph format.

## Important limitation

A complete Qt6 IDE compilation and physical SIDBOX runtime test have not been
performed in this environment. Existing game logic is not intentionally altered.
For a first test, use a separate copied game world and connect a Trigger to a lift,
then build `lift active → Boolean RESULT → AND with door active → Show Dialogue`.
Test the result in both Visual Nodes and Game Object Properties before touching
existing main-game puzzles.
