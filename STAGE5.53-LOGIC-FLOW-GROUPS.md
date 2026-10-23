# SIDBOX CoderGirl Stage 5.53.231026: Logic Flow Groups

Based on the Stage 5.52.231026 IDE source.

## New design-time UI

- **Drag a rectangle on empty graph space** to select multiple logic cards.
- **Ctrl+click** to adjust the selection; **Ctrl+G** or **Group (Ctrl+G)** creates a named, collapsed, draggable group from two or more cards.
- A manual group must contain cards from a single world. You can group individual cards while an automatic group is expanded. Nested group containers are not supported in this version.
- **Ungroup** or **Ctrl+Shift+G** dissolves a selected manual group. Automatic array groups are not removed, but can be expanded.
- Array-named objects like `kim[0]`, `kim[1]`, ... are automatically recognised (within the same world, regardless of an individual object behaviour). Two or more matching entries form a collapsed `kim[]` group by default.
- **Click the small + or - in the upper-left of a group card** to expand or collapse it. When expanded, original member cards are shown in a two-column layout and can be clicked for individual details.
- **Drag a group by its header**, even when expanded, to move it and all of its visible members together. Connectors reattach as the group moves. Internal links are hidden when collapsed; external links connect to the group border. Duplicate collapsed links use one arrow with combined tooltip information.
- **Middle-mouse drag or Alt+left drag** pans. Ordinary left-drag over empty canvas is now rubber-band select; wheel zoom, Fit Graph, 100%, Clean Layout and Spread Left to Right remain.
- Clean Layout and Spread Left to Right retain manual and automatic group membership and expansion state. They only rearrange visible group containers and ungrouped cards.

## Saved data and compatibility

All positions and manually created group metadata live in the project's `.sidbox-flow-layout.json`. Its version is now 2, with `positions`, `groups` and `expanded`. Existing version-1 `positions` are read unchanged. Automatic array membership is recalculated from saved `.sbgm` data when Logic Flow opens or reloads; manual groups use stable node IDs rather than display labels. Group positions and expanded/collapsed state are restored next time.

There are no changes to `.sbgm`, runtime C generation, PPBs, inventories, physics, world transitions or firmware. This remains a pure IDE/design-time feature. Grouping changes the visual graph only.

## Test coverage and limitations

- Source checks verify the new selection mode, Ctrl+G and Ungroup shortcuts, group expansion callback, read/write paths for V2 layout metadata, group-aware connector routing and original navigation controls.
- Source checks against the user's saved two-world GameTest3 find automatic array families `kim[0..5]`, `Phreight[0..5]` and `spikey[0..2]`.
- **Not yet Qt compiled:** The local environment lacks Qt6 >=6.5 headers and libraries. The first complete GUI compile, interactive drag/expand test and long-session crash check must be done on Fedora. These source checks cannot guarantee GUI or build correctness.
- Expanded members are selectable for details but move as a unit with their container (drag its header); per-child independent layout within a group is deferred.

## Suggested UI test

1. Open Logic Flow for a project with named object arrays. Confirm `kim[]`, `Phreight[]` and `spikey[]` start collapsed.
2. Click `+` to expand `kim[]`; click different child cards and inspect the right pane.
3. Move the group by its header, collapse it again and verify its incoming/outgoing arrows follow.
4. Drag a rectangle over any two or more individual cards in one world; press Ctrl+G, give it a name, and confirm it collapses into a draggable group.
5. Close and reopen the editor. Confirm manual-group membership, positions and expansion state survive.
6. Click Clean Layout and Spread Left to Right. Confirm groups persist, then select a manual group and press Ctrl+Shift+G to ungroup.
7. Zoom, Fit Graph, switch worlds, Reload Saved Worlds, and close/reopen to check stability.
