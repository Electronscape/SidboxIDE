# Stage 5.69.241026: NPC repeated wrong-item reactions

Use Adventure Editor > Dialogues & Choices > edit NPC answer > Configure GIVE inventory / AND-OR requirements.

Within the GIVE exchange dialog, **Repeated WRONG item (optional puzzle clue)** now supports one tracked item per dialogue answer, a first/second/third/fourth+ response dialogue node, and an optional once-only event on the third offer. A Game Object activation/deactivation/toggle can be selected for reveal actions, or a custom event ID for custom gameplay/Logic Flow integration.

Make the third dialogue node contain the clue, e.g. Future Kim squeals and reveals where the key is hidden. Nodes remain regular story dialogue nodes, no special text renderer changes. The chosen wrong item must not be one of the required exchange items.

**Behaviour**: wrong items are never consumed, first→second→third→fourth+ counts saturate, a third-offer action fires only once, and all unconfigured interactions use the existing wrong-item response unchanged. The repeated-item count is held in fixed world-local RAM and restored during existing world transitions via `gameadventure_save_progress()`/`gameadventure_restore_progress()` hooks. This is NOT yet on-TFCard save-game persistence. Existing `main.c` remains untouched. The generated `adventureruntime.c/.h` must be refreshed along with `gameadventure.c`, since this stage adds a small runtime API.

Safety: a missing dialogue ID falls back to the existing wrong-item dialogue. Deleting item or dialogue entries in the editor remaps or clears references. The same-node/item counter is shared by multiple NPCs only if you intentionally point them at the same dialogue answer. Each dialogue choice supports one special wrong item in this pass.

Build label: 5.69.241026. This release is source-level tested; SIDBOX hardware acceptance still needed.
