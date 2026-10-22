# Stage 5.12: Remove Duplicate Root gameassets

## What changes

Game-generated `gameassets/gameassets.c` and `gameassets/gameassets.h` are
**world modules**. Their published versions under:

- `worlds/forest/gameassets/gameassets.c/.h`
- `worlds/world1/gameassets/gameassets.c/.h`

are the only ones the V1 world-manager build needs. The generator currently
emits files temporarily in project-root `gameassets/` so the existing
world-bundle publisher can snapshot them. **After successful publication**
of a world and its registry, Stage 5.12 deletes only root C/H files whose
bytes exactly match the published version of *some* valid world (after
removing the single added namespace include from world C). The folder is
removed only when empty. Unrelated files and independent edits are retained.

The IDE's next normal **Save Project** prunes missing root gameassets.c/.h
entries from `.proj`. It does not delete or rewrite the world copies or
resource files such as PPB/WAV/music. The existing compiler already
excluded root gameassets.c from linking, so this is primarily workspace
cleanup, **not necessarily a reduction in final .app size**.

## Regeneration behaviour

`SidboxGameDesigner::regenerateBuildFiles()` now reads the chosen graphics
embedding mode from **the current world's private snapshot** first,
then its visible published source, and finally a legacy root output if one
exists. This avoids reverting to external PPB mode merely because the
root C file was removed.

The explicit **Generate V1 Game Code** replace warning now checks the
current world's published gameassets C/H instead of project-root staging.

## Updated IDE source files

- `gameworldsnapshot.h`: cleanup after successful publication, with safety
  checks and empty-folder removal.
- `mainwindow.cpp`: remove obsolete, missing root C/H project entries.
- `gamedesigner_export.cpp`: per-world embed-mode detection and regeneration
  warning; updated user message.

No SIDBOX runtime helpers, C namespace rules, compiler flags or resource
formats have changed.

## Test on the IDE and SIDBOX

1. Replace the three source files, rebuild CoderGirl.
2. Open the test project and use **Update Game Project** for both `forest`
   and `world1`.
3. Verify `worlds/forest/gameassets/` and `worlds/world1/gameassets/` retain
   their separate `gameassets.c/.h`. The root `gameassets/` generated C/H
   should disappear, and the folder itself disappears if empty.
4. Save and reopen the `.proj`; ensure it doesn't restore old root entries.
5. Build and run on SIDBOX; verify sprites, tile atlases, world switching,
   and graphics as normal.
6. Optional: generate with **Embed sprite and selected tile-atlas PPBs**;
   after a later F5 auto-regeneration, check the embedded-pixel marker stays
   present in the current world's generated C (and no root duplicate stays).

## Validation performed

- Stage 5.11 source and fixture checks still pass.
- Stage 5.12 fixture uses the uploaded Platformer3Testing Forest/World1 files.
  The actual project root `gameassets.c/.h` matches World1's generated files,
  after subtracting the C namespace include. Both published world outputs
  remain, and independent user edits and unrelated files are preserved.
- Static checks confirm that `.proj` pruning, per-world embed-mode selection,
  and existing global stamps/world helper code remain present.
- Qt6 IDE compilation and real hardware are **not** verified here.

Note: temporary `gameassets.c/.h` may be created while generating. Their
absence is expected **after successful world publication**, not mid-export.
