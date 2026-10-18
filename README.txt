SIDBOX / CoderGirl IDE — GamerGirl Stage 3.59
Tilemap canvas zoom, 1x–16x, pointer-centred
================================================

Changes to gametilemap.cpp ONLY (plus this README):

- Vertical mouse-wheel notches now zoom the tilemap canvas in/out one step.
- Numpad + / - zoom in/out when the map canvas has keyboard focus.
  Click anywhere on the map, or use the mouse wheel there, to focus it.
- The Zoom dropdown now offers 1x through 16x and follows wheel/key changes.
- Wheel zoom retains the world position under the mouse pointer (until a map
  edge prevents any more scrolling). Numpad zoom uses the pointer if it is
  inside the map canvas, or the viewport centre otherwise.
- Dropdown zoom retains the centre point of the viewport.
- Zoom preference and map pan settings keep their existing persistence.
- Middle-mouse drag and Alt+left-mouse drag still pan at any zoom level.
- Touchpad pixel-only wheel gestures continue using Qt's normal scrolling.
- No changes to map/slope/loop collision data or generated game code.

Build/install:
  Changed-files archive: replace gametilemap.cpp in your IDE source root;
  rebuild the project in Qt Creator.
  Complete archive: use as the whole IDE source tree.

Notes:
  At the outer edges of a small map, the viewport cannot pan far enough
  to hold the mouse anchor perfectly. The scrollbar clamps normally.

Verification:
  Source diff and packaging validated against Stage 3.58. No Qt6 SDK is
  installed in this environment, so Qt compilation and hardware/editor
  interaction have not been executed here.
