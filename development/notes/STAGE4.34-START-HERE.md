# Stage 4.34 — Named Pickup Types & NPC Quest Memory

1. Back up your Stage 4.33 IDE and platformer game project.
2. Extract `GamerGirl-Stage4.34-Changed-Files.zip` over the IDE source root; rebuild the IDE.
3. Extract `GamerGirl-Stage4.34-Game-Helper-Update.zip` over your platformer project root. This deliberately replaces **only** `gamehelpers/gameadventureruntime.c` and `.h`.
4. Open the `.sbgm` project, save and run **Update Game Project**. Compile and test on SIDBOX.
5. Do **not** replace your hand-edited `main.c`; retain its working `on_pickup()` callback with `game_adventure_collect(item->kind)`.

See `Stage4.34-Named-Pickups-and-Quest-Memory-README.md` for the Guardian-flower-door setup and limits.
