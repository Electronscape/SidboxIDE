# Stage 4.31 — Advanced Platformer Adventure refinements

See `Stage4.31-Adventure-Usability-README.md` for all changes and two **one-time hand-edited main.c fixes**.

**Especially important:** Your earlier `main.c` has a score-only pickup callback. Add `game_adventure_collect(item->kind);` after score addition to send collectable kinds into inventory. For the Adventure UI shortcut to avoid jumping, mask `BTN_UP` only in the player physics call. GamerGirl cannot modify your protected `main.c` automatically.

Run **Update Game Project** after installing the IDE so the generated `.c` and the refreshed `gameadventureruntime.c/.h` agree.
