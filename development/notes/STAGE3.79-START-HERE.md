# GamerGirl Stage 3.79 — Generate Before Compile Reminder

Based on **Stage 3.78**. This update addresses the background appearing correctly in the Game Designer while the SIDBOX game still uses stale `gameassets.c` because the game resources were not regenerated.

## Install

Either extract the **Complete IDE** archive into a backup/new source folder, or replace these six files from **Changed Files Only** in the IDE source root:

- `mainwindow.cpp`
- `mainwindow.h`
- `projectsettingsdialog.cpp`
- `projectsettingsdialog.h`
- `gamedesigner_export.cpp`
- `gamedesigner.h`

The Changed Files archive also includes this guide and two Python regression tests. **Do not copy the tests into the source root**; keep their `development/tests/` folder structure. Compile normally with Qt Creator.

## Test: the missing background scenario

1. Open your saved V1 Game project (for example `Platformer3`).
2. Press **F5**, whether you are on `main.c`, `world1.sbgm` or another tab.
3. The first build of that opened Game project asks:
   **Check generated game files before compiling?**
4. Choose **Update and Compile**.
5. The IDE regenerates `gameassets/gameassets.c/.h`, game world objects, required spline output and missing map exports **without replacing the installed `gamehelpers/*.c` or `*.h`**.
6. The normal build then continues, using the refreshed sources. Copy any changed disk-loaded PPB and `.map` assets to TFCard as usual.
7. Change/reimport a PPB asset and press F5 again: a changed PPB newer than `gameassets.c` triggers another reminder (unless you've remembered a choice).

### Prompt choices

- **Update and Compile:** regenerate the game's code/assets, then compile. If generation fails, F5 stops rather than compiling stale generated code.
- **Compile Without Updating:** compile using current generated files. Repeated prompts can be suppressed for this IDE session by ticking **Remember my choice for this project session**.
- **Cancel:** leave the build stopped. Do not remember a cancellation.
- **Remember my choice:** the answer (regenerate vs skip) applies automatically on subsequent builds *when game files become stale*, without another prompt, for the current project session only. It does not continuously regenerate unchanged files.

## Re-enable reminders

Open **Project Settings → Compiler** and tick **Ask before regenerating game files on build (F5)**. If you had previously ticked Remember my choice, the checkbox will be unchecked; rechecking it restores the prompt immediately.

**Deliberately not saved**: neither the checkbox state nor the remembered answer is written to `.proj` or global `QSettings`. Reopening a project always restores the default reminder on its first build. GUI/V2 projects aren't affected by this reminder.

## Safety / important differences

- F5 regeneration is *not* the **Update Project** button from Game Designer: **Update Project** deliberately refreshes installed SDK helpers, with a ZIP backup and confirmation. F5 never calls that destructive helper replacement workflow.
- F5 regenerates `gameassets.c/.h`, the generated `gameworlditems` and examples (and needed map/spline data). User-owned `main.c` continues using the existing ownership protection logic. If a helper is missing, the generator may install a missing helper but **never silently overwrite an existing one**.
- It attempts to preserve the existing graphics mode (`embedded` vs TFCard PPB-loaded) by recognising the existing generated `gameassets.c`; first-time generation defaults to TFCard PPB loads.
- For multiple `.sbgm` files, the IDE asks you which design to generate, rather than overwriting the same `gameassets` outputs repeatedly with different worlds.
- All physics, animation helpers, PNG palette converter, tilemap model and the 2 MiB syntax-highlighter threshold are untouched.
- The previously reported crash when closing `world1.sbgm` is a *separate, unresolved* issue; this patch does not claim to fix it.

## Verification

The structural/regression Python tests for refactoring, PNG importer, Tile Atlas selector, background import and Stage 3.79 build logic passed. Qt6 is not installed in the packaging environment: Qt Creator compilation and real SIDBOX acceptance **have not been tested** here.
