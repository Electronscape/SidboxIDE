SIDBOX / CoderGirl IDE Stage 5.166.78 (28 October 2026)
Conversation destinations: Adventure folder tree + popup stacking fix

WHAT CHANGED
- gamevisualnodes.cpp: The Next dialogue control on an expanded conversation
  node still shows a readable '#ID | Speaker: text' selection.
- Clicking the arrow opens a separate modal 'Choose Next Dialogue' window,
  rather than a combobox list embedded in the QGraphicsScene. This avoids
  normal popup z-order/occlusion problems behind other graph nodes.
- The chooser uses the Adventure Editor's existing dialogueFolders/folderId
  hierarchy, supporting nested folders, unfiled dialogues, and text search.
- A Close conversation entry writes -1, preserving existing semantics.
- Missing saved IDs are visible and cannot be accidentally selected as valid.
- Cancel makes no change. A folder isn't an actionable destination.
- The existing numeric dialogue ID is still stored in adventure.nodes[*].choices[*].next.
- No gameplay exporter/runtime changes, no new .sbgm/.vsgm fields, no main.c changes.
- splashscreenwidget.cpp: Build: 5.166.78.281026.

INSTALL
1. Back up your current source and game project.
2. Extract this FULL source archive over Stage 5.166.77.
3. Rebuild IDE and check splash version 5.166.78.281026.
4. Forest > Visual Nodes > Show Big Steve opening conversation flow.
5. Open an answer's Next selector. The separate chooser should appear above
   the node canvas and show your Adventure dialogue folders.
6. Try a folder, search, Close conversation, Cancel and selecting a dialogue.
7. Save Graph + World, close/reopen and verify the same destination and wire.

VALIDATION
- Relevant historical visual node, independent logic, NPC, PLAYER, weather,
  and save/load source/native regression checks passed.
- New stage 78 source contract covers modal tree, existing folders, selecting
  numeric IDs, Close/Cancel/MISSING and the z-order design change.
- This environment has no Qt 6 development headers; the desktop interface
  still requires a build and mouse/keyboard verification on your machine.
- No generated game rebuild is needed for this UI-only release.
