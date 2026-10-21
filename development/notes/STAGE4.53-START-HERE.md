# Stage 4.53 — World Name From .sbgm

Use the `.sbgm` filename as the exported world name instead of always forcing `level1`.

## Result
- `forest.sbgm` -> `gamelevels/forest.c`, `forest.h`, `forest.map`, `game_forest`
- `Cave 2.sbgm` -> `gamelevels/Cave_2.c`, `Cave_2.h`, `Cave_2.map`, `game_Cave_2`

If a valid name cannot be derived, the fallback remains `level1`.

## Updated
- `gametilemap.cpp/.h`
- `gamedesigner.cpp`
- `gamedesigner_export.cpp`
- `gamedesigner_project.cpp`
- `gamedesigner_update.cpp`
- `idelibs/codehelpers/game/worldmap.rulec`
- `idelibs/codehelpers/game/worldmap.ruleh`
- `idelibs/codehelpers/game/maingame.rulec`
- `idelibs/codehelpers/game/gameworlditems.rulec`

## Important
This changes exported tilemap file names and generated world symbols.
After installing:
1. Re-export the tilemap / run Update Game Project.
2. Update any hand-written `main.c` references from `level1` / `game_level1` to the new world name.
3. Rebuild the game.
