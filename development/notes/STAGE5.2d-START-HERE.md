# Stage 5.2d — Retire single-world V1 game startup

**Base:** Stage 5.2c. This is a GamerGirl V1 Game-project change only. V2 CGARM GUI projects and the user-owned `main.c` are untouched.

## What changed

1. **F5 has exactly one game build mode.** All `.sbgm` designs are checked against their own `worlds/<name>/world-build.json` manifests; stale world bundles can be regenerated. The old “Choose Game Design” branch and old active/canonical-file timestamp path have gone.
2. **Only world-owned generated gameplay sources link.** The build excludes `gameassets/gameassets.c`, `gamehelpers/gameworlditems.c`, `gamehelpers/gameadventure.c`, and `gamehelpers/splinepaths.c` from the root source tree, regardless of any `GAMERGIRL_WORLD_MANAGER_MAIN` marker. `worlds/<name>/` and shared `gamehelpers/gameworlds.c` are the compiled path. Root `gamelevels/<name>.c` is skipped whenever its world-folder copy exists.
3. **Clear error for unmigrated `main.c`.** An old main, or a mixed old/new main, is blocked with instructions before compilation. It is never overwritten. The known working Stage 5.2b world-manager `main.c` satisfies this check; no edits required.
4. **Replaced the generated starter in `idelibs/codehelpers/game/maingame.rulec`.** `maingame.c.txt` now starts its selected world with `gameworlds_start("<name>")`, binds tile physics to `gameworlds_map()` and the namespaced `worlds/<name>` player sprite, calls `gameworlds_update/before/after/check/draw`, and exits via `gameworlds_shutdown()`. Optional Adventure and animation paths remain in the rule, using the shared Adventure runtime, not the old generated story module. `maingame.c.txt` remains per-design, describing the design currently being regenerated.
5. **Safe transition boundary.** The starter includes `gameworlds_apply_pending()` but intentionally **exits** after a successful switch to a *different* world until the user implements rebinding the destination's player sprite and physics. Actual door/spawn/player migration remains future work.
6. The generator's success text reflects the world-manager path. `2048 KB` syntax-highlighting threshold remains unchanged.

## Important: Why old root files remain on disk

The exporter currently **generates its raw files into the old root output directories before snapshotting and namespacing them** into `.codergirl/worlds/<name>/` and the real compiled `worlds/<name>/` folder. The root files are **staging inputs, NOT compiled game code and NOT a legacy loader**. This stage deliberately does *not* delete them: that would break Update Project. This is a controlled runtime retirement, not yet a refactor of the export staging implementation.

The shared `gamehelpers/gametilemap.c`, `gamehelpers/gameworldobjects.c`, `gamehelpers/gamecollectables.c`, `gamehelpers/gamespline.c`, `gamehelpers/gameadventureruntime.c` and similar generic helpers **are still required**.

## Test order

1. Back up the current IDE/project (you've already backed up earlier stages).
2. Install all six replacements, including `idelibs/codehelpers/game/maingame.rulec`.
3. Rebuild the IDE. Open `world1.sbgm` and use **Update Game Project** so `maingame.c.txt` is refreshed. Repeat for `forest` if stale.
4. Check `maingame.c.txt`: it must include `gamehelpers/gameworlds.h`, `worlds/<name>/world_api.h`, and `gameworlds_start()`. It should **not** initialise root `gameassets` or `gameworlditems` directly.
5. Build with your **already-working Stage 5.2b hand-owned `main.c` unchanged**. Project Sources should show `worlds/world1/` and `worlds/forest/` modules, **not** the four retired root generated .c modules.
6. Run on SIDBOX and verify physics, sprites, springs, animation, collectables and music still work.

## Local checks run

- Stage 5.2 world-controller host-GCC simulation: PASS.
- Stage 5.2 mixed-features world-controller host-GCC simulation: PASS.
- Stage 5.2d static/runtime contract + six actual rule-render variants + sprite symbol namespacing: PASS.
- Mapless generated starter host-GCC strict syntax test: PASS.
- Qt6 IDE and ARM V1 hardware build **not** available in this container; your actual compile and SIDBOX run remain the acceptance test.

## Changed IDE files

- `mainwindow.cpp`
- `mainwindow.h`
- `gamedesigner_export.cpp`
- `gamedesigner_update.cpp`
- `gameworldsnapshot.h`
- `idelibs/codehelpers/game/maingame.rulec`
- `development/tests/test_stage52d_world_manager_only.py` (test only)

No `main.c` replacement and no changes to world physics implementation.
