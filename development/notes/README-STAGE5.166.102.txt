CoderGirl Stage 5.166.102 - 29 October 2026
Weather: standard Snow Atlas picker, continuous precipitation, irregular lightning

IDE:
- Weather > Snow atlas resource lists PPB Sprite/Tile Atlas resources registered in Game Resources.
- Weather > Snow graphic tile uses the EXISTING Adventure Editor atlas-cell grid picker, including middle-button pan. Cell sizes: 8/16/32. A tile thumbnail is shown on the button.
- None draws filled circles. Snow size slider remains 2..16 pixels, default 5.
- Saves particleAtlasId, particleTileSize, particleTileId beside the existing weather fields in each .sbgm.
- Regenerated gameworlds.c extracts just the chosen cell's indexed pixels from the named PPB at generation time and embeds up to 1KB of read-only data per snowy world; doesn't load a separate PPB at runtime. Missing/malformed selections produce a clear generation error, not a silent wrong atlas.
- Previously saved tile-ID-only snow settings are still loadable. The new editor changes these to circles until a resource and cell are selected; existing map-atlas fallbacks are retained in runtime for old records.

RUNTIME:
- Snow/rain source positions use uninterrupted world-space vertical paths (no modulo-height wrap within a fixed source chunk), preventing lower-edge respawn flicker. X scroll and wind remain world anchored. IDE preview mirrors the continuous movement.
- Lightning continues to honour the world Lightning Average Interval as the mean delay between main strikes (with +/-50% random jitter). Rare storm events get one or two weaker after-strokes (about 34% one, 10% two). Between strokes are dark gaps; each stroke respects the configured duration and overlay/palette strengths. No new weather setting or main.c call required.
- Lightning IDE preview uses a deterministic approximation of irregular primary strikes + occasional additional strokes; exact preview randomness need not match the SIDBOX game.
- The user-owned main.c and game saves are not modified. Regenerate ALL Worlds in IDE after changing weather settings, then rebuild the game to receive new world controller.

FILES CHANGED:
- gamedesigner.cpp/.h, gamedesigner_project.cpp: editor, preview, persisted settings
- gameadventureeditor.cpp/.h: exposes existing shared atlas-cell picker
- gameworldsnapshot.h: named resource lookup and per-world indexed pixel extraction
- idelibs/codehelpers/game/gameworlds.rulec: continuous weather and lightning burst runtime
- splashscreenwidget.cpp: Build 5.166.102.291026
- development/tests/test_stage5166_102_weather.py

VALIDATION:
- Five source+deterministic motion tests passed.
- Clang C11 host syntax check of reconstructed gameworlds.c passed using the user's real generated game source and SDK APIs, including a simulated embedded snow tile.
- Full Qt IDE build and real STM32H743 runtime remain to be tested by user.

Test suggestion: choose Snow > a registered PPB atlas and a tile; set snow size 8px. Regenerate ALL Worlds and verify the new snow graphic and no bottom-edge flicker while running/camera panning. Then set Thunderstorm to 7s mean and watch for occasional additional soft flashes while monitoring 50Hz.
