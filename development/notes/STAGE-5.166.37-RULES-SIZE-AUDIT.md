# SIDBOX CoderGirl Stage 5.166.37: V1 Rules/Size Audit (27 Oct 2026)

## Measured baseline (user's uploaded `gametest.tar.gz`)

- Applet: `platform3.app` = **371,452 bytes** (362.7 KiB). `.app` is a packed SIDBOX ARM applet, not an ELF.
- Project app allowance: **512 KiB** (from `platform3.proj`).
- Native GCC -Ofast (x86-64) code-size proxy for duplicated Adventure item drop queries across two worlds:
  - Before: 1,234 bytes for four functions (sweep/floor in World1 and Forest).
  - After: 604 bytes (one shared sweep/floor in tilemap plus four thin world adapters).
  - **630-byte reduction in the isolated native code sections, NOT a measured ARM `.app` reduction**. Clang/ARM code generation may differ.

## Actual embedded map data in the project

Read-only array counts from the generated `gamelevels/*.c`:

| World | Graphics | Collision | Flips | Shape refs | Total |
| --- | ---: | ---: | ---: | ---: | ---: |
| world1 | 40,960 | 20,480 | 20,480 | 40,960 | 122,880 bytes |
| forest | 8,000 | 4,000 | 4,000 | 8,000 | 24,000 bytes |
| **Total** | **48,960** | **24,480** | **24,480** | **48,960** | **146,880 bytes (143.4 KiB)** |

These are **raw source-array bytes**, not linker-proven applet occupancy. The linker may discard unused arrays or change padding; a map file and rebuilt `.app` are needed for exact contribution. The current world definitions reference graphics/collision/flip/shape-map data.

## Refactor done in this stage

- **`idelibs/codehelpers/game/gameadventure.rulec`**: world-specific Adventure item-drop collision callbacks now delegate to `game_tilemap_drop_sweep()` / `game_tilemap_drop_floor()`. They resolve `gameworlds_map()` per call, without caching stale world pointers.
- **`idelibs/codehelpers/game/tilemap.c` and `.h`**: implement the algorithms once, preserving 16x16 item footprint, one-way detection, slopes, blocked marker return values and map boundaries. Only these item-drop functions receive GCC's size-oriented optimisation attribute, to prevent `-Ofast` from inlining the main collision routine into the shared copies.
- **`gameadventure.rulec`**: remove two unnecessary player-origin/hitbox forwarding wrappers. Register world manager functions directly; signatures match.
- No saved-map format, title flow, world-state format, player reset, graphics, music, or input logic changes.

## Tests completed

- 43,008 comparisons with the Stage 5.166.36 original item-drop routines, using the actual SDK tilemap collision implementation (8,16,32 pixel cells; mixed and empty collision types). **Pass.**
- World1 and Forest generated source adapted to new rule contract compile with native GCC. **Pass.**
- Existing native tests for title button latching, new/load session resets, death FIRE2, World Map render fast-path, World Map animations/undo and title registry. **Pass (10 suites).**
- Source contract and native C++17 lambda check. **Pass.**
- Full Qt6 GUI and ARM/SIDBOX builds **not available in this environment**. Size reduction to `.app` must be measured on actual V1 toolchain; physical 50Hz gameplay still needs checking.

## Future improvements, ranked by probable payoff

1. **Make map storage user-selectable per world** (already supported by the Tilemap Editor's external `.map` output). The two embedded maps represent 146,880 raw array bytes. External maps are promising but require TFCard files to be deployed correctly. Do not switch without explicit user approval.
2. **Compare `-Ofast` with `-Os` as an OPTIONAL build configuration**, checking both `.app` size and actual SIDBOX performance at 50 Hz (no default flag change in this stage).
3. Investigate shared per-world particle simulation code (both worlds generate near-identical particle step, draw and sine table). This is a bigger refactor and requires per-world state isolation to avoid corrupting fireflies/weather.
4. Collect V1 link map file output, or record total text/rodata/data after every major update. The read-only `development/tools/audit_v1_project_size.py` inventories raw embedded map arrays but is not a replacement for a linker map.

## Installation (Stage 5.166.36 -> 5.166.37)

1. Back up your working source (user has already made a rules backup). Apply the small hotfix over Stage 5.166.36, or use the full Stage 5.166.37 source archive.
2. Rebuild the IDE (splash label `5.166.37.271026`).
3. Open the game and run **Update ALL Worlds / Update Game Project**. This stage requires BOTH updated `gamehelpers/gametilemap.c` and `gamehelpers/gametilemap.h` as well as the regenerated per-world `gameadventure.c`. If only the world files are regenerated, the linker will not find the two new shared functions.
4. Rebuild V1, record the new `.app` size for an apples-to-apples comparison, and test item drops, New Game, Load Game and world transitions on hardware.
5. Keep your working hand-owned `main.c`. It has **no required edits** in this stage.

The refactor is deliberately incremental. Avoid claiming a large `.app` reduction without a V1 before/after build and validation on SIDBOX hardware.
