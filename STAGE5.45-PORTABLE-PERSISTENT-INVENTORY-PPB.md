# Stage 5.45.231026 | Portable persistent inventory PPB artwork

## What was wrong

`SidboxGameDesigner::persistentItemsFromSavedWorlds()` already appended persistent
inventory definitions from other saved `.sbgm` worlds, preserving the item name
and pickup kind. It ALSO intentionally cleared the original `iconAtlasId`,
`icon`, `icon2x2` and `iconCells` fields. This made an inventory item from World1
appear as a fallback white square in Forest, even though the source collectable
had a valid PPB. Manually registering a copy of its PPB in each world should
never be necessary.

## Behaviour now

- Persistent collectables retain their selected cell IDs and 2x2 stamp layout.
- The exporter resolves the source world's local atlas UUID to a **project-relative
  PPB file path**, so foreign worlds never depend on source-world resource IDs.
- If the inventory item has no custom atlas, its source world's dialogue PPB
  is used. If neither is configured, the source collectable's original PPB,
  sprite frame and cell size are the default icon.
- Generated `gameadventure.c` checks `gameassets_find_ppb()` for an existing
  matching loaded bitmap before requesting a separate portable load.
- Portable PPBs are read from their original TFCard path when quantity becomes
  nonzero, after validating the complete header, dimensions and byte length.
- Multiple item icons sharing one PPB use one allocation, with no new PPB
  export, new file naming, or copies in world folders.
- The portable buffers are freed on world change. Only current-world scenery
  and currently owned inventory icons consume bitmap RAM.
- Missing/mismatched TFCard PPBs keep the visible fallback square rather than
  silently drawing from the wrong dialogue atlas.
- Persistent item identity, player inventory counts, named pickup kinds,
  local dialogue choice indices, HUD counts and world drop state retain their
  existing runtime logic.

## Installation and regeneration

Apply Stage 5.45 over **Stage 5.44.1** (or use the complete source archive).
Rebuild the IDE. Open each saved world and run **Update Game Project** to
regenerate current helpers and namespaced world bundles. Rebuild the game.
The original source PPBs still need to be present on the TFCard at the project's
normal paths (e.g., `graphics/pickups.ppb`). You no longer need to register them
in every destination world's Game Resources tree.

## Verification

Native C host tests passed: Stage 5.42 stamps and atlas selection, Stage 5.43
DROP and HUD contracts, Stage 5.44.1 collision guard, Stage 5.41 cross-world
inventory/HUD persistence, and new Stage 5.45 lazy-read/deduplication/icon
drawing test. Full Qt6 IDE compilation and real STM32H743 SIDBOX rendering
remain unverified here.
