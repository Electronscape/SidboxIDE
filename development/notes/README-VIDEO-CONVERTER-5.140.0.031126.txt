SIDBOX IDE 5.140.0.031126 - Standalone Video Converter
=======================================================

Changed/new source files:
  CMakeLists.txt
  mainwindow.cpp
  sidboxvideoconverter.cpp          [NEW]
  sidboxvideoconverter.h            [NEW]
  splashscreenwidget.cpp

What it does
------------
* Adds "Video Converter" to the main IDE toolbar, independent of any project.
* Opens a standalone, resizable two-pane file browser. Left selects the video
  source; right selects a destination folder. Independent navigation and paths.
* The centre "Convert" arrow prompts for an output filename, initially the
  source filename with .avi as its extension. Users can change the name.
* Toolbar: video sizes 480x320 / 320x240 / 240x160, 10/12/15/20/25 FPS,
  MJPEG JPEG Q3..Q12, MP3 at 64/96/128 kbps, 44.1 kHz mono or no audio.
* Defaults: 480x320, 15 FPS, MJPEG Q6, MP3 96 kbps/44.1 kHz mono.
* Preserves aspect ratio by letterboxing. Video uses yuvj420p for the
  SIDBOX JPEG decoder, AVI container with MJPEG video and MP3 audio.
* Remembers all converter settings, source and target locations, window
  geometry and splitter arrangement via existing QSettings organization.
* Runs FFmpeg directly via QProcess (no shell), so the UI stays responsive.
  Progress is read from FFmpeg; ffprobe supplies duration when present.
* Shows an output log, allows cancel, and handles FFmpeg not being installed.
* Encodes to a temporary AVI in the destination folder first. Only after
  conversion succeeds is the destination replaced, preserving pre-existing
  output on failed or cancelled jobs.
* Uses the IDE theme, no game data or game project configuration touched.

How to use
----------
1. Qt Creator -> open current IDE CMake project -> rebuild.
2. Click "Video Converter" in the IDE's main toolbar.
3. In the left pane, select the source video (double-click to enter folders).
4. In the right pane, select or navigate to the destination directory.
5. Choose options in the toolbar and click the large center Convert arrow.
6. Confirm or edit the .avi filename. Wait for "Completed".

External dependencies
---------------------
- ffmpeg must be installed on the system and in PATH.
- ffprobe is optional, used only to calculate percentage progress.

Verification
------------
- Conversion command tested with provided gamezone.avi: generated valid
  480x320 MJPEG 15 fps video and 44.1 kHz MP3 in AVI container.
- Full IDE Qt6 build could not be tested in the provided container because
  Qt6 >= 6.5 development headers/config are unavailable. Build with Qt6 in
  your normal IDE environment; share compiler errors if any.

No changes to any other IDE source files or the SIDBOX firmware.
