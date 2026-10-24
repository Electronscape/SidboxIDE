# Stage 5.77.1 - QJsonObject iterator compile fix (24 October 2026)

## Fix

`gamefloweditor.cpp`, line 944: Replace `embedded.cbegin()` and
`embedded.cend()` with `embedded.constBegin()` and `embedded.constEnd()`.
`QJsonObject` does not provide lowercase `cbegin`/`cend` in Qt6.
These const iterator functions avoid changing the JSON object while loading
saved embedded-array flow layout data.

`splashscreenwidget.cpp`: Build label updated to `5.77.1.241026`.

Only two source files changed. All Stage 5.77 flow logic, links,
editor functionality, and game assets remain unchanged.
Qt6 compilation is not available in this environment.

Replace these two files in the existing Stage 5.77 IDE source tree
and rebuild the IDE. No project regeneration is needed.
