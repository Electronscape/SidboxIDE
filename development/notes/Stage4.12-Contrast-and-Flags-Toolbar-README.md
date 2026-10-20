GamerGirl Stage 4.12 — High Contrast Object Tags & Tile Flags Icons
Base: IDE-GamerGirl-Stage4.11-Full.tar.gz (user's 20-10-2026 08:39 source)

CHANGED IDE SOURCE FILES (root directory):
    gamedesigner.cpp
    gametilemap.cpp
    gametilemap.h

WHAT CHANGED

1. World Editor Game Object labels
   Object name tags are now painted by a WorldObjectTag (derived from
   QGraphicsSimpleTextItem to retain rename/show-hide behaviour). Text
   uses a bold 14-pixel font, fixed bright ivory (255,255,225), and a
   thick black 3.4-pixel outline drawn FIRST, before the bright fill.
   Result should stay readable over dark and light artwork in any
   selected IDE theme. No change to LCD/camera labels or sprite data.

2. Tilemap Editor front-render F markers
   Both the map canvas and Tile Stamp editor now draw bold F markers
   in fixed bright ivory with a black outline drawn behind the glyph.
   Font size adapts to cell dimensions (8–16px). Marker colour is not
   taken from theme text, and neither is the World Object tag colour.

3. Apply tile flags / Don't change tile flags
   The old 'Apply tile flags' combo is hidden, replaced with two
   theme-coloured 24x24 icon buttons:
     [square/tick] APPLY selected cell X/Y and front-render flags
     [square/minus] PRESERVE existing flags when painting
   Only one option can be selected at a time. Selection updates the
   original combo value (1/-1); the existing painting, QSettings,
   canvas and stamp logic remains untouched. Individual tooltips are
   supplied. The original combo remains as internal source of truth.

4. Toolbar grouping
   Tile flag buttons, cell/stamp flipping and front-render controls
   appear together, then a vertical divider and spacing, then the
   collision controls, followed by divider/spacing and player reference
   and hitbox controls. Extra divider within tile flag group removed.

INSTALLATION
   Replace the THREE source files listed above in your IDE source root
   and rebuild. Do not install the test script unless desired.

TESTING
   Stage 4.00–4.12 source regression checks: 14 PASS / 0 FAIL.
   Native Qt6 build and user-interface verification are still required
   on Fedora; the Qt6 development headers are unavailable here.

NOT CHANGED
   Firmware, games' runtime helpers, saved .sbgm/.map formats,
   game project generation, collisions, player spawn, 2048 KB editor
   syntax highlighting threshold, atlas paint mode behaviour.
