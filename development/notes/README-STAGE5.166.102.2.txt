Stage 5.166.102.2 - Live Snow Atlas Preview
29 October 2026

INSTALL
  Overlay this complete IDE source archive on 5.166.102.1 and rebuild.
  Splash screen: Build: 5.166.102.2.291026

FIX
  gamedesigner.cpp / gamedesigner.h:
  The editor's in-world Weather preview previously drew filled circles even
  when the Snow graphic tile selected a registered Game Resources PPB atlas.
  Now the preview extracts the same 1-based atlas cell used by world generation
  and displays it at the configured 2..16 px particle size, using the current
  foreground palette and index 0 transparency.

  The cached glyph is invalidated when the PPB file, resource selection,
  tile cell, particle size, or foreground palette changes. Each frame draws
  all visible flakes onto a single camera-clipped transparent preview pixmap,
  with their existing camera-aware positions. No hundreds of scene items.

  No atlas / missing or invalid atlas tile still uses the previous filled
  circle fallback. Rain, lightning, day/night and their preview behaviour
  are unchanged.

  Resource selection is committed when you press OK in World Settings.
  To see the newly selected graphic falling in the main world preview,
  confirm World Settings and enable the Weather preview checkbox.

UNCHANGED
  Game runtime templates, generated world records, game saves, and user-owned
  main.c. No need to regenerate the game for this IDE-only preview fix.

VALIDATION
  Previous Stage 5.166.102 and .102.1 source tests and new preview tests.
  Full Qt 6 compilation cannot be performed in the supplied environment.
