# Stage 4.55 — World Items Generated Guide Rules

Based on Stage 4.54, without changes to game runtime code.

## What was that `G <<` block?

It generated the text file `gamehelpers/gameworlditems.txt`. This is the beginner-facing
World Items integration guide, not executable C. The text explains object counts,
player physics bindings, springs, collision safety, triggers, breakable rewards,
and positional audio. This was the remaining hardcoded World Items *documentation*.

## What changed

- `gamedesigner_export.cpp`: `SidboxGameDesigner::exportWorldItems()` now reads and
  renders `gameworlditems.ruletxt` using the same strict conditional/value renderer
  as other SDK rules. All 11 template fields are explicitly supplied.
- `idelibs/codehelpers/game/gameworlditems.ruletxt`: new rule file containing the
  complete programmer guide and feature-conditional paragraphs.
- The empty-world stub also comes from this same guide template.

No `.inc` files have been introduced. `gameworlditems.rulec` and
`gameworlditems.ruleh` are byte-for-byte unchanged. The output remains named
`gamehelpers/gameworlditems.txt` in user projects.

## Verification

- 216 old-versus-new generated guide comparisons passed byte-for-byte.
- Pickups/worlds/triggers, audio, map, reward, and empty-world cases included.
- Source audit confirms removal of the old `G <<` guide-generation block.
- Qt IDE compilation and SIDBOX hardware execution **not performed here**.

## Test

1. Replace the exporter and install the new `.ruletxt` under `idelibs/codehelpers/game`.
2. Rebuild the IDE.
3. Open your existing game project and select Update Game Project / regenerate World Items.
4. Inspect `gamehelpers/gameworlditems.txt` to confirm its existing guidance remains.
5. Generate and compile your game; verify it on SIDBOX as usual.

If the rule file is missing/corrupted, the generator will report an error instead
of writing an incomplete guide.
