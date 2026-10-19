# CoderGirl / GamerGirl Stage 3.69 — IDE refactor, first pass

**Source:** user archive `IDE - 18-10-2026-1652.tar.gz` (18 October 2026, 16:52).

## Purpose

This is **the first verified source-organization pass, not a claim that the entire IDE is refactored**. The IDE has grown large enough that one giant uncompiled rewrite would be needlessly risky. The immediate priority is preserving the user's currently working SIDBOX V1 game, especially passive slippery collision stamps, connected slopes, 64px artwork / independent hitboxes, player animations, and springs.

### Modified/new Qt IDE files

| File | Responsibility |
|---|---|
| `gamedesigner.cpp` (modified) | The existing editor, resource UI and editing workflows |
| `gamedesigner_export.cpp` (new) | V1 helpers, world-object export, starter `main.c` generation, and game-code generation |
| `gamedesigner_project.cpp` (new) | `.sbgm` JSON project load/save |
| `gamedesigner_update.cpp` (new) | Update Game Project, ZIP backups, rollback and preservation of programmer-owned `main.c` |
| `gamedesigner_limits.h` (new) | Shared LCD dimensions and editor-coordinate bound |
| `gametilemap.cpp` (modified) | Tilemap editor UI, canvas, brushes, Bezier and loop controls, level export |
| `gametilemapmodel.cpp` (new) | Tilemap data resize, stamp data resize, JSON read/write |
| `gametilemapinternal.h` (new) | Shared slope-point validation needed by the UI export and model import |
| `CMakeLists.txt` (modified) | Compiles the new translation units |
| `development/tests/stage364_main_animation_integration_test.py` | Finds generated starter C in new export source |
| `development/tests/test_stage365_animation_autosave.py` | Scans both UI and export files |
| `development/tests/test_stage368_generated_hitbox.py` | Finds generated hitbox setup in new export source |
| `development/tests/test_stage369_refactor_layout.py` (new) | Verifies single definitions and build file registration |

The large method bodies were **moved without altering their implementations**. ZIP backup helpers moved alongside the Update Game Project method. Common editor coordinate limits are defined once. No `.map` or `.sbgm` format changes.

### Installation

**Full archive:** Back up your current IDE source. Extract the full source archive and reopen `CMakeLists.txt` as the Qt Creator project. Use **Build > Run CMake** (or reconfigure the project) so the newly added `.cpp` files are included, then rebuild `SidboxIDE`.

**Changed-files archive:** Extract over the corresponding files of your exact 16:52 IDE, keeping the new `.cpp`/`.h` filenames in the **IDE source root** beside `gamedesigner.cpp`. Reconfigure CMake and rebuild. Do **not** only replace `gamedesigner.cpp` and `gametilemap.cpp` or you'll get undefined symbols at link time.

No update of your V1 game or map data is required for Stage 3.69; the `idelibs/codehelpers` production sources were not changed.

### Verification completed

- Existing C physics tests: Stage 3.60, 3.61, 3.63, 3.65, 3.66, 3.67 and Stage 3.68 player-hitbox/world-objects pass.
- Stage 3.62 C animation playback and Stage 3.64/3.65/3.68 generated-animation checks pass, with source-location checks updated for new files.
- All 14 production `.c`/`.h` codehelper files match the uploaded archive byte-for-byte.
- Stage 3.69 structural sanity test passes (new files registered; no duplicated definitions).
- Qt IDE build **not tested** in this environment. CMake configure stops because Qt6 SDK / `Qt6Config.cmake` is absent. The first Qt Creator build on Fedora is therefore the integration gate.

### Suggested smoke checks after building the IDE

1. Open the same V1 project; inspect and save its `.sbgm`, then reopen it.
2. Edit a tilemap and save (including a slippery collision stamp and a loop track), then reopen and confirm settings.
3. **Update Game Project**: verify its ZIP backup and that programmer-owned `main.c` is not overwritten.
4. Save Player Animations and confirm the optional `gameanimations/player_anim.h` update prompt.
5. Export V1 code and recompile the game. Check 2% damping over adjacent slopes, 64px sprite with smaller hitbox, springs and animated frames on actual SIDBOX.

### Next refactoring passes (NOT included yet)

- **Main Window** (~17,200 lines): separate project lifecycle, compiler output, editor history/recovery, file tree, toolchain management, and UI wiring. Requires a live Qt6 build after each extraction.
- **GUI Designer** (~14,100 lines): separate schema and serialization, palettes/graphics, canvas interaction, gadget property UI and code generation. Preserve sharp/square-corner styling.
- **Remaining Game Designer & Tilemap UI**: split resource/canvas/controller code from generators and export, with dedicated Qt regression coverage for `.sbgm` and `.map` round trips.
- **Runtime and toolchains**: isolate formatting/IO, tests, and any obsolete V1/V2 coupling only after verifying toolchain artifacts on SIDBOX. Keep V1 working and do not silently migrate game projects.
- **Intentional breaking-format cleanup**, later: remove old `.map` and `.sbgm` compatibility only **after** choosing a final released format and ensuring no existing private projects need migration. This pass deliberately preserves old loaders and writers.

Avoid any promise of 'full IDE refactor complete' until those areas pass real Qt Creator builds and on-device regression tests.
