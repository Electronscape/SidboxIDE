SIDBOX / CoderGirl IDE Stage 5.166.80 (28 October 2026)
Visual Nodes: non-bowing conversation curves, branch-aware Tidy, graph Undo/Redo

CHANGES
1. Conversation-flow purple and dashed amber preview links use the same flat-
   tangent cubic between actual socket endpoints. An artificial downward 16px
   bend on missing-item branches was removed. Dashed amber appearance remains.
2. Tidy now discovers weak connected components using displayed links, chooses
   graph levels while coping with feedback cycles, reorders same-level cards
   through eight barycentric parent/child sweeps, and uses iterative child-
   centering for visible branch grouping. Unrelated clusters are separated.
   It changes layout only: does not edit gameplay connections or dialogue IDs.
3. Full in-memory session history records pending graph state AND layout:
   connections, node placement, collapsed states, NPC settings, dialogue edits,
   and conversation route/view state. Toolbar Undo and Redo buttons added.
   Ctrl+Z = Undo; Ctrl+Shift+Z or Ctrl+Y = Redo. Keyboard Undo/Redo inside
   editable text controls still edits that text, not the whole graph.
4. History groups successive edits after ~360ms of inactivity; an immediate
   toolbar/shortcut Undo commits any pending edit first. Up to 80 snapshots.
   Tidy explicitly records before and after so it can be undone instantly.
5. Save Graph + World starts a NEW undo history. Undo is session-scoped and
   does not roll back previously saved .sbgm files or across editor restarts.
   Both undo and redo restore unsaved graph data; to keep result use Save.
6. Splash version: Build: 5.166.80.281026.

INSTALL
1. Back up current IDE source AND game .sbgm/.vsgm project files.
2. Extract this FULL source archive over Stage 5.166.79.
3. Rebuild IDE; confirm splash version 5.166.80.281026.
4. Open Forest > Visual Nodes > Big Steve conversation flow.
5. Inspect amber dashed item-missing route for no downward bowed hump.
6. Tidy -> Yes: compare connected branches vs prior column-only layout.
7. Ctrl+Z should restore old layout, Ctrl+Shift+Z / Ctrl+Y should redo.
8. Move a node, delete a wired node (confirm), undo, redo, then undo again.
   Check restored wires and their saved .sbgm action values.
9. Edit text in a dialogue and Ctrl+Z while text field is focused: text-level
   undo should work independently from graph-level shortcuts.
10. Save Graph + World to persist changes. No game regeneration required
    unless you intentionally modified gameplay connections/dialogue properties.

VERIFICATION
- 21 related historical/source regression checks passed, including Stage
  5.166.80 branch layout/undo contract. Game generator code unchanged.
- Qt 6 development headers are not available here; a full IDE compile and
  interactive GUI acceptance test on your desktop is still required.
- No edits to user-maintained main.c or generated game runtime.
