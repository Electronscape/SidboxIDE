# Stage 3.96 — Local Find, PPB Viewer, Theme Fixes & Head-butt Rewards

Based on the complete working Stage 3.95a source archive. New notes live in `development/notes/`.

## User-facing changes

* **Ctrl+F** opens a simple find box for the active source document. **F3** advances through occurrences, wrapping to the start. **Ctrl+Shift+F** preserves the full-project Find/Replace interface unchanged.
* **Programmer Calculator** checked bit colours now use the IDE accent and a contrasting calculated foreground, updating if the user changes the theme.
* **View PPB...** toolbar action opens a standalone PPB viewer (also opens PPBs selected in the project file tree). Uses the PPB's **own embedded 256-entry CLUT**, no external palette file needed. Scroll-hand dragging pans; mouse wheel and +/- buttons zoom; Fit/100% controls are included. The existing PPB reader applies a file size guard.
* **Game Object Properties** selected Object Type text gets a contrast-aware foreground in light/dark themes. Internal UUID remains in `.sbgm` and generated data but is no longer shown as an end-user Object ID row.

## Breakable from below + falling reward

In a Breakable object's Properties, check **Break by jumping into underside (head-butt)**. The existing **1–4 Hits to break** still controls how many separate deliberate jumps are needed. The block remains solid when stood on, but landing on top does not damage a head-butt block. Hits from below stop upward travel and pulse the existing Breakable Hit/Break sounds once per event. Touch-to-break and bounce remain separate modes.

Under **Drop collectable on break**, choose an existing Collectable from Game Resources. The link is stored as its stable resource ID, so renaming resources is safe. Each breakable reward must have its own distinct Collectable object; two blocks may not use the same reward. The selected reward is automatically **hidden in the generated runtime at startup**, even if its editor checkbox says initially active. Its location in the editor is only a design-time reference.

On the final break hit, the generated World Objects code positions the linked collectable horizontally centred on the block at the block's top, makes it visible, accelerates it downward (0.65 px/frame² capped at 9 px/frame), tests each pixel against the game's **tilemap collision**, and enables collection only after landing. Its pickup kind, value, sprite, animation, audio and later respawn rules remain those of the existing Collectable. **You must enable the Advanced Platformer tilemap**, and the reward must not have its own spline attached. Generation validates both restrictions and validates missing/duplicate reward links.

The source template `idelibs/codehelpers/game/collectables.h/.c` gains a `can_collect` flag, defaulting to 1 for existing pickups. Head-butt code only affects breakables whose new opt-in flag is enabled; old saved maps load with it off. No existing game physics code was replaced. The generated `gameworlditems.txt` now explains this flow.

### IDE and game update steps

1. Copy changed production files over the same paths inside the IDE source directory, then rebuild it using Qt Creator.
2. Set up a Breakable and a Collectable in Game Designer; select the Collectable as the reward. The selected Collectable is hidden automatically at runtime until spawned.
3. Save the `.sbgm`, then **F5 → Update and Compile**, so both the World Objects and Collectables helper templates and generated `gameworlditems.c/.h` are refreshed.
4. Existing user-owned `main.c` should already call `gameworlditems_update(1)`, `gameworlditems_before() / after()`, `gameworlditems_check(...)` and drawing passes. Keep these calls; there are no additional reward-specific calls.
5. Test on the actual SIDBOX: jump repeatedly into the underside; confirm that only the final hit spawns the reward, which then falls to ground and becomes collectible.

### Verification

* Native C: head-butt vs stomp, hit counter, sound event flag, separation rearm — **PASS**.
* Native C: `can_collect` pickup gating — **PASS**.
* Native C: extracted generated fall template, tile collision stop and pickup enabling — **PASS**.
* Previous breakable, spring and hazard native regressions — **PASS**.
* Stage 3.96 source-level integration and existing tests — **PASS** except the pre-existing Stage 3.71 mechanical checksum test which also fails on the supplied Stage 3.95a baseline.
* Qt6 is not installed in the working container; **Qt Creator build and SIDBOX hardware tests are pending**.

**Known scope:** Falling rewards collide with the static tilemap, not moving platforms or other game objects. The spawn is one-shot per breakable. This is not a full inventory or general-purpose particle emitter. PPB alpha/colours are whatever the PPB's embedded CLUT specifies; shared palette variations require using Game Designer's corresponding palette preview.
