# Stage 4.43 — Adventure Story Rules

This source tree is derived from **Stage 4.42b**, based on the user's **21 Oct 2026 11:08** known-good snapshot.

**New story rules:** `idelibs/codehelpers/game/gameadventure.rulec` and `gameadventure.ruleh`.

They render, via `gameadventuregen.cpp` + strict `gamehelpertemplates.h`, to the project's normal `gamehelpers/gameadventure.c/.h`. Stage 4.42b's `adventureruntime.rulec/.ruleh` are unchanged.

See `Stage4.43-Adventure-Story-Rules-Guide.md` for marker contracts, install and test instructions.

**No GUI-side changes, runtime ABI changes, or changes to user-owned `main.c`.**
