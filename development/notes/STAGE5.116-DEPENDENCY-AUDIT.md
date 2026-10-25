# Stage 5.116, 25 October 2026 - Adventure Editor control dependency audit

## Scope

A focused pass over the Adventure Editor (dialogue node, GIVE exchange,
inventory item, NPC selection and animation, dialogue tree, text/atlas frame,
and dialogue placement preview). Other IDE pages, including the general
Game Flow graph, are **not claimed to have been audited exhaustively**.

## Intent

Grey out operations with no effective runtime path; explain what is missing,
update on user edits, and retain inactive values unless users explicitly
change them. The runtime/generator and game C ABI remain unchanged.

## Preserved invariants

1. Answerless Player Speech + THIS bubble appears with the current dialogue;
   Fire2 dismisses normally.
2. On a terminal dialogue, the three Choice rows' `NPC gives` and two NPC
   appearance selectors are **still active mirrors** of on-close actions.
   Only blank Choice action controls of a node containing some real Answers
   are unreachable and greyed out.
3. Setting 'show with NEXT dialogue' requires a Next dialogue target.
4. Existing saved properties are retained when prerequisites go missing;
   explanatory warnings make dormant configurations visible.
5. No save format, generated C or game-owned `main.c` modifications.

## Regression

`python3 development/tests/test_stage5116_dependency_guards.py`

This performs UI/source guards and compiles/runs Stages 5.114 and 5.115
thought-bubble tests against the real, unchanged runtime. Other passing
selected tests include Stage 5.108 spotlight, 5.113 cross-world NPC,
5.97 dialogue sequence, 5.98 thoughts and 5.99.2 reply scales.

Some legacy tests that were failing on the unmodified Stage 5.115 source are
not represented as new regressions. In particular: stage534 exchange native
test, stage571 NPC visibility old source contract, stage5711 same source
contract. Stage 5.71.3 source test also has a superseded expectation that
NPC action selectors are always active even on unreachable blank choices;
the terminal/on-close exception remains intentionally preserved here.

Qt6 graphical compilation and manual UI acceptance remain outstanding.
