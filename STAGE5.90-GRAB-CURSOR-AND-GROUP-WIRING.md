# CoderGirl Stage 5.90 (24 October 2026)

## Logic Flow Debugger: group grab cursor and visible cross-group wiring

### 1. Drag affordance
- Hover over an **automatic array group** or a **manual logic group** to see the open-hand grab cursor.
- Left-drag that group and the cursor becomes a closed hand during the drag, returning to an open hand on release.
- A small six-dot grip (`⋮⋮`) appears at the upper-right of both root group headers and nested array group headers. You can drag by this area.
- Ordinary node cards, canvas panning, group toggle controls and double-click title renaming keep their existing controls.

### 2. Wiring above group fill but under cards
- Previously, wires from inside an expanded group to an outside node were drawn at scene z=-2 but the group background was part of the group card at z>=2. That completely hid the portion inside the group.
- Group **background fills** now use independent, mouse-transparent scene panels. They follow the corresponding group frames during moving, resizing and nesting. They sit behind scene-level wires, and above the world background.
- Group **borders, headers, controls, actual cards and mini-cards** stay at their existing foreground layers. Links do not draw across their opaque faces.
- Wires wholly contained inside a group are still rendered inside that group's hierarchy (above its fill, below its children), including nested arrays.
- Background panels respect the click-to-front order, while remaining below the wire layer. The panel order is normalized within a bounded z range, so repeated clicks cannot lift a panel over a wire.
- The existing separate coloured reciprocal wires, click-to-front, drag in/out grouping, the Dialogue Choice double-click inspector and IDE-theme palette are preserved.

### Changed files
- `gamefloweditor.cpp`
- `splashscreenwidget.cpp` (splash: `Build: 5.90.241026`)

There are **no** game runtime, generator, world-data, `main.c`, resource, or saved diagram format changes.

### Fedora manual testing checklist
1. Rebuild the Qt6 IDE and open Logic Flow with an expanded Logic Group containing an Array Group.
2. Hover over each group: open hand; hold and drag: closed hand; release: open hand. Drag from the six-dot grip too.
3. Move the outer group and nested array. Their filled panels must move with the cards, including when a nested array is pulled out and placed back in.
4. Inspect a connection from inside an expanded group to an outside node. The wire must be visible across the group's body but disappear *under* the opaque header and individual cards.
5. Click overlapping groups. Both the group card and its fill should come to the front relative to other group fills, with connectors still under cards.
6. Verify internal group links, red-to-green arrows, reciprocal arrows, selected-link highlighting, and double-click Dialogue Choice.

### Verification
32 targeted source/layering checks passed, plus all 19 Stage 5.89 relationship/inspector regression checks. The environment does not have Qt6 development headers, so this is not yet a compiled or interactive GUI test.
