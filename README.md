CoderGirl Qt6 IDE source, Stage 5.48 (23 October 2026).

Goto World now selects its destination Player Start's OUT effect for the
current world and IN effect for arrival. This fixes wrong effects on return
and repeat visits. Added per-start Circle centre: Screen centre (legacy) or
Door / Player Start, following camera offsets. No new PPB graphics.
See STAGE5.48-DOOR-TRANSITIONS-CIRCLE-ORIGINS.md. Native C transition tests
pass; Qt6 GUI build and SIDBOX Stage 5.48 hardware effects await testing.

---

CoderGirl Qt6 IDE source, Stage 5.47 (23 October 2026).

Shared HUD collectable artwork now follows the actual Inventory Items PPB and
cell/2x2 layout, or the Game Object sprite frame/stamp when no inventory art is
selected. The Editor list, placed preview, and generated C icon bytes agree;
placed counters are refreshed from saved worlds on regeneration. No new PPB
files, no palette index remapping. See STAGE5.47-HUD-ICON-ATLAS-CELLS.md.

Full Qt6 IDE compile and SIDBOX hardware verification remain pending.

---

CoderGirl Qt6 IDE source, Stage 5.46 (23 October 2026).

World transitions belong to each Player Start: independent IN and OUT modes,
including fade, directional wipe and circle mask, plus frame duration.
The generated world manager sequences exit, safe world load, and entrance
without loading two worlds or modifying PPB pixel indices. Player movement
pauses during transitions; music and rendering continue. Old user-owned
main.c continues instant-cut until it explicitly opts in.

See STAGE5.46-WORLD-TRANSITIONS.md for upgrade, implementation and hardware
caveats. Native C tests pass; full Qt6 IDE build and SIDBOX hardware
verification remain pending.

---

CoderGirl Qt6 IDE source, Stage 5.45 (23 October 2026).

Persistent Inventory PPBs are portable across worlds. Source-world icon atlas
references, 8x8 cell indices, and 2x2 stamp arrangements are preserved. The
runtime borrows a loaded PPB when possible; otherwise, it loads the ORIGINAL
TFCard PPB on demand when the item is owned, shares it between items, and frees
it on world travel. No atlas registration required in destination worlds.
Source PPBs still must exist once on the TFCard. See
STAGE5.45-PORTABLE-PERSISTENT-INVENTORY-PPB.md for test/upgrade details.

Native regression checks passed; Qt6 full build and physical SIDBOX verification
remain pending. Apply over Stage 5.44.1, Update Game Project in every world.

---

CoderGirl Qt6 IDE source, Stage 5.44.1 (23 October 2026).

Hotfix for C symbol collision when a graphics resource is named pickups[0],
platforms[0], etc. Internal managed runtime arrays now use namespaced symbols.
World generator templates and cross-object target expressions are updated.
Regenerate all worlds using Update Game Project after rebuilding the IDE.
No PPB assets, game design files, inventory identifiers, or palette indices change.

Native C regression: development/tests/test_stage5441_pickup_symbol_collision.py
Qt6 full IDE build and STM32 hardware run still require local verification.

CoderGirl Qt6 IDE source, Stage 5.44 (23 October 2026).

Game Resources keeps its nine top-level categories in the original fixed order,
but sorts entries A-Z within each category (including palette subgroups and
Game Object aliases). Names re-sort live when edited. See
STAGE5.44-GAME-RESOURCES-ALPHABETICAL.md.

This is a SOURCE bundle; any old SidboxIDE executable is excluded. Full Qt6
GUI compile and STM32 hardware testing remain pending.

---

CoderGirl Qt6 IDE source, Stage 5.43 (23 October 2026).

Fixes inventory icon PPB selection directly in the artwork dialog (used by
inventory and world DROP), preserves Game Objects tree selection on edits, and
removes HUD palette index remapping for tiles/icons. No extra PPB files.
See STAGE5.43-INVENTORY-PPB-TREE-HUD-INDICES.md.

This is a SOURCE bundle; any old SidboxIDE executable is deliberately excluded.
Full Qt6 GUI compile and STM32 hardware testing still required.

---

CoderGirl Qt6 IDE source, Stage 5.42.1 (23 October 2026).

Hotfix: capture `draftSpriteStamp` in the Game Object Properties preview lambda;
correct the Sprite Stamp in-dialog help to describe direct original-PPB
rendering; replace the Qt-deprecated HUD QImage::mirrored() call.
See STAGE5.42.1-COMPILE-HOTFIX.md.

This is a source package. Rebuild the IDE; any previously compiled SidboxIDE
executable is from an older stage and is deliberately excluded.

---

CoderGirl Qt6 IDE source, Stage 5.41.1 (23 October 2026).

Hotfix for Qt `QVariant::toInt(8)` compiler errors and HUD inventory balances.
See README-Stage5411.md.

---

CoderGirl Qt6 IDE source, Stage 5.41 (23 October 2026).

Newest changes: see README-Stage541.md. This release adds unified HUD palette colours, per-item inventory PPB atlas choices, opt-in collectible persistence with cross-world inventory definitions, array-aware object pasting and viewport-centred resource imports.

The original Stage 5.12 README is preserved below for historical context.

---

CoderGirl Qt6 IDE source, Stage 5.12 (22 October 2026).

Based on Stage 5.11, including Stage 5.10 persistent Tile Stamp fix,
Stage 5.8 compile corrections, multi-world global stamps and helpers.

Changes in Stage 5.12:
- Remove byte-identical generated root gameassets C/H after publishing.
- Keep world-specific gameassets C/H under worlds/<world>/gameassets/.
- Prune obsolete root asset source references when saving .proj.
- Preserve current world's embedded/external graphics mode across F5.
- Point explicit Generate V1 warning at the world-specific files.

Read STAGE5.12-REMOVE-DUPLICATE-GAMEASSETS.md for testing and details.
Qt6 compilation and SIDBOX hardware testing are pending.
