CODERGIRL STAGE 3.2 — BOB-BASED SD TILE ATLAS
===========================================

Replaces the Stage 3.1 tile-atlas renderer (not your physics or game objects).

CHANGED IDE FILES:
  gametilemap.cpp
  gamedesigner.cpp
  idelibs/codehelpers/game/tilemap.c
  idelibs/codehelpers/game/tilemap.h
  idelibs/codehelpers/game/tilemap.txt

WHAT CHANGED:
  - Stage 3.1 still repacked PPB pixels into tiles. Now we keep the ORIGINAL
    row-major PPB pixels in one RAM buffer after reading from SD.
  - gfx_drawbob() draws each visible map tile, using its atlas column index.
    We shift bob.imgdat to the required atlas row so 16-bit map IDs still
    work even though gfxbob_t.index is uint8_t.
  - A blank 8/16/32 px tile is cleared via gfx_blit() first. This preserves
    transparent pixels and double-buffer behaviour; check performance on HW.
  - Map graphics IDs: 0 is blank, 1 means BOB frame 0.
  - Existing FNV-1a atlas content checksum retained. Stale PPB files fail.

FOR EXISTING PROJECTS:
  1. Make a backup/commit before replacing code.
  2. Replace gamehelpers/gametilemap.c and .h with the new matching SDK files.
  3. Re-export the Tilemap in updated CoderGirl to refresh level1.c.
  4. Keep your existing game_level1_load_atlas() call and the SAME current
     graphics/wall.ppb on SD. No change to main.c is necessary.
  5. Do NOT replace your hardware-proven main.c or gameworlditems helpers.

The Stage 3.2 version token GAME_TILEMAP_BOB_SD_ATLAS_V1 lets CoderGirl
refuse an out-of-date project helper at export time.

HOST CHECKS: C syntax and PPB fidelity/frame-address arithmetic tests.
REAL SIDBOX HARDWARE TEST: required. gfx_drawbob() is a firmware API, so
exact tile draw visuals/performance must be verified on the device.
