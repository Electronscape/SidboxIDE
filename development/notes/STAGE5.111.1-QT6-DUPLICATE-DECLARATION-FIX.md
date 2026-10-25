# Stage 5.111.1.251026: Qt6 duplicate declaration fix

Fixes repeated declarations of the seven player-spotlight animation fields in
`gamedesigner.h` (reported on Fedora at line 332 onward), plus a second
accidental duplicate `QStringList` declaration in `gameworldsnapshot.h`.
Also removes redundant spotlight animation field reads and writes in
`gamedesigner_project.cpp`.

## Installation
Apply the drop-in over the Stage 5.111 IDE source directory and rebuild.
No `main.c` changes, no firmware changes, and no game regeneration are needed.
The cached BOB renderer and spotlight engine templates are deliberately untouched.

## Verification
Source-level uniqueness checks and native GCC spotlight regression tests can
run without Qt6; the full IDE must still be compiled on your Fedora machine.
