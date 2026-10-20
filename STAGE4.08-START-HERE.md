# GamerGirl Stage 4.08 — Quiet Compile Update

Changes since Stage 4.07:
- F5 Update and Compile no longer opens the nested Update Project confirmation
  or the success popup; the existing remembered session decision still applies.
- Explicit Game Resources > Update Project... retains its confirmation, embed
  option and success popup.
- ZIP backup, error reporting, rollback and protected main.c are unchanged.

Modified IDE source: mainwindow.cpp, gamedesigner.h, gamedesigner_update.cpp.
See Stage4.08-Quiet-Compile-Update-README.md for installation and testing.
