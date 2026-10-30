SIDBOX IDE Stage 5.166.118.3.301026

COLLECTABLE LOGIC GRAPH PERSISTENCE HOTFIX

Bug: An independent AND/OR/NOT/BOOLEAN gate created from a Collectable's
ON PICKUP output appeared in Visual Nodes and could be saved without error,
but disappeared on reopening or after the normal Game World save/refresh.

Cause: Three stale explicit exclusions of Collectable-owned logicNodes:
  1. gamevisualnodes.cpp / VisualNodesDialog world-resource load
  2. gamevisualnodes.cpp / VisualNodesDialog::saveAll()
  3. gamedesigner_project.cpp / ordinary .sbgm project serialization

Fix: Preserve collectable-owned logicNodes during all three paths.
No changes to logic format, runtime evaluation, event pulse handling, or
save-game payload. Previous Stage 118.2 Trigger label fix is retained.

Important: Any graph discarded by an earlier save is NOT recoverable from
.vsgm alone; it stores layout, not gameplay rules. Recreate that graph once
(unless you have an .sbgm.vsgm-backup from before it was lost).

Acceptance:
  1. Create kim[2] ON PICKUP -> AND + stopLift STATE ON -> dialogue.
  2. Save Graph + World, close, reopen; verify all nodes and wires are present.
  3. Save the ordinary Game World, close, reopen; verify again.
  4. Export, compile, and test the pickup event on hardware.

Full Qt build and actual hardware execution remain unverified here.
