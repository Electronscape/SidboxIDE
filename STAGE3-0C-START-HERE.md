# CoderGirl Stage 3.0C — Expanded beginner comments in maingame.c.txt

Built directly on the confirmed Stage 3.0B IDE. **The only changed source file is `gamedesigner.cpp`.**

## What changes

After clicking **Generate V1 Game Code**, the Game Designer recreates `maingame.c.txt` in your game's project root. It now explains:

- What a mock `.c.txt` file is for and why it is deliberately not compiled.
- The difference between world coordinates, screen coordinates and the camera offset.
- Each object's kind, world position, collision box, optional spline, sprite-animation settings and type-specific behaviour.
- Which headers, player physics state, display buffers and pointers are needed.
- Why the startup sequence initialises assets before game objects.
- The important frame-by-frame order: movement update -> pre-physics lift carry -> player physics -> post-physics landing/bounce/conveyor -> pickup checks -> camera -> tiles -> objects -> player -> swap buffers.
- How the pickup callback and its `void *user` argument work.
- Why the object helpers subtract camera position and must not be double-drawn via `drawworld()` or double-offset via `offset_spline()`.
- Which generated files may be overwritten, and which game logic belongs to the programmer.

When the Game Designer cannot identify both an attached tilemap and an ordinary sprite named `player`, it produces a **separate, clearly labelled integration recipe**. Example names are identified as placeholders, instead of pretending they are real project variables.

## Installation

Replace **the IDE source-root `gamedesigner.cpp`** with the one in the drop-in archive, then rebuild CoderGirl on your normal Fedora Qt6 installation.

Open your `.sbgm` design and click **Generate V1 Game Code**. Double-click `maingame.c.txt` in the Project Tree to read the expanded notes.

**Your existing game project's `main.c` is never touched.** No V1 helper runtime, physics, tilemap, export format, object setup, graphics code, or Qt GUI layout has been changed.

`maingame.c.txt` itself is overwritten on generation; write your own notes in a separately named file.

## Verification

- Changed only the `exportExampleMain()` C++ generator, with no change to the call sites or its output path.
- Compiled the actual C++ generator function with a host-side minimal Qt-shaped shim using `g++ -std=c++17 -Wall -Wextra -Werror -pedantic` and exercised two scenarios: a tilemap + player + moving lift + animated coin, and a fallback scene with no tilemap/player.
- Examined the generated walkthrough outputs and checked required call ordering, object data, and comment structure in both branches.
- The full CoderGirl Qt6 application cannot be compiled in this environment because Qt6 developer headers/libraries are not installed. Real IDE compilation/testing still takes place on Fedora.

No rounded corners have been added! :)
