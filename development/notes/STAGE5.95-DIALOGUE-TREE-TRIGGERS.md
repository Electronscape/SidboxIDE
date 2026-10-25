# Stage 5.95 - Trigger dialogue selector

The `On success: dialogue` field in **Game Object Properties > Trigger / Switch** now uses the *same* searchable, nested folder-tree dropdown as the NPC dialogue fields in the Adventure Editor.

## Changes

- `gameadventureeditor.h`: public factory declaration for the existing `DialogueTreeCombo` widget.
- `gameadventureeditor.cpp`: factory implementation; no change to the existing tree widget behavior.
- `gamedesigner.cpp`: replace the flat Trigger dialogue dropdown; supply `nodes` and `dialogueFolders` from the active design and preserve `currentData()` numeric IDs.
- `splashscreenwidget.cpp`: build `5.95.241026`.

The Trigger's stored dialogue ID is unchanged; **None** remains `-1`, and invalid stored IDs remain visibly selectable for diagnosis. Search supports speaker/title, dialogue text and folder names. Folders stay nested exactly as saved by the Adventure Editor. The UI respects the IDE's existing square-corner convention.

No changes were made to engine/runtime, game generator, game resources, or `main.c`. No **Update Game Project** is required for this change.

## Checks

The source contract, ID preservation, factory signature and Stage 5.94.1 baseline were inspected. Both provided game worlds (`forest.sbgm` and `world1.sbgm`) have valid dialogue node and folder data. This environment does not have Qt6 development headers, so compiling and clicking through the UI on Fedora remains the acceptance test.
