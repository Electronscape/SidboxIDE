# GamerGirl Stage 4.28a — Guardian NPC & readable generated main

## Diagnosis from your actual game archive

Your `world1.sbgm` *does* define NPC `Guardian[0]`, linked by sprite UUID
`334c1efb-fb65-4311-9fb8-ea8c6044051e` to conversation node `0`.
The generated `gamehelpers/gameadventure.c` also contains the correct NPC
at world `(3048,144)`, size `64x64`, interaction radius `48`.

However, your manually maintained **main.c** has:
- Adventure input and draw hooks, **but no `gameadventure_setup()`**;
- no call to draw `guardian[0]` (a decorative sprite, not a world item);
- no inventory collection call in the original pickup handler;
- no `#include "gamehelpers/gameadventure.h"`.

Your original **platform3.proj** also lacks references to the four new
adventure C/H files, so project-only builds may not compile/link their code
until you rescan/register those files.

## Fix — Your actual platformer project

Extract `Stage4.28a-Your-Platformer-Fix.tar.gz` **over your actual platform3
project folder**, **AFTER backing it up**. It contains:

- `main.c` — your custom movement/animation/water/space/spring logic untouched;
  adds Adventure include, startup setup, inventory callback and Guardian draw.
- `platform3.proj` — original IDE project listing plus four Adventure files.
- `maingame.c.txt` — readable generated example, adventure block indented.
- `README-IMPORTANT.txt` — instructions and caveat about NPC placement.

No `world1.sbgm` or other assets are changed. The user's custom `main.c` is
**not** overwritten by the IDE update operation, and the project-specific
patch deliberately preserves that ownership.

**Guardian location:** Player originally placed at X=2512; Guardian X=3048.
That's **536 pixels right** of spawn and initially offscreen. Walk to Guardian
and press **FIRE2**. Moving Guardian in World Designer and regenerating the
resources changes the generated NPC position; because `main.c` is hand-owned,
remember to update its two Guardian world drawing coordinates as well.

## Fix — IDE source code

To stop future `maingame.c.txt` examples from losing indentation inside
`if (!game_adventure_open())`, replace the IDE's `gamedesigner_export.cpp`
with the version in `IDE-GamerGirl-Stage4.28a-Changed-Files.tar.gz`, then
rebuild the IDE and use Update Game Project. Preprocessor directives stay
at column zero while ordinary code gains one level of indentation.

You can instead take `IDE-GamerGirl-Stage4.28a-Full.tar.gz` if you want
all the IDE sources together.

## Verification done here

- Inspected **your uploaded** `world1.sbgm`, `main.c`, `platform3.proj`,
  `gameadventure.c` and `maingame.c.txt`.
- Host GCC syntax checks passed for the patched game `main.c` and the two
  generated adventure C source files.
- Host adventure runtime test passed.
- Stage 4.28/4.28a source integration checks passed.
- **Not** yet compiled in Qt6 on Fedora or tested on actual SIDBOX hardware.
