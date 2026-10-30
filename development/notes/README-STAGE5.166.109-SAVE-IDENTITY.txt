SIDBOX CoderGirl IDE - Stage 5.166.109.291026
Save-game identity & compatibility protection
==========================================

Changes
-------
- The compiled multi-world registry now carries a 64-bit, SHA-256-derived
  save-layout identity that includes the ordered, immutable Game Object UUIDs
  for BOTH serialized arrays: Collectables and other World Objects.
- The frozen per-world identity is recorded during each world publication in
  .codergirl/worlds/<world>/world.json. It is NOT recalculated from subsequently
  edited .sbgm files while building the registry.
- Adventure NPC order, dialogue node order/contents, inventory-item indices,
  pickup kinds and world order are also represented by the identity.
- Project Quest and Objective stable IDs, order, type and targets contribute.
- Save header version is now 3 and includes this identity. Header identity,
  world names, serialized blob lengths and checksum must all match on load.
- Saves with no identity proof (version 1/2) or a mismatching identity are
  refused before any world object data is imported. No best-effort remapping.
- The existing dual-bank alternating save files, payload checksum, project
  namespace, max size, and legacy-path read logic remain in place. They only
  load version 3 files with the proper identity.
- Splash screen build bumped to 5.166.109.291026.

IMPORTANT: one-time world publication upgrade
--------------------------------------------
Before building a game with this version of CoderGirl:
1. BACK UP YOUR GAME PROJECT and old .SAV files if you need them later.
2. Open each previously published .sbgm world and choose Generate Game Code
   (or trigger the normal rebuild for each world). Every published world must
   acquire a frozen saveLayoutDigest in its published world.json.
3. On the first world, the shared registry may report that another world was
   published before the save-identity update. The world already opened is
   published; continue exporting the other named .sbgm worlds. Re-export the
   first world or rebuild when all worlds have been upgraded.
4. Build and start a NEW GAME, and create fresh save slots. Older version-1/2
   saves CANNOT automatically load. They are not deleted by validation, but
   saving over the SAME slot can overwrite their bank files.
5. Do not reuse old saves after rearranging, deleting or replacing generated
   game objects. An index-compatible but identity-mismatching save is rejected.

Intentionally conservative
-------------------------
- Editing an Adventure dialogue node can invalidate old save slots because
  legacy dialogue progress is indexed and dialogue nodes lack durable UUIDs.
- A new game save is required after incompatible layout edits; no automatic
  conversion of old state to the new object's identity is attempted.
- Changing presentation-only resources (unrelated palette/graphics) does not
  itself change the world-object identity list.

Tests
-----
- development/tests/test_stage5166_109_save_identity.py compiles the actual
  generated world registry on native GCC with a TFCard mock and checks:
  matching-v3 save loads, different layout is refused, first-bank mismatch
  falls back to second bank, both mismatching banks fail, and old v2 fails.
- Stage 5.166.107/108 enemy visual-node tests and native save/quest tests
  were re-run against the updated rule source.
- Full Qt IDE build and real STM32H743/TFCard tests remain to be done on Fedora.

Source files modified
---------------------
- gameworldsnapshot.h
- idelibs/codehelpers/game/gameworlds.rulec
- splashscreenwidget.cpp
- development/tests/*.py / test_stage5165_quest_runtime.c (fixtures updated)
