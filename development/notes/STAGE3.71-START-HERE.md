# CoderGirl / GamerGirl Stage 3.71 — Refactor Pass 3 (GUI Designer)

**Baseline:** Stage 3.70, reported working on the user's Fedora Qt6 IDE.

## What changed

Refactored the 14,064-line `guidesigner.cpp` by moving code into focused internal sections while preserving the existing logic, interfaces, saved `.sbui` files, generated applets, palette data, gadget drawing, and square-corner styling. `guidesigner.cpp` is now ~8,671 lines.

| File | Role |
|---|---|
| `guidesigner_detail.h` | Internal Gadget/Window/Menu model types and declarations for shared preview functions |
| `guidesigner_graphics.cpp` | **Separate C++ compilation unit:** exact SIDBOX 256-colour CLUT, 8x16 preview font, PNG-to-CLUT converter, gadget/window drawing primitives, safe C text/identifier formatting |
| `guidesigner_palette_widgets.inc` | Designer toolbox, gadget drag source, menu editor and menu preview widgets |
| `guidesigner_canvas.inc` | Canvas rendering, hit testing, selection, drag/resize, keyboard/mouse interactions |
| `guidesigner_propertygrid.inc` | Compact sharp-cornered designer properties layout |
| `guidesigner.cpp` | The principal designer controller: `.sbui` save/load, gadget property bindings, code generation, undo and IDE integration |

**Note:** The three `.inc` files contain the intact inline class implementations. They are deliberately included once from `guidesigner.cpp`, *inside the shared internal namespace*. They are **not** independent C++ compilation units, and their class implementations have not yet been split method-by-method. `guidesigner_graphics.cpp` *is* a new, independently compiled `.cpp` module. This is the conservative first pass over the unusually tightly coupled GUI Designer, not a complete design rewrite.

The internal model/rendering symbols formerly had anonymous-namespace linkage. `GuiDesignerDetail` now provides the shared internal declarations needed by the separate graphics `.cpp`. The original ARGB CLUT is exposed as a read-only array so palette previews and generated source keep the same colours. The GUI Designer public API (`guidesigner.h`) is **unchanged**.

### Intentionally unchanged

- Main Window and Game Designer behaviour from Stages 3.69/3.70
- `idelibs/codehelpers/game` physics, springs, custom hitboxes, loops and animations
- `.sbui`, `.map`, `.sbgm` and all other saved/exported formats, including backward compatibility
- The 2048 KiB syntax-highlighting threshold
- All existing icon mappings, dialogs, menu bindings, and `border-radius: 0px` styling

## Installing

1. Keep a backup of your working **Stage 3.70** source directory.
2. Extract the **full Stage 3.71 IDE** archive, or extract the **changed files** archive over the Stage 3.70 source tree (preserve paths).
3. Open `CMakeLists.txt` in Qt Creator and **reconfigure CMake**. All five new support files must be present beside `guidesigner.cpp`.
4. Rebuild the IDE. If there is a Qt compiler or linker error, capture the **exact file, line and message** before making other changes.

There is **nothing to regenerate in your V1 game** for this refactor.

## Automated checks completed here

- `python development/tests/test_stage371_guidesigner_refactor.py` — PASS. Checks the relocation SHA-256 manifests against the original Stage 3.70 source text (no function-body rewrites), ensures CMake registrations and unique classes.
- `python development/tests/test_stage369_refactor_layout.py` — PASS.
- `python development/tests/test_stage370_refactor_layout.py` — PASS.
- Generated animation, animation autosave, hitbox setup and animation C tests — PASS.
- Nine C physics/world-object tests — PASS, including the real 16px slope-stamp/32px feet handoff, 32/48/64px hitboxes, springs and platforms. World-object test compiled using temporary test-only aliases for the headers renamed by game-helper installation.
- Byte comparison to Stage 3.70 shows **only** GUI Designer/CMake files and new tests changed. All runtime game helpers are identical to the tested Stage 3.70 source.

**Outstanding:** Qt6 is not installed in this environment. CMake stops at `find_package(Qt6 6.5 ...)`, so **no Qt GUI compilation or on-screen check has happened here**. Qt Creator on the user's Fedora machine is the required build gate. Do not treat the static checks as proof the IDE will build.

## Suggested Qt smoke tests

1. Open an existing `.sbui` and create/save a new one.
2. Add each basic gadget; use toolbox drag/drop, snap, resize, multi-select, Undo/Redo.
3. Edit Gadget properties (particularly Messenger, Timer, Media, BitmapView, ListBox, TabGroup).
4. Use the menu editor to reorder and preview menu items.
5. Import a PNG into BitmapView; compare its CLUT colours on preview to before.
6. Generate a V2 applet and compile it; inspect `.c`, `.h` and resource files.
7. Reopen a saved design, regenerate it and compare the generated files where appropriate.
8. Confirm Stage 3.70 IDE project navigation and your already-working V1 game remain unchanged.

**Potential next GUI Designer refactor pass:** split the controller class's serialization and C generator methods into true `.cpp` compilation units, but only after this mechanical split has built and passed GUI smoke tests on Fedora.
