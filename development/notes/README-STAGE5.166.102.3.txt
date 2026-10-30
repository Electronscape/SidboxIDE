Stage 5.166.102.3 - Snow Particle Size 32px
29 October 2026

INSTALL
  Overlay this complete IDE source archive on Stage 5.166.102.2 and
  rebuild CoderGirl. Splash: Build: 5.166.102.3.291026.

CHANGE
  Snow particle size now ranges from 2 to 32 pixels (default remains 5).
  - World Settings slider, spinbox, tooltip
  - Saved weather setting load clamp in gamedesigner_project.cpp
  - Generated world metadata clamp in gameworldsnapshot.h
  - Weather renderer accepted size range in gameworlds.rulec
  - Editor comments and fallback-renderer comments

  Both the IDE-preview glyph and runtime BOB rendering already scale to
  the selected particle size, including 32px. No new renderer or PPB
  allocations. The existing normal-circle fallback also scales to 32px.

RUNTIME
  Regenerate ALL Worlds after rebuilding the IDE; recompile the game.
  Do not overwrite the hand-maintained game main.c.
  Weather movement, snow atlases, thunder intervals, preview palette and
  saving format are unchanged.

VALIDATION
  Source regressions for all four bounds, preview scale and runtime BOB
  scale plus prior Qt dialog and weather preview regressions.
  Full Qt 6 desktop build and STM32 performance require user testing.
