# Stage 3.97 — Reward launch, hidden collectables and PPB double-open fix

## Installation

Replace these files in your IDE source root with the same relative paths:
- `gamedesigner.h`
- `gamedesigner.cpp`
- `gamedesigner_project.cpp`
- `gamedesigner_export.cpp`
- `mainwindow.cpp`

Rebuild the Qt6 IDE. Edit your Breakable properties to select a reward, optionally tick **Launch reward when block breaks**, and adjust the signed X/Y momentum. Collectables now show **Hidden until activated / spawned**. Save the design, then use **F5 → Update and Compile** to regenerate the runtime C code. No direct edits to your existing `main.c` are necessary.

Full rationale, behavior and test coverage: `development/notes/STAGE3.97-REWARD-IMPULSE-HIDDEN-PPB.md`.

Qt6 GUI and SIDBOX hardware are still to be tested locally. All dedicated source/native-C tests passed here.
