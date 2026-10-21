# Stage 4.53b — World Name Compiler Hotfix

Based on Stage 4.53, not an older build.

## Fixes

1. `gamedesigner_export.cpp` — in `SidboxGameDesigner::exportWorldItems(QString *error)`, derive `worldBase`, `worldSymbol` and `worldHeader` from the `.sbgm` filename. The World Items generator was using the latter two outside the scope where they had been declared for the Main Game generator, causing compiler errors around lines 913–914.
2. `idelibs/codehelpers/game/worldmap.ruleh` — make its include guard world-specific. The original fixed `SIDBOX_GAME_LEVEL1_H` guard would suppress later named-world headers when multiple worlds were included in the same C file.
3. `gametilemap.cpp` — supply `WORLD_HEADER_GUARD` to the `.ruleh` renderer. The existing `level1` world retains its original guard spelling for compatibility.

## Replace these files

- `gamedesigner_export.cpp`
- `gametilemap.cpp`
- `idelibs/codehelpers/game/worldmap.ruleh`

Do not replace any other files for this hotfix. `worldmap.rulec`, `maingame.rulec` and `gameworlditems.rulec` are unchanged.

## Testing performed

- Confirmed local variables exist in `exportWorldItems()` and both world-name fields are mapped.
- Rendered test headers for `level1`, `forest`, and `Cave_2`, and verified all three can be included in one C translation unit under `gcc -std=c11 -Wall -Wextra -Werror -fsyntax-only`.
- Qt IDE compilation and physical SIDBOX testing remain to be done on your machine.
