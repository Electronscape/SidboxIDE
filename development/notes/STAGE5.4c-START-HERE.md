# Stage 5.4c — True Shared Player Animation & Preview

Built from the **Stage 5.2e + 5.3 + 5.4b compiler-hotfix** source. This update fixes the incomplete UI separation identified after the initial shared-player release. It does NOT update the V2 GUI Designer, generated game physics, `.sbgm` world schema, or user-owned `main.c`.

## Changed files

- `gamedesigner.cpp` — Create / Edit Player opens `SidboxPlayerAnimationEditor` using the project's own PPB and `.sbanim`, without searching for a Sprite resource named `player`. Adds an existing-animation chooser and sets the correct `gameanimations/player_anim.h` output path. The Game Designer scene shows the shared player's Idle frame instead of the yellow start figure. The Tilemap Editor uses that same directional preview rather than the old world Sprite. The original yellow figure remains if no valid shared `.sbpi`/PPB is available.
- `gameplayerprofile.h` — one design-time-only `idlePreview()` helper loads the project `.sbpi` PPB, extracts the first Idle frame from `.sbanim` (or cell 0), handles Left/Right and mirror fallback, makes palette entry zero transparent, and exposes the optional preview hitbox.
- `gamedesigner_export.cpp` — `maingame.c.txt` advertises player-animation calls for shared players only when both `.sbanim` and `player_anim.h` exist (not just when a path is filled in).

## First test on Fedora

1. Install the three replacements and rebuild your IDE.
2. Open `world1.sbgm`. Select **Create / Edit Player**. Select a PPB file **inside the game project**, then enter the correct sprite cell width/height.
3. Click **Create / Edit Animations...** without adding any Sprite named `player` to the level. The familiar Animation Editor should open on the shared PPB; create/edit **Idle → Right** and optionally **Idle → Left**, then save animations. When asked to generate the C header, answer **Yes** if your game needs the generated animations.
4. Save the player profile. `players/player.sbpi` references the `.sbanim`; your atlas/animation files remain unchanged except when you explicitly save them in their own editor.
5. Look at the Game Designer canvas: Player Start now shows the chosen Idle sprite. Change facing in the **Player Start** properties and check that the image flips or uses the appropriate Left clip. Drag it; X/Y should still persist in the world `.sbgm`.
6. Open the Tilemap Editor: its design-time player overlay should show the SAME player image at this world's start position.
7. Try `forest.sbgm`: you should see the same player's artwork but forest's own position/facing. No per-world `player` Sprite needs adding. Run Update Project / F5, then test the existing game on SIDBOX.

### Migration / safety notes

- An existing `.sbpi` and its `.sbanim` are reused, not rewritten on opening the editor. If no `.sbpi` exists, the Create / Edit dialog can borrow settings from an old world Sprite named `player`, **once**, for migration. This old resource is not required thereafter.
- The shared player profile stores the **starting definitions**; runtime inventory/stats persist in the game world manager.
- Existing world-level Sprite resources (even those named `player`) are **not deleted or renamed**. Retire duplicates separately after confirming the shared runtime player, to avoid deleting test-world content unexpectedly.
- Animation `.sbanim` is editor metadata; the familiar editor still asks whether to update `gameanimations/player_anim.h`. Say Yes for generated animation C. Changes to `.sbanim` are saved by the animation dialog, independently of the Profile dialog's Save/Cancel.
- If there's no Idle clip or no `.sbanim`, the preview uses atlas cell 0; if `.sbpi`/PPB is missing or invalid, the yellow marker remains. The picture is not another runtime BOB or memory allocation on SIDBOX.

## Verification limit

Source-structure regression tests passed; **Qt6 dev libraries are not available in this container**, so the full Qt build, interactive preview, ARM link and actual hardware test must be completed on your Fedora/SIDBOX setup. Report the first compiler error if there is one, with the file/line number.
