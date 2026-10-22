# GamerGirl Stage 5.2c — F5 Builds All Published Worlds

Based on the **Stage 5.2** full IDE source. Compatible with the **Stage 5.2b** working, user-owned world-manager `main.c`.

## Fixed

- With a world-manager `main.c` (`/* GAMERGIRL_WORLD_MANAGER_MAIN */`), **F5 no longer shows “Choose Game Design”** when several `.sbgm` worlds exist.
- The IDE checks each design's own `worlds/<name>/world-build.json` and `.codergirl/worlds/<name>/world.json` against the design and referenced files. It detects missing or outdated published world files, rather than mistakenly treating the last-edited world as the only active output.
- **Update and Compile** regenerates all changed world designs, updating their buildable C sources and the shared `gameworlds` registry. On the first build after opening the project, the existing first-build confirmation may still offer a full update of all worlds.
- **Compile Without Updating** still leaves generated files untouched. The separate “Update Project?” safety prompt remains available according to Project Settings.
- Older `main.c` projects without the world-manager marker keep their **single-world selector** and active-world safety checks.
- No changes to V2 GUI Designer, rules, physical player, `.sbgm` format, or user-owned `main.c`.

## Install

Copy `mainwindow.cpp` and `mainwindow.h` into the IDE source root, replacing only those two IDE source files. The ZIP also contains two tests under `development/tests/`; copy them with the same directory layout if you keep the IDE test suite. Rebuild and restart the Qt IDE. Your already working Stage 5.2b `main.c` needs **no modifications**.

## Test

1. Reopen `platform3.proj` with `world1.sbgm` and `forest.sbgm` already generated.
2. Press **F5**. **No “Choose Game Design” popup** should appear. A separate first-build **Update Project?** confirmation can still appear; this is intentional. Choose **Update and Compile** for the initial test so both worlds are refreshed.
3. Verify both `worlds/world1` and `worlds/forest` modules are listed during compilation. Test the APP on SIDBOX.
4. Modify/save **forest.sbgm** and press F5. **Update and Compile** should regenerate forest while preserving world1's build bundle. A direct **Compile Without Updating** should compile current files without exporting worlds.
5. Repeat F5 with no changes: no world-choice popup; normally no update reminder once the session first-check is complete and world bundles are fresh.

## Notes

This fixes IDE pre-build world selection only. It does not add graphical transition/door controls, alter the default world started by `main.c`, or implement player rebinding in mapless worlds. Stage 5.2's runtime controller remains unchanged. V1 applet RAM limits still apply; your last linked build used 186/200 KB.

## Validation

Six regression checks passed: Stage 3.79 and 4.08 F5 safety, new Stage 5.2c all-world selection, Stage 5.1 GCC namespace/link, and two Stage 5.2 host-GCC world runtime tests. ZIP/tar integrity checks were also performed. Full Qt6 IDE build and ARM/SIDBOX hardware tests are not available in this environment.
