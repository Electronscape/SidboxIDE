# Stage 5.9: remove duplicate project-root gamelevels generation

**Starting point:** Stage 5.8, with corrected `gamedesigner.cpp` (`#include "gameglobalstamps.h"`).

## New output layout

- **Published compiler source:** `worlds/<world>/gamelevels/<world>.c` and `<world>.h`
- **External TFCard map (if enabled):** `worlds/<world>/gamelevels/<world>.map`
- **Private archive:** `.codergirl/worlds/<world>/gamelevels/...` (IDE snapshot, excluded from compiling)
- **Private staging while exporting:** `.codergirl/tilemap-staging/<world>/gamelevels/...` (removed after successful publication)
- **Global collision and loop stamp runtime:** `gamehelpers/gameglobalstamps.c` (unchanged)
- **Project-root `gamelevels/`:** NOT produced by normal Game Project export; old generated duplicates are deleted after a successful world publication.

The project-root `gamelevels/` directory is removed if it becomes empty. User-owned / unrecognised files are never deleted automatically. Stale root `.c` files are excluded from V1 Game compiles even if not removable. Obsolete missing root file references are pruned from `.proj` on its next save.

**External map path:** The game still requests `gamelevels/<world>.map` on the **TFCard**. Copy the file from `worlds/<world>/gamelevels/<world>.map` to the matching TFCard path. The TFCard runtime path is not the project output folder.

## Relevant source changes

- `gametilemap.h/.cpp`: optional generated-map output root; still resolve atlas/physics helper against project root.
- `gamedesigner.cpp`: stage map in `.codergirl`; missing-world prompt now invokes full publication rather than only staging.
- `gamedesigner_project.cpp`: detect previous published map instead of obsolete root map.
- `gamedesigner_export.cpp`: always regenerate current world map immediately before publishing, preventing stale staging.
- `gameworldsnapshot.h`: copy staged map into world archive, publish namespaced module, remove staging, clean recognised obsolete root files.
- `gamedesigner_update.cpp`: back up old root map exports before replacement/cleanup; no new root map outputs.
- `mainwindow.cpp`: never include Game Project root-level gamelevels C in V1 compiler inputs; prune missing old entries from saved project manifest.
- `idelibs/codehelpers/game/tilemap.txt`: explains the new output folder, while identifying older single-world snippets as historical.

## Test

1. Back up game project; rebuild IDE with Stage 5.9 source.
2. Open Forest, run Update Game Project. Check `worlds/forest/gamelevels/forest.c/.h` exist and `gamelevels/forest.c/.h` do not.
3. Open World 1, Update Game Project. Check `worlds/world1/gamelevels/world1.c/.h` exist and `gamelevels/world1.c/.h` do not.
4. If the legacy project-root `gamelevels/` directory contains an unrelated file such as `level1.map`, it is intentionally retained. You can manually remove that unused file once you verify it is not needed.
5. Compile and run the game on real SIDBOX. Confirm worlds and slope/loop collisions still work.
6. Check `buildv1/` compiler inputs / build log contain `worlds/<world>/gamelevels/<world>.c` but not project-root `gamelevels/<world>.c`.
7. Save the `.proj` file again and check it no longer lists deleted project-root C/H files.

## Verification available here

Source-level regression and representative host C world-link tests pass. Actual Qt6 GUI compile and SIDBOX test were not possible here; hardware validation remains pending.

**Binary-size note:** Previously the compiler already skipped most root duplicates whenever a published world copy existed. Removing them saves disk/project clutter and eliminates a fallback that could accidentally compile a root map. It does **not** guarantee the final `.app` shrinks.
