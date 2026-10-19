# Stage 3.83 — Project Loaded! (2-second finish)

Based on the working **Stage 3.82 project-loading splash**, with all Stage 3.81
animation and earlier physics/crash/build fixes retained.

## Changed production files

- `mainwindow.cpp` only.

## Behaviour

When opening a project, the splash behaves as before and displays progress from
0 to 99% along with the asset or task being loaded. After everything succeeds,
it now:

1. Changes its heading to **Project Loaded!**
2. Shows **100%** on the progress bar.
3. Displays **Finished loading — all project assets are ready.**
4. Holds this completed appearance for **2 seconds**.
5. Closes itself automatically without blocking Qt's main event loop.

The dialog and all controls maintain **sharp square corners**; no new artwork,
theme settings, or external assets are needed.

If loading fails before completion, the splash closes immediately and shows
the existing error dialog, rather than displaying a false success.

## Installation

For the changed-files-only archive, copy `mainwindow.cpp` into the root of your
CoderGirl/SidboxIDE **Stage 3.82** source tree, replacing the existing file.
Rebuild in Qt Creator. There are no changes to project, firmware, or game-helper
files. No game regeneration is needed.

## Verification

1. Build the IDE in Qt Creator.
2. Open a game project (ideally one with lots of assets).
3. Observe progress and filenames during loading.
4. Check that the final **Project Loaded! / 100%** display remains for about
   **2 seconds**, then closes.
5. Confirm the project tabs and Game Designer work normally afterward.
6. For extra safety, close and reopen a Game Designer tab to check the earlier
   crash fix is unchanged.

Qt6 build and interactive tests **could not be performed** in the packaging
container (Qt6 development SDK unavailable). Available source regressions pass.
