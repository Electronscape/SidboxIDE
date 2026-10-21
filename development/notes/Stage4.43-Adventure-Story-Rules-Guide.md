# GamerGirl Stage 4.43 — Adventure Story Rule Files

Base: **Stage 4.42b**, itself derived from the user's **21 October 2026 11:08 known-good snapshot**. This is **only** the Adventure story generation migration. No changes to GUI helpers, World Objects, SPC, sprite physics or user-owned `main.c`.

## What changed

New SDK files in `idelibs/codehelpers/game/`:

- `gameadventure.rulec` — complete story C structure: includes, inventory/dialogue/NPC arrays, one flattened frame-record array, weak user event callback, linked event dispatch, skin loading and `gameadventure_setup()`.
- `gameadventure.ruleh` — declaration of the story API and resolved item/node/NPC counts.

The IDE takes validated values from the Adventure Editor and fills `@IDE{...}` markers in these files. The **output** is still:

- `<your game>/gamehelpers/gameadventure.c`
- `<your game>/gamehelpers/gameadventure.h`

**The rule files remain in the IDE's SDK** and are not copied into the game's compiler inputs. Project C files contain no unresolved rule markers.

Stage 4.42b's `adventureruntime.rulec/.ruleh` continue to handle the reusable engine and runtime settings. Stage 4.43's `gameadventure.rulec/.ruleh` handle project-specific **story data**. Both are now rendered by the IDE.

## What remains in the IDE

`gameadventuregen.cpp` still reads the `.sbgm` Adventure JSON, validates references and limits, escapes dialogue strings, maps sprite symbols and Game Object actions, and **serializes project records** into data-only placeholders. It no longer writes the C setup function, event callback or table declaration skeleton.

A new `GameHelperTemplates::renderFields()` uses strict, **one-pass** marker expansion. This prevents a player's dialogue containing text that *looks* like `@IDE{SOMETHING}` from being treated as a second instruction. Unknown, malformed or missing **required** tokens cause a generation error, rather than silently dropping content. The existing Update Project ZIP-backup/rollback mechanism remains in effect.

### Current rule markers

| `gameadventure.rulec` marker | Filled with |
|---|---|
| `WORLD_OBJECT_INCLUDE` | Optional Game Object header include |
| `ITEM_ROWS` | Inventory definitions |
| `NODE_ROWS` | Dialogue nodes and up to three choices each |
| `CHOICE_FLAGS` | Once-only and NPC-helped flags |
| `NPC_ROWS` | World coordinates, sizes, talk radius, starting nodes |
| `NPC_COMPLETED_NODES` | Next-visit dialogue node IDs |
| `NPC_FRAME_ROWS` | Flat NPC idle/talk animation frame list |
| `NPC_ANIMATION_ROWS` | Sprite animation bindings and frame offsets |
| `SKIN_CELLS`, `SKIN_FLIPS` | Dialogue atlas layout and flips |
| `LINKED_ACTION_CASES` | Validated Game Object event cases |
| `SKIN_LOAD_STATEMENT` | Optional PPB dialogue-skin lookup |

`gameadventure.ruleh` uses `ITEM_COUNT`, `NODE_COUNT` and `NPC_COUNT`.

As long as these marker contracts remain unchanged, adjusting the **C implementation around them** needs **no IDE rebuild**: edit the SDK `.rulec/.ruleh` and run **Update Game Project** again. Adding new marker fields, editor settings or new data kinds still requires an IDE update.

## Installation (Fedora / Qt6)

1. **Keep the 11:08 known-good archive untouched.** Back up your working Stage 4.42b IDE and your game.
2. Extract `GamerGirl-Stage4.43-Changed-Files.zip` into your **Stage 4.42b IDE source root**, preserving directories. Or use the supplied full Stage 4.43 source archive.
3. Rebuild GamerGirl with your usual Fedora Qt6 build command.
4. Open your normal `.sbgm` design and use **Update Game Project**. Allow its regular ZIP backup. The new story rules must be in `idelibs/codehelpers/game/` where GamerGirl finds the helper SDK.
5. Inspect `gamehelpers/gameadventure.c/.h`: you should find **ordinary C**, the actual Guardian/Flower text and the generated NPC records; **no** raw `@IDE{...}` markers. Check that the project also contains rendered `gameadventureruntime.c/.h`.
6. Compile your game and test flower inventory, Guardian's initial and helped greeting, NPC idle/talk animations, event-linked door activation, and inventory/UI. No change to `main.c` should be necessary.
7. **Template-only update proof:** Add a harmless comment in the SDK's `idelibs/codehelpers/game/gameadventure.rulec`. Click **Update Game Project** again without rebuilding GamerGirl. Check that the comment appears in `<project>/gamehelpers/gameadventure.c`.

If Qt fails to compile, **send the exact first error**. If project update fails, preserve and send its error message; your normal Update Game Project backup/rollback protects the generated outputs. This stage does not change a running game until you explicitly regenerate it.

## Tests performed in this environment

- Rule marker contracts, missing/unknown marker handling and installer exclusion checks.
- Native GCC `-std=c11 -Wall -Wextra -Werror -fsyntax-only` against resolved story rules for: empty Adventure project, saved four-node Guardian flower adventure, two NPCs with independent animation offsets, and design limits of 64 items / 256 dialogue nodes / 256 NPCs. A Python fixture serializes test data; the **Qt C++ generator itself was not compiled here**.
- Existing native tests for inventory, once-only dialogue, completed-NPC memory, animations, runtime configuration and Stage 4.41 generated editor settings still pass.
- Legacy source-level regression assertions adjusted to inspect the story **rule file** for implementations which no longer belong in `gameadventuregen.cpp`.

**Outstanding:** Fedora Qt6 compilation, IDE Update Game Project UI test, and real SIDBOX hardware run. Those cannot be claimed as passed yet.

## Rollback

Restore your Stage 4.42b IDE files or your untouched known-good archive, then use your game's Update Project ZIP backup if necessary. Existing user-owned `main.c` remains protected.

For **next stages**, migrate the other game-helper families incrementally, only after the Adventure story/engine pair passes on hardware. GUI helpers are specifically excluded.
