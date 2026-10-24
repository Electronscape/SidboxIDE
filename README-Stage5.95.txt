CoderGirl Stage 5.95 - Trigger Dialogue Folder-Tree Picker
Build: 5.95.241026
Base: Stage 5.94.1 (includes gamefloweditor.cpp compile correction)

Install this drop-in over the existing CoderGirl IDE SOURCE root:
  gameadventureeditor.cpp
  gameadventureeditor.h
  gamedesigner.cpp
  splashscreenwidget.cpp

Rebuild the Qt6 IDE. You do NOT need to run Update Game Project or
recompile the game for this UI-only improvement.

To test:
  1. Open a saved game world with Adventure dialogue nodes.
  2. Right-click a Trigger Game Object -> Configure Game Object.
  3. Under Switch & Trigger, open "On success: dialogue".
  4. Check the same searchable, nested folder tree used by the
     Adventure Editor (e.g., Forest > Big Steve > Intro).
  5. Select a dialogue, save, reopen properties and verify selection.
  6. Confirm "None (no dialogue)" still works.
  7. Check a saved invalid node index: "Missing dialogue node N" remains
     visible rather than silently selecting a different node.

Implementation:
  Reuses the existing DialogueTreeCombo from gameadventureeditor.cpp
  through a small public factory, with the unchanged numeric dialogue IDs.
  Both dialogue-node and folder JSON arrays outlive the properties dialog.
  No generator, runtime, game files or user-owned main.c were modified.

Verification:
  Static/source checks and actual Forest/World1 folder-data checks passed.
  Qt6 compilation and visual interaction still need testing on Fedora.
