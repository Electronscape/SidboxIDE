# Stage 5.25: Adventure missing-item generated C fix

Based on Stage 5.24.

**Reported compiler error:**

```
error: static declaration of 'ga_next_node' follows non-static declaration
note: previous implicit declaration of 'ga_next_node' was here
```

## What changed

- `idelibs/codehelpers/game/adventureruntime.rulec`: forward declaration of
  `ga_next_node()` before `ga_reply_then_next()` calls it, preventing an
  implicit declaration in generated `gamehelpers/gameadventureruntime.c`.
- Same runtime template: missing-item fallback `-1` now really retains
  previous behaviour (do nothing) rather than closing the conversation.
- `splashscreenwidget.cpp`: `Build: 5.25.221026`.

## Install

Copy the updated files into the same paths in your **IDE source** and rebuild
CoderGirl. Open your game and run **Update Game Project** to regenerate
`gamehelpers/gameadventureruntime.c` from the repaired template, then build the
game again.

Do **not** put `adventureruntime.rulec` directly in `Platformer3/gamehelpers/`.
That directory needs the *generated* `.c`, not the rule template.

## Immediate fix if you do not want to rebuild the IDE yet

In `Platformer3/gamehelpers/gameadventureruntime.c` add this line directly
before the definition of `static void ga_reply_then_next(...)`:

```c
static void ga_next_node(int16_t node);
```

If you also want the `Keep current behaviour (do nothing)` option to stay
unchanged, change `c->missing_next >= -1` to `c->missing_next >= 0` in the
same generated `.c`. These direct edits will be overwritten by regeneration.

## Checks

Host-GCC runtime and source checks are in `development/tests/test_stage525_adventure_missing_item.py`.
Qt6 and SIDBOX builds remain for verification on the user's machine.
