Stage 5.166.103 - Game Object Type Selector Mapping Fix
29 October 2026

INSTALL
  Overlay this COMPLETE IDE source package on Stage 5.166.102.3.
  Rebuild CoderGirl. Splash: Build: 5.166.103.291026.

BUG FOUND
  The left-hand OBJECT TYPE list in Game Object Properties displayed
  14 labels/icons for the canonical 15 behaviour IDs. The second
  type, `decoration_object` (switchable decoration), was absent from
  the labels. Every subsequent sidebar entry was displayed against
  the WRONG real object type, e.g. Stompable enemy appeared on
  `goto_world`.

FIX
  gamedesigner.cpp now maps each display name and symbol by the
  canonical, stable object-type ID, with a safe fallback for new
  types and debug assertions to catch missing mappings. The 15
  entries have correct labels and selectable IDs. The actual type
  combo, property-visibility logic, and game object serialisation
  are not changed.

IMPORTANT PROJECT CHECK
  The old mislabeled UI could save the WRONG behaviour if you
  selected an object type by its visible sidebar label and clicked
  Save. This release does not silently rewrite existing project
  objects. In Game Resources, inspect/reselect any object types you
  edited/saved with the old mismatched sidebar, especially Enemy,
  Goto World, Save Checkpoint or switchable Decorations.

RUNTIME
  No generated-runtime, world code, game save format or hand-owned
  main.c changes. Regenerate game code only if you actually correct
  the stored behaviour of a resource.

TESTING
  22 source-level regression checks passed: 4 new object-type mapping
  tests and 18 earlier weather/Qt preview tests. Full Qt6 desktop
  build and GUI visual verification must be performed on the user's
  machine (Qt dev packages unavailable in this environment).
