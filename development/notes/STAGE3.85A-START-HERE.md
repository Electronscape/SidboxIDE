# Stage 3.85a — Project Loading Splash Visual Hotfix

Based on **Stage 3.85**. This is a tiny cosmetic correction in `mainwindow.cpp` only.

## What changed

- Removed the opaque `QWidget` spacer in `ProjectLoadProgressDialog`; replaced it with `panelLayout->addStretch(1)` so the Nagelgirl illustration remains visible.
- Corrected the Qt progress format from `%p%%` to `%p%` to display `100%`, not `100%%`.

The 2-second **Project Loaded!** hold and existing project progress updates are unchanged. No other C++ files, asset formats, animation routines, physics code or game helpers were modified.

## Install (small patch)

1. Back up your existing IDE source (recommended).
2. Replace the IDE source-root `mainwindow.cpp` with the supplied file.
3. Rebuild your IDE in Qt Creator.
4. Open `platform3.proj` and verify that the project splash leaves the portrait unobstructed and reads `100%` at completion. The splash should close after roughly two seconds.

Qt6 SDK is not installed in the packaging environment, so **Qt compilation and visual testing must be done on your Fedora machine**.
