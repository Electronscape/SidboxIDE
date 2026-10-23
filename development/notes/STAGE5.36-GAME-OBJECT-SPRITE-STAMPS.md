# Stage 5.36: Game Object Sprite Stamps

## What it adds

In **Game Designer → Game Objects → Configure Game Object → Visual & Movements → Sprite Stamp → Arrange Sprite Stamp...**, assemble a single game-object sprite from tiles of an indexed 8×8 PPB sheet.

* Select a PPB sheet from the object's existing file or imported tile atlas resources; **Choose PPB...** opens an arbitrary PPB.
* Click a source tile, then click destinations in the arrangement grid to paint; **Erase cell** clears a cell to transparent index 0.
* Choose a 1–16 cell **width** and **height**, with existing cell positions kept on resize.
* **Flip X on paint** / **Flip Y on paint** set flags for each placed 8×8 tile independently.
* **Mirror stamp X** / **Mirror stamp Y** reverse tile positions and toggle corresponding per-cell flips. Mirroring twice restores the original.
* **Copy stamp from...** copies an already authored object stamp from this world, retaining its cells and source sheet.
* **Remove stamp** switches that object back to its original source PPB, using its first 8×8 tile.
* The edit dialog may be cancelled without changing the resource. Changes apply when you save the Game Object Properties.

The chosen tile sheet stays untouched. The world `.sbgm` saves `spriteStamp` source path, dimensions, 0-based source tile IDs, and per-cell flip flags. No new runtime stamp API is needed. The IDE writes an ordinary single-frame PPB under **gamesprites/generated/stamp_<resource-ID>.ppb** beside the `.sbgm`, sets that Game Object resource to the generated file, and keeps the source tile sheet for future edits. This baking happens again on world save so edits to the original atlas can be reflected.

**Colour/index handling:** All pixel indices are copied without re-quantisation. Index 0 is transparent, indices 1–255 are opaque. It uses the source PPB's original colour table and is compatible with existing foreground palette selection and the newly added Stage 5.35 matching-colour importer. Ensure the source palette indices are compatible with your game's foreground CLUT.

**Limitations:** A composed stamp is one static frame (up to 128×128 pixels). It does not create sprite animations, add physics collision cells, or auto-resize the object's hitbox; adjust its hitbox normally in Game Object Properties. The source sheet must have 8×8-aligned dimensions, with no more than 4096 source cells for editing. Other resources and custom runtime code are not modified.

## Installation

Drop the changed IDE sources into Stage 5.35 and rebuild the IDE. `gamespritestamp.h` is a new header. No new .cpp needs registering in the build system. Once a stamp is created, **Save World** then **Update Game Project / Generate Code** to include the generated PPB in the world bundle. Source files `main.c` and customised runtime helpers are untouched.

## Testing and safety

* The stamp model has an included Qt6 GUI-library unit test: `development/tests/test_stage536_spritestamps.cpp` for serialization, individual flips, mirrored positions, alpha rules, empty cells, size changes and invalid tile IDs. Run on Fedora from the IDE source directory:

```bash
g++ -std=c++17 -fPIC -I. development/tests/test_stage536_spritestamps.cpp \
  $(pkg-config --cflags --libs Qt6Gui) -o /tmp/test_stage536_spritestamps
/tmp/test_stage536_spritestamps
```

* Source-wiring/static checks passed in packaging environment: UI controls, PPB output, JSON round-trip paths, cross-world source path rebasing and stage splash number.
* Qt6 development headers are not installed in the packaging environment: **this is not yet a verified full Qt6 IDE compile or SIDBOX hardware test.** Verify the Fedora Qt6 build before depending on the change for irreplaceable project art.

*Suggested test:* Make a 2×2 collectible from four distinct sheet cells, flip one cell, save, reopen the Game Object editor, verify flip and 16×16 output, update game, collect it on real SIDBOX. Save first so you have the original `.sbgm` to roll back to.
