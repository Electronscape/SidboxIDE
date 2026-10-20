# GamerGirl Stage 4.12 — High-contrast tags and Tile Flags icon modes

Based on Stage 4.11. The World Editor object-name tags and both kinds
of tile-editor front-render F markers now draw bold, fixed bright text
with black outlines independent of the IDE's theme.

The Tilemap Editor's Apply/Keep Flags combo has become two 24×24 icon
buttons, with clear toolbar dividers separating tile flags, collisions,
and player-reference overlays. Painting state still goes through the
original (hidden) combo and is saved the same way as before.

Replace `gamedesigner.cpp`, `gametilemap.cpp`, and `gametilemap.h` from
this source bundle and compile with your usual Qt6 build process.

See the `Stage4.12-Contrast-and-Flags-Toolbar-README.md` document
for details and testing notes.
