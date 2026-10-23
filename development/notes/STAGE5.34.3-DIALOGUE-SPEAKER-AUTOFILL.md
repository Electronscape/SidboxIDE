# Stage 5.34.3: New dialogue Speaker from NPC folder

## In the Adventure Editor
1. Create or select a top-level dialogue folder named after an NPC, such as `Village Elder`.
2. Press **+ Dialogue Node**. The node's Speaker starts as `Village Elder`.
3. If you create nested folders like `Village Elder / After Quest`, newly added nodes there also start as `Village Elder`.
4. Selecting an existing node and pressing **+ Dialogue Node** uses that node's folder's top-level NPC name.
5. In `Unfiled dialogues`, the default remains `NPC`.

The Speaker value is only copied once on node creation. Later renaming the folder does not silently alter previously written dialogue. You can always edit any node's Speaker by hand. Dialogue IDs, links and NPC bindings stay the same.

## Installation
Drop in `gameadventureeditor.cpp` and `splashscreenwidget.cpp` over the Stage 5.34.2 IDE source, or use the patch. Then rebuild the IDE. Game regeneration is not necessary.

## Testing
A source-level contract test checks the root-folder traversal, node selection, unfiled fallback, existing node creation and the splash version. Qt6 GUI and actual click-through require verification on Fedora.
