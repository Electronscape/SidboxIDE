# CoderGirl Stage 5.87: Update saved worlds without opening tabs

**Problem:** Update Project and build-time project regeneration used `MainWindow::openGameDesigner()` for every saved `.sbgm` that was not already open. That function adds a tab, leaving many world tabs open after a multi-world update. Adventure Inventory world sync already edits target JSON directly and does not call `openGameDesigner()`.

**Fix (mainwindow.cpp, MainWindow::updateGameWorldPaths):**

- Reuse any existing, open `SidboxGameDesigner` for the target world (unchanged behaviour).
- For a closed world, construct a temporary hidden `SidboxGameDesigner`, validate and theme it, call the **same** backed-up `updateGameProject(fromCompile)` and destroy it after that world completes.
- Give the temporary Designer the same protection against overwriting an unsaved `main.c` editor buffer.
- Never call `openGameDesigner` from the batch updater. No additional tabs, no current tab switches, no new open-tabs entries in saved project session.
- Preserve all backup, generated code, helper refresh, project scan, user-owned `main.c` protections and Adventure world sync.

**Files changed:** `mainwindow.cpp` and `splashscreenwidget.cpp`.

**Test on Fedora:** Keep Forest open; close World1; choose Update Project, accept. Confirm World1 source is refreshed under `worlds/world1/` but no World1 editor tab appears. Repeat with both closed or more worlds; try F5 with regeneration selected. Open tabs and the active tab should remain unchanged. Also verify inventory rule sync still writes to the other `.sbgm` without opening it.

**Testing limitation:** Source checks run in this environment; Qt6 development libraries are not installed here, so live GUI behaviour needs your Fedora test.
