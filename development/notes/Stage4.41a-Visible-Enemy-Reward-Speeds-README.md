# GamerGirl Stage 4.41a — Visible Enemy Reward Launch Speeds

This is a **Qt IDE-only** correction on top of Stage 4.41. It does NOT change the STM32 Game Object helper/runtime, generator, world/project save format or protected `main.c`.

## Problem and fix

The `Stompable Enemy` settings already contained `Reward speed X` and `Reward speed Y`, but both slider/spinbox controls were crammed side-by-side into a single row within a busy scrolling properties card. This made them hard to see/use.

In Game Object Properties > Stompable Enemy, the **DEFEAT REWARD** section now has clearly separate rows immediately after the drop selection:

- **Item dropped when defeated** — choose an existing Collectable object.
- **Launch dropped item on defeat** — tick to activate the X/Y launch velocity controls.
- **Reward speed X (px/frame)** — horizontal launch. Negative = LEFT, positive = RIGHT.
- **Reward speed Y (px/frame)** — vertical launch. Negative = UP, positive = DOWN; gravity takes over.

Each speed has its own full-width slider and editable number box. The slider **and** number box are disabled together if launch is off or there is no drop selected.

## Install

1. Back up your Stage 4.41 IDE source.
2. Replace **`gamedesigner.cpp`** in the IDE source root with the file in `GamerGirl-Stage4.41a-IDE-Reward-Speed-Visibility-Fix.zip`.
3. Rebuild GamerGirl with your existing Fedora Qt6 workflow and reopen the world designer.
4. Select your Stompable Enemy and open Game Object Properties; expand `Stompable Enemy` and scroll to its top if needed. Choose the reward, tick launch, and adjust the two clearly labelled speed rows.
5. Save Design > Update Game Project > Compile if you changed the reward speed values.

**Do not replace gamehelpers/gameworldobjects.c or .h**, and do not replace your hand-edited `main.c`. The Stage 4.41 drop implementation remains unchanged.

## Checks

- Enemy reward rows and enabling/static wiring: PASS.
- Stage 4.41 enemy generator/reward persistence: PASS.
- Stage 4.40 death atlas picker: PASS.
- Stage 4.39 red/green collision preview: PASS.
- Stage 4.38 generator and Stage 4.37 enemy generator: PASS.

Full Fedora Qt6 GUI compilation and actual visual verification remain to be done on your machine because Qt6 development libraries are not installed in this environment.
