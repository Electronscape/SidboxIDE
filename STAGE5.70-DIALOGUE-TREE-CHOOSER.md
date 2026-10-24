# Stage 5.70.241026: Dialogue folder-tree chooser

## What changed

The Adventure Editor's dialogue-node drop-downs now open a genuine hierarchical
`QTreeWidget` popup instead of a flat `QComboBox` list. Existing nested folder
organization is read from `dialogueFolders` (`id`, `parentId`, `name`) and the
node's `folderId`. Folders can be expanded/collapsed, and typing in the search
box filters dialogue titles, speakers, and folder names. Select a leaf by click
or enter. Special options such as `Close conversation`, `Keep current NPC
dialogue`, and `Use normal opening dialogue` remain top-level entries.

Applied to:
- NPC Start node and After helped (optional)
- Dialogue choice Next and If missing required item
- GIVE exchange Wrong item -> dialogue
- GIVE repeated wrong item First / Second / Third / Fourth+ dialogue
- Completed NPC conversation next visit
- Dialogue Box Position preview node

The original *flat underlying QComboBox model* remains exactly as it was,
including integer `itemData` for every dialogue ID. Existing `findData`,
`currentData` and `currentIndexChanged` handlers remain fully compatible. No
changes to saved project JSON, gameplay/runtime or `main.c`. Moving a folder
does not change dialogue ID.

### Notes
- There is no new dependency or build-system entry. The custom subclass lives
  in `gameadventureeditor.cpp` and needs no Qt meta-object or moc changes.
- Empty folders are shown. Missing/cyclic parent references fall back to the
  root without altering saved metadata. Unfiled dialogues appear under an
  Unfiled dialogues branch.
- Only dialogue-target selectors change; inventory item selectors and event
  selectors remain unchanged.
- Qt6 graphical compilation/GUI interaction and real hardware testing remain
  to be done on user's Fedora machine. This is an IDE-only UI change and does
  not require an Update Game Project to use.

Build: 5.70.241026.
