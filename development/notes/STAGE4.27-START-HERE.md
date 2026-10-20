# Stage 4.27 — Music resource autoplay

Game Resources → Music → select a track → Resource Properties → **Play on game start**. Only one track can start automatically. Generated `gameassets_init()` now calls the existing `music_play()` after successful resource loads. No new audio codec, no firmware changes, no rewriting of user-owned `main.c`.

For installation, behaviour and tests see `Stage4.27-Music-Play-on-Start-README.md`.
