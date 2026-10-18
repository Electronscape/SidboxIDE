# CoderGirl / GamerGirl Stage 3.70 — Refactor Pass 2

**Baseline:** Stage 3.69 (the version reported working on 18 October 2026).

## Scope

This is the second **behaviour-preserving source-layout pass**, concentrating on `mainwindow.cpp`. It deliberately does **not** change game physics, player animation, runtime helpers, GUI Designer, Tilemap Editor, project formats, or old `.map` / `.sbgm` compatibility. Those format changes are deferred until a separate intentional breaking release-format revision.

49 existing `MainWindow` method definitions were moved *without editing their function bodies* from `mainwindow.cpp` to seven new C++ translation units:

| New IDE source file | Functions moved | Responsibility |
|---|---:|---|
| `mainwindow_projectexplorer.cpp` | 11 | Create, remove, rename and move files and folders in the project explorer |
| `mainwindow_editorview.cpp` | 12 | Active editor and split-view UI, tab selection and cursor-position presentation |
| `mainwindow_filewatch.cpp` | 4 | File watchers, external-edit detection and reload while preserving cursor/scroll |
| `mainwindow_findreplace.cpp` | 2 | Find/Replace dialog and current-word lookup |
| `mainwindow_paths.cpp` | 9 | Project-relative file paths, compiler/objcopy locations and library enumeration |
| `mainwindow_output.cpp` | 8 | Build progress, compiler diagnostics display, output text formatting |
| `mainwindow_preferences.cpp` | 3 | Editor font and theme-setting persistence |

The existing `editorTabIconForFile()` body is now in `mainwindow_uiicons.cpp`, with its declaration in `mainwindow_uiicons.h`, so the main editor and split editor can call the exact same mapping across translation units. `CMakeLists.txt` compiles all eight new `.cpp` files and registers the `.h`.

**Remaining large areas:** `mainwindow.cpp` still contains compiler orchestration, source indexing/analysis, home page and major UI setup. `guidesigner.cpp` remains its own large file and will need a carefully staged refactor with a real Qt build gate; we didn't move its internal anonymous-namespace types blindly. This is **not** a full-IDE overhaul.

## Install (full source archive)

1. Make a backup of your last working Stage 3.69 tree.
2. Extract the **full** Stage 3.70 archive as your IDE source tree.
3. In Qt Creator open `CMakeLists.txt` and run **Build > Run CMake** / Reconfigure to pick up the new `.cpp` files.
4. Rebuild `SidboxIDE`. If it reports a compile error, keep the exact file and line so we can fix the real issue rather than guessing.

## Install (changed-files archive)

Extract the changed-files archive over the exact Stage 3.69 source tree, preserving paths. In particular keep the new files **beside** `mainwindow.cpp` in the IDE source root. Reconfigure CMake and rebuild. Do not copy only the old `mainwindow.cpp` or you will get undefined symbols at link time.

**No** need to regenerate your V1 game, maps or animations. `idelibs/codehelpers/game` is untouched.

## Verified without Qt

- All 49 moved method bodies have **identical SHA-256 hashes** to their Stage 3.69 implementations. The file-icon mapping body is identical apart from its default parameter moving into the declaration.
- New methods appear in exactly one `.cpp`, and every new file is listed in CMake: `python development/tests/test_stage370_refactor_layout.py`.
- Stage 3.69 layout and Stage 3.62 / 3.64 / 3.65 / 3.68 animation and generated-hitbox tests passed.
- Stage 3.60 / 3.61 / 3.63 / 3.65 / 3.66 / 3.67 / 3.68 player-hitbox C regression binaries passed, including the real 32px player across adjacent 16px slopes.
- All 29 `idelibs/codehelpers/game` files, and `guidesigner.cpp`, `gamedesigner*.cpp`, `gametilemap*.cpp`, and `gameanimationeditor.cpp` match Stage 3.69 byte-for-byte.
- The main IDE's **2048 KiB** syntax-highlight/source-size threshold is preserved.

**Outstanding:** The Qt6 IDE has **not** been compiled or clicked through in this environment. CMake configuration stops on missing Qt6 development files (`Qt6Config.cmake`). The full Qt Creator build on Fedora is the first integration gate. The world-object test harness also expects generated `gameanimation.h` and `gamespline.h` headers that are not present in the raw IDE source checkout; those world-object sources were not changed.

## Suggested smoke tests after Qt Creator build

1. Open/close a project and create, rename and move a project file in its tree.
2. Split an editor tab, switch between sides, close the split; check file icon and cursor display.
3. Externally modify a **saved** source file; verify the reload/unsaved-changes prompt and cursor position.
4. Find/Replace in the current file and across the project.
5. Compile a V1 game and a V2 applet; inspect compiler output and clickable diagnostic markers.
6. Change an editor font/theme setting, restart and check it persists.
7. Open the existing platformer, confirm Stage 3.67 slippery slopes and Stage 3.68 custom hitboxes still behave on SIDBOX.

Keep the last working Stage 3.69 backup until these tests pass.
