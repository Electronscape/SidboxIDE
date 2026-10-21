# GamerGirl Stage 4.31a — Fedora Qt6 build fix

This is a minimal patch on top of **Stage 4.31**. It only changes two C++ files at the root of the IDE source tree:

- `gameadventuregen.cpp`: uses `std::min<qsizetype>` and converts the bounded result to `int`, fixing the template deduction compilation error at the NPC animation frame counter.
- `gameadventureeditor.cpp`: replaces two deprecated `QImage::mirrored(bool,bool)` calls with `QImage::flipped(Qt::Orientations)` through a small helper, retaining independent X/Y atlas-cell mirroring.

## Install

1. Back up your working Stage 4.31 IDE source.
2. Extract the **Changed Files Only** archive into your IDE source folder (the folder containing `CMakeLists.txt` and `gameadventuregen.cpp`). Allow these two `.cpp` files to overwrite the existing ones.
3. Rebuild using your normal Fedora/CMake workflow.

No SIDBOX firmware, game project, `main.c`, runtime helpers, resources, or music playback code are changed.

## Verification

- Stage 4.31 generator/GUI/physics/music boundary checks passed.
- Stage 4.31 adventure C runtime test passed.
- Stage 4.30 adventure C runtime test passed.
- Standalone C++17 checked the corrected `std::min<qsizetype>` expression with `-Werror`.

**Qt6 IDE compilation was not performed here** because Qt development headers are unavailable in this environment. Please test the Fedora build and share any remaining diagnostics.
