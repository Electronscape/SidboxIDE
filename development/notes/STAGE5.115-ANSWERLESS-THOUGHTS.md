# Stage 5.115 (25 October 2026): Thought bubble with NO answer

## Bug reported

In a Fire2-only NPC speech with no selectable Answer, Stage 5.114 did not show
"Use as thought bubble (show with this dialogue)" Player speech. The runtime
only looked at the currently highlighted choice, and no such choice exists.
Users could make the thought appear only by inventing an Answer, which then
changed dialogue flow.

## Correct behaviour

Adventure Editor > Dialogues & Choices > Dialogue Node:

1. Enter the NPC's normal Dialogue text.
2. In Choice 1, leave **Answer** completely blank.
3. Enter the character's internal thought in **Player speech**.
4. Tick **Use as thought bubble (show with this dialogue)**.
5. Save world, Update Game Project, rebuild game.

The NPC speech and thought bubble now appear together, without an Answer or
selection cursor. Fire2 closes the conversation normally (or first completes
any text still typing, as before). The thought does NOT create a selectable
answer, fire choice events, award choice items, change NPC status, or follow a
choice Next link. Normal dialogue-on-close effects, including one-time rewards
and appearance changes, remain intact.

The first nonempty THIS-dialogue Player speech among the three blank Answer
rows is used. Choice 1 is recommended for clarity.

If there are any actual Answers, existing Stage 5.114 behaviour remains:
THIS means thought for the highlighted answer; NEXT means carry the thought
after choosing the answer. Hidden/once-used answers cannot leak into an
answerless node thought. The old NEXT flag on a blank answer still does not
trigger anything.

The editor now has explanatory text and updated tooltips. The Thought Bubble
Placement preview also displays answerless thoughts instead of the generic
"Thought preview" placeholder. No saved world JSON schema, generated game
struct layout, or user-owned main.c changes are needed.

This works for direct NPC conversations and no-answer Trigger Message dialogue.
Trigger Message with real Answer labels continues to hide answer-dependent
thoughts, just as before.

## Changed files

- `gameadventureeditor.cpp` (editor instructions, tooltips, live preview)
- `idelibs/codehelpers/game/adventureruntime.rulec` (no-answer thought fallback)
- `idelibs/codehelpers/game/adventureruntime.ruleh` (updated comments)
- `splashscreenwidget.cpp` (`Build: 5.115.251026`)
- `development/tests/test_stage5115_answerless_thought.c` (new native regression)
- `development/tests/test_stage5115_answerless_thought.py` (source & GCC test)
- `development/tests/test_stage5114_current_thought.py` (accept future build versions)
- `INSTALL-STAGE5.115.txt`, `INSTALL-START-HERE.txt`

Generator code is unchanged: Stage 5.114 already exports the reply text and
thought flag for all three rows, even without an Answer.

## Verification

PASS: native GCC -std=c11 -Wall -Wextra -Werror of generated runtime;
answerless Choice 1 and Choice 3, normal Fire2 close, no accidental answer
actions, real selectable-answer thought, Trigger Message modes, legacy NEXT,
empty Player speech. Existing Stage 5.114, Stage 5.113, Stage 5.98,
Stage 5.99, Stage 5.99.2, Stage 5.94, Stage 5.96 and Stage 5.97 native tests
also pass.

This environment has no Qt6 development SDK, so the Qt IDE was not compiled
here. Physical SIDBOX hardware test remains for the user.
