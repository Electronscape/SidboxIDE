# SIDBOX CoderGirl Stage 5.54.231026: Manual Group Mini-Graphs and 8px Snap

Based on Stage 5.53.231026. This update changes only the design-time Logic Flow editor, its project-local layout JSON, documentation/tests, and the splash build number. No changes to game code generation, .sbgm world design, PPB graphics, SIDBOX firmware, or TFCard contents.

## Controls

- **Ctrl+G**: create a named *manual* group from at least two selected cards within one world. Drag on empty canvas to rectangle-select.
- **Ctrl+Shift+G** or **Ungroup (Ctrl+Shift+G)**: dissolve the selected manual group. Works when either the group's frame **or a mini card inside it** is selected. Automatic indexed-name groups are not ungrouped.
- **+ / −** in a group header: expand or collapse the group.
- **Expanded manual groups**: individual mini cards can be dragged inside the group. The group's own incoming/outgoing links attach to its frame; internal links show as visible curved lines with arrowheads behind the mini cards. Each link retains its action tooltip.
- **Expanded array groups** (`kim[]`, `Guardian[]`, etc.): remain simple two-column collections without mini connectors or independent member dragging.
- **Drag the group frame/header**: moves all mini cards and their internal wires together.
- **Snap 8px**: checked by default; snaps ordinary cards, group frames and movable mini cards to multiples of 8 scene/parent pixels. Uncheck for free placement. The toggle is saved per project.
- **Clean Layout** / **Spread Left to Right**: still arrange the outside graph without deleting group membership or saved mini-card arrangement.

## Saved data

The existing project-local `.sidbox-flow-layout.json` now uses version 3 and adds:

```json
{
  "version": 3,
  "positions": {},
  "groups": [],
  "expanded": {},
  "memberPositions": {"flow-group/manual/world1/1": {"world1/object/example-id": {"x": 24, "y": 88}}},
  "snapToGrid": true
}
```

`memberPositions` stores manual-group child positions **relative to the parent frame**. Moving the group does not mutate these offsets. Old V1 and V2 files without these fields remain readable and use default group layouts and enabled snapping. Position values are bounded and validated on load. The internal default mini layout follows outgoing graph links, seeded from zero-incoming nodes, with a five-column cap to handle cycles.

The group frame grows when a mini card is moved beyond its right/bottom edge. Mini cards cannot be dragged above/left of the content area. Ungrouping an expanded manual group places its former cards at their on-screen scene coordinates.

## Source changes

- `gamefloweditor.cpp`: group-local mini positions; embedded connector items with correct scene/parent coordinate conversion; 8px position snapping and toggle; Ctrl+Shift+G selection resolution for child nodes; separate rendering for expanded manual vs array groups.
- `splashscreenwidget.cpp`: `Build: 5.54.231026`.
- `development/tests/test_stage554_logic_flow_groups.py`: source-contract and edge-routing assertions for old/new behaviours.

## Testing and known limitation

- PASS: Stage 5.54 source-contract and connector routing test, including internal, cross-boundary, collapsed, and auto-array cases.
- PASS: unchanged runtime-bearing `gamedesigner.cpp` and `gamehudeditor.cpp` source comparison with Stage 5.53.
- Verified against Qt 6 API documentation: `QGraphicsItem::mapFromScene` supports both `QPainterPath` and `QPolygonF` conversions.
- **NOT Qt compiled here**: this environment has no Qt6 development headers. Fedora compile, interactive moving/expanding, save/reopen, multi-select and exit-crash testing remain necessary.

## Suggested Fedora test

1. Apply Stage 5.54 to the Stage 5.53 source tree, rebuild SidboxIDE, and launch Logic Flow.
2. Select 3+ linked cards in one world and press Ctrl+G. Expand the group. Confirm arrows appear between the mini cards.
3. Drag individual mini cards and confirm arrows track them and the group grows if necessary. Drag the whole group next.
4. Close/reopen Logic Flow. Confirm the frame and mini-card offsets persist. Toggle Snap 8px off/on and confirm fine movement vs 8px steps.
5. Select a mini card inside the manual group and press Ctrl+Shift+G. Confirm the group dissolves without teleporting its cards.
6. Expand an automatic `name[]` group and confirm its members are still a simple card list.
7. Repeat Fit Graph, wheel zoom, world switching and close/reopen to exercise the original crash path.
