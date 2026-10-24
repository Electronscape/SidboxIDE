# Stage 5.64.2 — Files in Project audio recognition

Date: 2026-10-23

## Problem

The Files in Project tree had several independent extension checks. MP3 was
absent from the explorer whitelist and recursive file scanner, so it could not
appear after a Rescan. SBA was already in those lists, but was assigned the
unknown-file icon. The Add File dialog still defaulted to an outdated C/text
file filter, hiding both MP3 and SBA unless All files was selected.

## Fix

- Add `mp3` to `isProjectExplorerSuffix()` and the recursive
  `projectFolderSourceFiles()` scanner in `mainwindow.cpp`.
- Keep `sba` supported and give both formats (and the other existing audio
  extensions) the actual 16x16 `gr_icon_audio.png` asset icon in the tree.
- Expand **Files in Project > Add File** with the complete supported project
  file extensions, a dedicated **Audio files** filter, plus source-only and
  all-files filters in `mainwindow_projectexplorer.cpp`.
- Guard MP3/SBA against opening as C/UTF-8 source. Double-clicking audio now
  explains that it is a project audio asset; no unsafe binary parsing.
- Source compilation/IntelliSense filters remain unchanged. The IDE will not
  compile or C-index audio files.
- Change the splash to `Build: 5.64.2.231026`.

## Usage

Put `.mp3` and `.sba` files anywhere inside the project root (including
`music/` or `audio/`), then right-click **Files in Project > Rescan Project
Files**, or reopen the project. They should appear with the audio icon.

Being visible as an audio project file is *not* a guarantee that SIDBOX
firmware supports MP3 decoding or that a `.sba` is suitable for a particular
runtime playback API. No firmware codecs, title-screen runtime code or Game
Designer audio import/generation logic are modified here.

## Changed files

- `mainwindow.cpp`
- `mainwindow_projectexplorer.cpp`
- `splashscreenwidget.cpp`
- `development/tests/test_stage5642_project_audio_files.py` (regression check)

## Tests

- `python development/tests/test_stage5642_project_audio_files.py` PASS
- `python development/tests/test_stage426_spc_project_rescan.py` PASS

Full Qt6 compilation and interactive Fedora testing were unavailable in this
environment.
