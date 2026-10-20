# GamerGirl Stage 4.08 — Quiet Update Project during Compile (F5)

Base: GamerGirl Stage 4.07 source, including the Tilemap Editor player reference.

## Behaviour

### Compile / F5
- The existing first-build/changed-resources question remains available. You may check
  "Remember my choice for this project session" to stop asking for this session.
- "Update and Compile" now calls the full Update Project operation WITHOUT its
  second "Update Game Project — Confirm" dialog or its "Game Project Updated" popup.
- Subsequent F5 updates are automatic and quiet after the remembered Update choice.
- A remembered "Compile Without Updating" choice continues to skip updates as before.
- Updates still create their ZIP backup, refresh helpers, export resources,
  generate code and protect user-owned main.c exactly as before.
- Errors and update/rollback failures STILL show warnings and stop compilation.
- Compile-triggered updates use the regular external-PPB generation mode
  (embedded sprite pixels OFF, as with the prior unchecked option).

### Manual Game Resources > Update Project...
- ALWAYS presents the detailed confirmation, including the embed-PPB checkbox.
- ALWAYS presents the completion information after a successful update.
- The build reminder setting has no effect on manual updates.

## Installation

For the changed-files package, replace these three files at the root of the IDE source:
  mainwindow.cpp
  gamedesigner.h
  gamedesigner_update.cpp

Rebuild the Qt6 IDE. No SIDBOX firmware or game project format changes.

## Verification
- Existing Stage 3.79b and Stage 3.93–4.07 focused Python regression tests: PASS.
- New Stage 4.08 source regression test: PASS.
- A Qt6 native build / interactive confirmation still requires local Fedora testing:
  Qt6 >= 6.5 development files are unavailable in this test environment.

Suggested UI checks:
1. Open game project; F5; choose Update and Compile with Remember checked.
   Only the compile-choice dialog should appear, followed by the build — no update confirmation/completion popup.
2. Edit a game resource; F5 again: no reminder and no update confirmation/completion popup.
3. Click Update Project... in the Game Resources pane: confirm appears,
   and after a successful update the success notice appears.
4. Start a new IDE session: the first-build reminder should reappear.
5. Verify a new ZIP appears in .codergirl-backups/updates after each actual update.
