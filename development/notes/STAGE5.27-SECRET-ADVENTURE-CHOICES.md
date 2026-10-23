# Stage 5.27: Hide Required-Item Clues in Adventure Dialogue

Based on Stage 5.26. This is a narrow fix for the Adventure runtime, no
`main.c` changes, no project format changes, no dialogue editing needed.

## Behaviour

- All answer options are displayed alike whether the player owns the required
  item or not. Removed the `X` indicator from the dialogue choice list.
- When the player selects an option but lacks `Requires this item`, its
  `If missing required item` destination dialogue node opens **immediately**.
  The successful choice's player-speech bubble is not displayed first, and
  no extra FIRE2 press is necessary.
- A failed item check still does not grant/consume items, fire actions, mark
  a once-only choice used, or mark the NPC helped.
- When the item is present, the existing flow is unchanged, including player
  speech, success dialogue and attached effects.
- Leaving `If missing required item` at "Keep current behaviour (do nothing)"
  still leaves the current dialogue open on a failed requirement.

## Files

- `idelibs/codehelpers/game/adventureruntime.rulec`
- `splashscreenwidget.cpp` (`Build: 5.27.221026`)
- `development/tests/test_stage525_adventure_missing_item.c` (updated historic
  regression test to reflect the intentional immediate fallback)
- `development/tests/test_stage527_adventure_secret_choices.c` (new C test)
- `development/tests/test_stage527_adventure_secret_choices.py` (render and GCC test)

## Installation

Copy the files from the changed-files archive into the IDE source, preserving
folder paths, then rebuild CoderGirl. In your game run **Update Game Project**,
which regenerates `gamehelpers/gameadventureruntime.c`, and rebuild the game.

For a temporary test without rebuilding the IDE, edit the generated
`gamehelpers/gameadventureruntime.c`:

1. In `if (!ga_allowed(c))`, replace
   `ga_reply_then_next(c, c->missing_next);` with
   `ga_next_node(c->missing_next);`.
2. Remove the line `if (!ga_allowed(c)) ga_text(bx+bw-pad-24,cy,"X");`.

Those direct generated-file edits disappear during regeneration.

## Tests

PASS: `test_stage527_adventure_secret_choices.py` (generated C compiled with
`-std=c11 -Wall -Wextra -Werror`, missing and successful item paths, no X,
immediate fallback, no failed-choice effects).

PASS: `test_stage525_adventure_missing_item.py` (updated expected user journey).

PASS: `test_stage526_goto_world_persistence.py`.

PASS: `test_stage515_adventure_icon_restore.py`.

Note: the old `test_stage442_adventure_templates.py` has an existing stale
assertion about `skin_cells` and fails unmodified Stage 5.26 too. It is not
an outcome of this change. Qt6 and real SIDBOX testing are still pending.
