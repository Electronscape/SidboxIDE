# Stage 3.94 — Game Object Properties second visual pass

Based on the working Stage 3.93 Qt6 GUI source. **GUI-only change** in `gamedesigner.cpp`; no game runtime/serialization changes.

## Changes

- Object type selector items have square selection borders using the active `IDETheme::accent` colour.
- Every collapsible property section displays a theme-accented **16×16 icon on the left** and a separate disclosure arrow **on the far right**. Either header or disclosure arrow can collapse the section.
- QCheckBox indicators use square 16×16 styling based on the Player Animation Toolkit, with theme-defined colours, not hardcoded red.
- A dedicated **Sprite Info** heading in the preview pane shows actual sprite filename, frame cell dimensions, atlas frame count, and currently previewed frame.
- The original Collision Width and Height controls have moved below **Collision Preview**. They remain the SAME `hitW` / `hitH` spinboxes used by Save and the preview painter; the sliders remain synchronised. The right pane is independently scrollable on shorter screens.
- Collectable **Pickup Type** (with vector coin/heart/key/gem icons) and **Pickup Value** share a row; Respawn Frames stays below.
- Collectable **Pickup Sound / Respawn Sound** share a row; global **Audible Radius / Loop Fade Frames** share a row. Other object types retain their relevant audio controls.
- Explicitly capture `this` in two preview drawing lambdas, fixing C++20 `-Wdeprecated` implicit `this` capture warnings.

## Installation

Replace `gamedesigner.cpp` at the IDE source root and rebuild the IDE in Qt Creator. No project F5 update required.

## Validation

- Existing Stage 3.93 layout source checks and new Stage 3.94 source checks pass.
- Existing hazard, breakable audio, generated tutorial, animation, splash, loop integration, and other source regression tests pass.
- `Qt6Widgets` is unavailable in the build environment here; **actual Qt6 compilation and live visual sizing are pending** user test on Fedora.
- No changes to `gamedesigner.h`, game codegen, physics, or save formats.
