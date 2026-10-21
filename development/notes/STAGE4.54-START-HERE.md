# Stage 4.54 — Final V1 Embedded Resource + Adventure Rule Migration

Built from the **Stage 4.53b** IDE source that generated `world1` correctly.

## Actual changes

### Embedded PPB → C/H resources

- New SDK files: `idelibs/codehelpers/game/embeddedresource.rulec` and `embeddedresource.ruleh`.
- `SidboxPpb::exportC()` in `ppbcodec.cpp` now supplies **pixel rows, palette rows, dimensions, symbol, and filenames** to the two templates. It no longer writes C source statements itself.
- The standalone **Export Embedded V1 C Resource** button in `gamedesigner.cpp` passes the installed rules directory into `exportC()`.
- The generated file names, symbols, palette representation (`0xAARRGGBB`), 32-byte alignment, and row-major pixel ordering are unchanged.
- Both rules are validated/rendered before either output file is written; missing/invalid templates fail visibly.

### Adventure small remaining C statements

- `gameadventure.rulec` now has a repeatable `LINKED_ACTION` section. The IDE supplies only event IDs, object slot IDs, and requested action mode.
- The same rule contains the optional dialogue-skin PPB load call and conditional `gameworlditems.h` include.
- `gameadventuregen.cpp` validates the named section, selects conditional flags, and supplies validated project data. No `gameworlditems_set_active(...)` statement or `gameassets_find_ppb(...)` call is constructed in C++.
- Existing generated APIs and event ordering are retained.

### Helper menus

`embeddedresource.rulec/.ruleh` and `worldmap.rulec/.ruleh` are **generator-owned templates**, not drop-in runtime helpers. They're excluded from Add Helper Code and Update Game Project's helper discovery.

## Files modified

- `ppbcodec.cpp`
- `ppbcodec.h`
- `gamedesigner.cpp`
- `gamedesigner_update.cpp`
- `gameadventuregen.cpp`
- `idelibs/codehelpers/game/gameadventure.rulec`

## Files added

- `idelibs/codehelpers/game/embeddedresource.rulec`
- `idelibs/codehelpers/game/embeddedresource.ruleh`
- `development/tests/test_stage454_v1_rules.py`

No extra `.inc` files. V2 GUI generation and user-owned `main.c` are untouched.

## Static testing performed

`python3 development/tests/test_stage454_v1_rules.py`

This verifies PPB header/source byte-for-byte against the pre-migration layout for four sizes; compiles those four generated resources using GCC; renders and syntax-checks four Adventure combinations (with/without dialogue skin and linked object actions); verifies generator-owned rule wiring and strict markers.

**Qt6 IDE compilation and physical SIDBOX testing were not possible here.**

## Recommended hardware test

1. Back up the Stage 4.53b working IDE and game first.
2. Replace the changed files using the same directory layout, then rebuild the Qt IDE.
3. In Game Designer, test **Export Embedded V1 C Resource** on a small sprite. Check that the generated `.c/.h` compile and the palette remains unchanged.
4. Regenerate an adventure with a linked world-object dialogue choice, and a dialogue-skin atlas. Confirm generated `gamehelpers/gameadventure.c` compiles.
5. Generate the starter as usual, and test game launch on SIDBOX. Existing `world1` exports should remain unaffected.

The V1 template work addressed here does **not** implement multi-world loading, inventory persistence, or GUI Designer V2 rules.
