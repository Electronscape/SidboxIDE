# GamerGirl Stage 3.79b — Full Update Project on F5

Built on **Stage 3.79a**, keeping the confirmed `world1.sbgm` close-tab crash fix.

## Install

Either extract the **complete IDE** archive into a fresh/backed-up source folder, or copy these **four** production files from the changed-files archive into the root of your IDE source:

- `mainwindow.cpp`
- `gamedesigner.h`
- `gamedesigner_update.cpp`
- `projectsettingsdialog.cpp`

Rebuild in Qt Creator. Also included: this guide and updated Python source regression test under `development/tests/`.

## What F5 now does

For **V1 Game** projects, on the first build after opening the project (or after a referenced asset or game design has changed), F5 offers:

- **Update and Compile:** runs exactly the **same full `SidboxGameDesigner::updateGameProject()` implementation** as the Game Designer **Update Project...** button. That operation shows its existing detailed overwrite confirmation, makes a timestamped ZIP backup **first**, refreshes installed SDK helper C/H files, exports level and spline data, regenerates gameassets and world items, and updates `maingame.c.txt`. The `main.c` ownership safeguards remain in effect. **Only if that operation succeeds** does F5 continue compiling.
- **Compile Without Updating:** does not invoke Update Project; it continues the normal compile using existing generated/helper source. Normal saving of modified open designs still happens as before. It will not separately offer to install missing tilemap helpers. A first-time project whose files have not been generated may therefore fail to build if this option is chosen.
- **Cancel:** stops compiling.

**Important:** Update Project WILL OVERWRITE **installed** helper `.c/.h` files after the normal, explicit **Back Up and Update** confirmation. It creates a ZIP in `<game-folder>/.codergirl-backups/updates/`. Backups are retained according to the existing Update Project policy (newest 20 ZIPs). Existing user-owned `main.c` is protected; `maingame.c.txt` is regenerated.

### Remember my choice

The build prompt still has **Remember my choice for this project session**. With it checked, Yes remembers **full Update Project** (when game files need updating) and No remembers **compile as-is**. The full Update Project **backup / overwrite confirmation still appears** for safety, even if the build choice is remembered. Cancelling or failing a full update **does not** remember a newly selected Yes or continue compiling.

The preference is **not written** to `.proj` or `QSettings` and resets on reopening a project. **Project Settings -> Compiler -> Ask before running Update Project on build (F5)** turns the prompt back on.

## Suggested tests

1. Open Platformer3 or another V1 game project. Keep a copy of any customised `gamehelpers` C/H files before testing.
2. With `world1.sbgm` open, press F5. Choose **Update and Compile**. In the subsequent **Update Game Project — Confirm** dialog, inspect the listed replacements and choose **Back Up and Update**.
3. Check for a `.zip` in `.codergirl-backups/updates`, refreshed `gamehelpers/*.c/.h`, updated `maingame.c.txt` and normal compiler output after the update succeeds.
4. Cancel the second confirmation on a fresh run: ensure compilation does **not** begin.
5. Change a PPB or the `.sbgm` file. Choose **Compile Without Updating** on F5: ensure no full Update Project backup or helper rewrite occurs.
6. Tick **Remember my choice**, then change an asset again. Confirm the build question is skipped on the next build, and that Project Settings can re-enable it.
7. Reopen the project: the first F5 asks again. Open/close `world1.sbgm` repeatedly: the Stage 3.79a crash hotfix must remain fixed.

## Verification

Available Python structure/regression checks pass. Qt6 development libraries are not installed in this packaging environment, so actual Qt Creator compilation and SIDBOX testing must be performed on your system. Background conversion, PNG importer and game physics have not been changed by this stage. The syntax-highlighter limit stays at 2048 KiB.
