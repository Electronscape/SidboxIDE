# Stage 5.38: Shared HUD Designer

**New button:** Game Designer / World controls → **HUD Editor...**, directly beside Adventure Editor.

## What the editor creates

- **One shared layout per game project**, saved as `gamehud.sbhud` beside your `.proj`, rather than a HUD copied into every `.sbgm` world.
- **HUD tilemap**: width/height in cells, configurable cell width/height, PPB tile atlas drawn from *Game Resources*, click-to-paint atlas cells, per-cell Flip X / Flip Y, whole-layout horizontal/vertical mirroring, right-click erase.
- **HUD collectables list**: reads *all saved* `.sbgm` worlds from the project directory; only collectables with `Show in HUD` enabled appear. Shows the item's icon and pickup type; drag onto the HUD canvas to place a counter. Move it later by dragging; right-click to delete. **Save Design in the relevant world first** so it appears in the list.
- **Text labels**: enter text, tick Place Text and click the HUD canvas. Drag to reposition, double-click to edit, right-click to delete. Set the shared text colour index.
- **Generated renderer**: `gamehelpers/gamehud.c/.h`, registered once in the `.proj` source-file list. The designer bakes atlas tiles to a compact indexed bitmap at design time. Runtime drawing uses the existing `gfx_drawbob` and `gfx_drawtext` APIs, with no new engine or world-specific draw rules. `Update Game Project` refreshes the generated HUD code and assets.

## Count semantics (changed from Stage 5.37)

For new tracked collectibles, **one physical pickup = +1 in inventory (if selected) and +1 in the HUD (if selected)**. HUD totals are shared across world transitions and don't drop when inventory is spent. **Pickup Value** is *not* the HUD count. It remains available to user-defined `on_pickup` callbacks for gold/score/etc. Old untracked pickups remain on their legacy callback path. Multiple worlds using the same Pickup Type intentionally share one counter. Counters currently track pickups, not all sources of an Adventure inventory item.

## How to draw the HUD

CoderGirl regenerates `maingame.c.txt` with:

```c
#include "gamehelpers/gamehud.h"
/* After drawing the level and foreground, before dialogues: */
game_show_hud(0, 0);
```

`game_show_hud(x, y)` uses **LCD/screen coordinates**: it is not offset by the scrolling camera. Draw each frame on the *foreground* buffer after the world and before modal dialogues. `gamehud.c` is compiled once as a project-owned source file.

**IMPORTANT:** if `main.c` is user-owned, CoderGirl never overwrites it. You must copy the include and one-line draw call from `maingame.c.txt` into your own `main.c` to see the HUD. Regenerating `maingame.c.txt` alone does not change an authored game loop.

This is a single static HUD tile composition with draggable icons and numeric counters, not animated HUD cells. Runtime art is indexed and uses the currently active foreground palette, so pick palette indices compatible with each world's palette to keep colours consistent.

## Status

Source-level checks and strict host GCC pickup tests passed. Qt6 development headers and physical SIDBOX hardware are unavailable in this environment, so the full IDE GUI build and hardware execution are not yet verified. Back up your project before testing. **Do not overwrite user-owned `main.c`.**

Splash: `Build: 5.38.231026`.
