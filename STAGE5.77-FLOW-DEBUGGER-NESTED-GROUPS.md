# Stage 5.77 (24 October 2026): Flow Debugger drag-to-group and reciprocal connections

## Modified files

- `gamefloweditor.cpp`
- `splashscreenwidget.cpp` (`Build: 5.77.241026`)

No `.sbgm`, game runtime, generated code, `main.c`, project assets, or unrelated IDE source changed.

## Drag into an existing logic group

Drag a standalone card, or an existing automatic ARRAY GROUP card, onto a manual LOGIC GROUP in the **same world** and release it with a substantial overlap.

- The logic group expands to reveal the new child.
- A regular card becomes a movable mini card in the logic group.
- An automatic array stays a **nested, independently expandable ARRAY GROUP** with its member cards preserved. The array card itself can be positioned inside the logic group.
- Moving the parent logic frame carries nested contents and their connections with it.
- Layout and nested-array parentage are persisted in `<project>/.sidbox-flow-layout.json` (layout version 4). Existing version 3 files remain loadable.
- Ungrouping the logic group returns any embedded automatic arrays to top-level cards.
- No cross-world drag-into-group, and no manual-group-inside-manual-group nesting.

The actual game-design `.sbgm` files are **read-only** to the Flow Debugger and aren't rewritten by this change.

## Directional connection clarity

When the diagram contains both `A -> B` and `B -> A`, each direction now uses a **separate parallel curved wire** instead of overlapping one line. Both display the established source-red to destination-green gradient and a green destination arrowhead. Same-direction duplicates still share a path with combined tooltips. All existing Green Trace and link highlighting controls remain.

## How to test on Fedora

1. Compile the IDE from these replacement files.
2. Open Game Flow Debugger, world1, and the existing “Give Kim her Flower!” logic group.
3. Drag a standalone card over the logic group, release, then expand/collapse the group and check it reopens with the new card inside.
4. Drag a `kim[]`, `Phreight[]` or other array group onto the same manual group; expand the nested array, move it inside the parent and save by closing.
5. Reopen the debugger, check the nested group and positions survived, then optionally ungroup the parent and check that the array group returns intact.
6. Inspect `Em Sel` / “Nothing to give” or any other known bidirectional link; verify two parallel red-to-green directional wires.

## Verification

- 21 static/model regression checks passed, including existing saved flow-layout compatibility and a nested-group visibility model.
- The source was not compiled against Qt6 in this environment. The final Fedora GUI and mouse interaction test is still needed.
