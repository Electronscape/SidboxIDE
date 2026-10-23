# Stage 5.44 (23 October 2026): Game Resources A-Z

Scope: **Game Resources tree only**. No asset IDs, runtime drawing, saved project
resource order, game code generation or PPB data changes.

## User-facing change

The top-level categories remain in precisely this fixed order:

1. Player Starts
2. Sprites
3. Tile Atlases
4. Backgrounds
5. Palettes
6. Sounds
7. Music
8. Game Objects
9. Splines

Entries within each category are sorted by their displayed names, ascending.
The nested **Palettes** branches are also sorted, including the
Background/Foreground group names and the palette entries inside each group.
The required Default start remains available, but is sorted alongside named
entrances.

The same underlying sprite still appears under Sprites and (when configured)
Game Objects, using the original resource index; only the display position
changes. When a sprite or object is renamed, the relevant entries are re-sorted
in place, without rebuilding the tree during typing. Group expansion and
selection restoration after normal refreshes continue to use the previous
ID/index and category.

## Files

- `gamedesigner.cpp`: explicitly disable entire-tree sorting, sort immediate
  children on tree rebuild and re-sort affected children after live renaming.
- `splashscreenwidget.cpp`: `Build: 5.44.231026`.
- `development/tests/test_stage544_resource_tree_sort.py`: source contracts.
- `development/tests/test_stage543_editor_contracts.py`: decouple historic
  feature regressions from the splash build number (now tested in Stage 5.44).

## Validation

- Stage 5.44 resource-tree source contracts: pass.
- Stage 5.43 inventory PPB / HUD and DROP native-C regression: pass.
- Stage 5.42 existing PPB stamping/inventory native-C test: pass.
- Stage 5.36 integrated source contracts: pass.
- Complete Qt6 GUI build and STM32 hardware test: not available here.
