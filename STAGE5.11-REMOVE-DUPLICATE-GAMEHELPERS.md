# Stage 5.11: remove duplicate generated world helpers

The generated per-world `gameworlditems.c/.h/.txt`, `gameadventure.c/.h`, and
`splinepaths.c/.h` belong in `worlds/<world>/gamehelpers/`, not in the project
root `gamehelpers/`. They are generated temporarily in the root for the
existing rules/publisher, then removed after successful world publication.
This applies to all already-published worlds as long as the root file exactly
matches a published module (the publisher's namespace `#include` is ignored
for C-file comparison). Files which have been edited independently at the root
are preserved, not silently deleted.

**Keep in root `gamehelpers/`:** `gameworlds.c/.h`, `gameglobalstamps.c`,
`gameplayer.c/.h`, `gametilemap.c/.h`, `gamespline.c/.h`,
`gameadventureruntime.c/.h`, `gameworldobjects.c/.h`,
`gamecollectables.c/.h`, `gameanimation.c/.h`, and installed helper guides.
These are genuinely project-wide runtime modules.

World publication remains transactional: root generated files are only
cleaned after both the namespaced world and registry are successfully
published. Update Project already backs up the old root files and can restore
them if generation fails. A later normal Save Project discards references to
removed root world-module files; world source references remain unchanged.

No runtime `.c` helper, compiler flag, or world C-symbol renaming has changed.
The compiler already excluded root generated world-item/story/spline C modules,
so this removes disk/project duplication but does not necessarily shrink the
compiled `.app`.

## Test

1. Build the IDE with Stage 5.11 source, open Platformer3Testing.
2. Update Game Project for `forest` and `world1`. Confirm each world has its
   own generated `worlds/<world>/gamehelpers/gameworlditems.*`,
   `gameadventure.*` and, where applicable, `splinepaths.*`.
3. Confirm project-root copies of **these generated modules** disappear.
   Project-root shared helpers such as `gametilemap`, `gameworlds`, `gameplayer`
   and `gameglobalstamps` MUST remain.
4. Save the `.proj` and confirm it no longer lists missing root copies.
5. Build the game and test both worlds and world-item / adventure / spline
   behaviour on SIDBOX.

**Known workflow detail:** The manual *Export Spline Paths* action can create
a temporary root `gamehelpers/splinepaths.*` pair until that world is next
published. The project updater and generated game build remove it.

**Validation:** source-level checks and a fixture using the uploaded
Platformer3Testing files. Qt6 compilation and hardware testing remain for
the user.
