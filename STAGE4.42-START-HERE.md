# GamerGirl Stage 4.42 — Game Helper Template Engine (Adventure First)

Base: the user's known-good **IDE - 21-10-2026-1108.tar.gz** snapshot.

## What changed

Stage 4.42 adds the shared, strict `@IDE{NAME}` game-helper template renderer
(`gamehelpertemplates.h`) and migrates only these templates:

- `idelibs/codehelpers/game/adventureruntime.c`
- `idelibs/codehelpers/game/adventureruntime.h`

The Qt IDE now resolves templates in **all three relevant game install routes**:

1. **Update Game Project** (`gamedesigner_update.cpp`): validates and renders ALL
   required C/H helpers before touching the game project; afterwards it still
   makes the existing ZIP backup and uses the usual rollback on errors.
2. **Generate Game Code** / missing dependency installation
   (`gamedesigner_export.cpp`): renders any newly installed Game C/H files.
3. **Add Helper Code... > Game** (`gamedesigner.cpp`): renders Game C/H files
   before installing, whether replacing or filling missing source files.

**GUI helper templates are NOT migrated or modified.** All other Game helpers
are currently passed through unchanged. `gameadventuregen.cpp` still emits
`gameadventure.c/.h` (items, NPCs, dialogue) as before; migration of the static
story-table generator belongs to a separate stage.

## Current Adventure template fields

| Token | IDE value / rule | Usage |
|---|---|---|
| `@IDE{MAX_ITEMCOUNT}` | `64` | Existing safe runtime inventory capacity |
| `@IDE{ITEM_COUNT}` | Actual item count, 0–64 | Metadata in the generated runtime header |
| `@IDE{GA_COLS}` | `54` | Existing maximum 8-pixel font wrapping columns |
| `@IDE{GA_LINES}` | `6` | Existing inventory display lines |

Example template in `adventureruntime.c`:

```c
#define GA_COLS @IDE{GA_COLS}
#define GA_LINES @IDE{GA_LINES}
```

Result in your generated `gamehelpers/gameadventureruntime.c`:

```c
#define GA_COLS 54
#define GA_LINES 6
```

The installed C/H files never contain unresolved tokens. Unknown or broken
`@IDE{...}` markers produce an IDE error before Update Game Project begins
its backup/install phase; no broken placeholder should reach the C compiler.

**Important:** The runtime inventory capacity intentionally stays at **64**,
not `max(1, item count)`. A game may regenerate its story tables without
reinstalling the runtime, so shrinking the array to today's number of items
would silently truncate inventory later. This keeps Stage 4.41b behaviour.

Changing the surrounding helper C implementation or comments now needs only
an SDK helper template edit + **Update Game Project**. Adding a new named
placeholder, changing a rule/ABI, or changing the generated dialogue-table
format still requires an IDE update.

## Installation

1. BACK UP the working Stage 4.41b IDE and project. The uploaded 11:08 snapshot
   is the reference. Do not overwrite your only good backup.
2. For the changed-files ZIP, extract into the **IDE source root** while
   preserving subdirectories. It contains the shared renderer header, three
   IDE `.cpp` files, the two Adventure templates, and updated tests.
3. Build the IDE on Fedora using your normal Qt6 method.
4. Open a copy of your current adventure world. Click **Update Game Project**.
   Confirm its list of overwritten generated files. The usual ZIP backup will
   be created first.
5. Inspect `gamehelpers/gameadventureruntime.c/.h` in the **game project**:
   no `@IDE{...}` markers should remain; expect `GA_COLS 54`, `GA_LINES 6`,
   `GAME_ADVENTURE_MAX_ITEMS 64u`, plus the configured item count.
6. Build and run your platformer. Test Guardian/Future Kim, flower inventory,
   helped conversation on revisit, NPC animations and dialogue rendering.
7. Edit a **comment only** in
   `idelibs/codehelpers/game/adventureruntime.c`; click Update Game Project
   again. Confirm that the comment appears in the generated game helper —
   **without recompiling GamerGirl**. This is the key architectural test.

Do not copy the raw `idelibs/codehelpers/game/adventureruntime.c/.h` directly
into a game and compile them: they are now SDK templates. Use Update Game
Project or Add Helper Code, which resolve the placeholders.

Existing `main.c` ownership protections and ZIP rollback are unchanged.

## Tests run in this environment

- GCC syntax check on rendered runtime source and header for item counts
  0, 1, 2 and 64 — PASS.
- Stage 4.29/4.30/4.31/4.33/4.34 adventure native C regression tests
  against resolved templates — PASS.
- Stage 4.28/4.29 adventure IDE/source wiring checks — PASS.
- Stage 4.39/4.40/4.41b visual and generator source checks — PASS.
- All three game-helper install paths wired to one renderer — checked in source.
- Full Qt IDE build — **not run**: Qt6 development packages are not present
  in the test environment. Must build on Fedora.
- Actual SIDBOX hardware — **not run** here. Must test on real hardware.

## Boundaries

No changes to `idelibs/codehelpers/gui`, world objects, physics, game audio,
SPC handling, sprite rendering or the Adventure dialogue table generator.
