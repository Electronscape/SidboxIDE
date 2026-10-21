# GamerGirl Stage 4.39 — Live Red/Green Enemy Collision Preview

**IDE-only update**, based directly on the complete **Stage 4.38** source.
Your generated game, current `.sbgm` files, and working SIDBOX game helpers do not need changing.

## What changed

Open **World Designer → Game Object Properties → Stompable Enemy** and look at the **Collision Preview** on the right:

- **RED solid rectangle:** enemy's damaging body, from the normal Width/Height collision settings under the preview.
- **GREEN dashed rectangle:** the vulnerable stomp hitbox. Its X, Y, Width and Height sliders are in the **Stompable Enemy** card.
- Both rectangles update **live while dragging or typing** values — no saving or rebuilding to see the result.
- The sprite remains visible underneath the translucent boxes.
- The image automatically scales to show both hitboxes, including a stomp zone wider than the body or positioned above it with a negative Y offset.
- The small red/green legend appears only for Stompable Enemies.
- Other object types and the existing sprite animation preview retain their previous presentation.

The preview uses the SAME origin and dimensions as the runtime: the red body begins at sprite position (0,0), and the green box begins at (stomp X, stomp Y). Width=0 uses the body width. X/Y offsets remain world-space even when a sprite's graphic is flipped. **Green is only vulnerable to a descending stomp**, not ordinary side contact.

### Recommended first try

For a 16 × 16 enemy with a 16 × 16 body:

- Stomp X = `-4`
- Stomp Y = `-6`
- Stomp width = `24`
- Stomp height = `6`

The green rectangle should extend 4 pixels outside each body edge and sit immediately above its head.

## Installing

1. Back up the working Stage 4.38 IDE source.
2. Extract **GamerGirl-Stage4.39-IDE-Preview-Fix.zip** at the IDE source root. This replaces **`gamedesigner.cpp`** only; other files in the ZIP are documentation and test.
3. Rebuild GamerGirl as usual on Fedora and open an existing Stompable Enemy's Game Object Properties.
4. Change the X/Y/Width/Height values and observe the preview; Save Design as normal if you want to retain new settings.

**Do not replace your game's** `gamehelpers/gameworldobjects.c` **or** `.h` for this update. The actual hitbox physics, death animations, patrol, splines, music, Adventure system and protected `main.c` remain unchanged. No project migration and no game-code regeneration are needed merely to display these previews.

## Checks

Passed in this environment:

- Stage 4.39 preview control wiring, two-color overlays, bounding layout for negative offsets, zero-width fallback and runtime hitbox field consistency.
- Stage 4.38 persistence/code generator source checks.
- Stage 4.38 compiled native C multi-hit stomp, vulnerable hitbox, separate body damage and death animation tests.
- Verified the original `gamedesigner.cpp` precisely matches the Stage 4.38 source archive before applying the patch.

**Qt6 development packages are not available here**, so the final native Qt compilation and visual check in Fedora are still to be done on your machine.
