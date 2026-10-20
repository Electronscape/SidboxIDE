GamerGirl Stage 4.22 — World Sprite Navigation & Colour Cycle Design Preview
=======================================================================
Based on complete Stage 4.21 source (not the older 20 Oct user archive).

CHANGES
1. World Designer: double-click a Sprite item in the Game Resources tree to
   centre the World Canvas on its existing QGraphicsItem. Game Object aliases
   continue opening Game Object Properties. Does NOT move the sprite, camera,
   physics player or other world objects. Editor pan is saved with .sbgm.

2. Palette Editor: a new Colour Cycles section with Enabled, Start, Length,
   Speed and Preview controls. It displays an animated preview of CLUT swatches
   but NEVER writes animated data into .pal or PPB files. Settings return to
   the owning World Designer and become part of Save Design (.sbgm).

3. World Designer: a new Colour cycles checkbox beside Asset tags and Show
   Tilemap displays an animated editor-only preview over indexed foreground,
   background and the visible tilemap overlay. No game-side graphics, palette
   files or firmware are modified. Editor-only preview is persisted.

SAVED .sbgm FIELDS (the document format remains version 1)
  "colourCycle": { "enabled": true, "start": 16, "length": 16, "speed": 5 },
  "showColourCycles": true
Older .sbgm files load with cycling off. Start is 1..254, length is 2..
(256-start), and speed is 1..255. The same cycle is applied to both preview
banks. Index 0 is reserved for foreground transparency. Range END for the
hardware API is start+length-1; length is NOT the last palette index.

GRAPHICS API INVESTIGATION (WHAT IS KNOWN)
In the bundled idelibs/api/graphics/graphics.h the exported calls are:
  gfx_palcycleon();
  gfx_palcycleoff();
  gfx_palcycleset(enabled);
  gfx_palcyclerange(uint8_t fromcol, uint8_t tocol);
  gfx_palcyclerate(uint8_t tick);
  gfx_usefpalette(palette);
  gfx_usebpalette(palette);
Only one cycle range and rate are exposed. No separate F/B cycling API is
exposed. The supplied archive DOES NOT contain the firmware-side implementation
of those calls; idelibs/api/graphics/graphics.c is an application-side file.
Therefore we cannot confirm whether both CLUT banks are cycled together or
verify rotation direction or exact timing. The host preview assumes positive
rotation and approximates the arbitrary tick as 50 Hz intervals. It is NOT a
hardware-accurate timing guarantee. No firmware modification attempted.

To enable cycle on actual SIDBOX hardware from the user's game code after
loading palettes, the documented API is (illustrative range start 16,
length 16, speed 5):
  gfx_palcyclerange(16, 31);
  gfx_palcyclerate(5);
  gfx_palcycleon();
The Stage 4.22 design settings do NOT automatically insert these calls into
main.c or generated runtime code. This is intentionally deferred pending
confirmation of firmware dual-bank behaviour. On firmware that cycles both
banks together, the same range/rate will affect both banks.

UPDATED SOURCE FILES
- gamepalette.h / gamepalette.cpp (shared editor-side cycle settings + rotation)
- gamepaletteeditor.h / gamepaletteeditor.cpp (design controls and palette preview)
- gamedesigner.h / gamedesigner.cpp (double-click and World Canvas preview)
- gamedesigner_project.cpp (.sbgm read/write)
- development/tests/test_stage422_colour_cycle_and_sprite_nav.py

BUILD / TEST
Extract the changed-files archive into your Stage 4.21 IDE source tree,
keeping file paths; rebuild with your normal Fedora Qt6 workflow.
Source-level tests pass; actual Qt6 GUI/native compile and SIDBOX behaviour
still need local tests. No firmware or C game-engine changes were made.
