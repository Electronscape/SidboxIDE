# CoderGirl Stage 5.114 (25 October 2026): Choose when a thought appears

## Adventure Editor -> Dialogues & Choices -> Dialogue Node

Every Choice / Player speech now has TWO checkboxes, stacked vertically:

- **Use as thought bubble (show with next dialogue)**: existing Stage 5.98 behaviour, unchanged. The player thought appears simultaneously with the subsequent dialogue node after selecting the answer.
- **Use as thought bubble (show with this dialogue)**: NEW. While this dialogue is on screen, the player's thought appears simultaneously with the NPC's current dialogue, based on the currently highlighted answer.

Ticking either option unticks the other. Unticking both gives the existing sequential Player speech behaviour. Blank Player speech does not substitute the Answer label as a thought.

## Runtime

- The selected answer controls the current-dialogue thought. Changing highlighted answers immediately changes or hides that thought. No inventory, quest, NPC or Game Object actions run on merely highlighting an answer.
- A this-dialogue thought does NOT repeat as a sequential spoken player reply when the answer is finally chosen; it advances directly to the configured Next dialogue (or closes if Next = Close conversation).
- Next-dialogue thoughts still carry across to the next dialogue and clear on advance. If that next dialogue has its own highlighted this-dialogue thought, its thought takes precedence while highlighted; changing to an unmarked answer resumes the inherited next-dialogue thought.
- Trigger Message (single text-only node) does not display this-dialogue thoughts, because it has no choices. Trigger Message sequence continues to show current thoughts for its navigation options and next thoughts for links, without performing quest actions.
- Existing dialogue skins, thought placement, independent font scales and z-order are reused. Runtime per-choice flags still occupy one byte, indexed `node*3+choice`: `0`=normal, `1`=next, `2`=this. No runtime ABI changes.

## Saved-world compatibility

The new optional JSON boolean `thoughtBubbleThis` defaults to `false`; existing `thoughtBubble` continues to mean NEXT dialogue. Old worlds retain their behaviour without migration. If malformed data sets both, NEXT wins in the generator and editor. Only new projects choosing THIS opt in.

## Installation

Copy the following files into the same paths in the IDE source root, rebuild CoderGirl IDE, then open the world, set the new option on any dialogue choice, save that world, choose **Update Game Project**, and rebuild the SIDBOX game.

- `gameadventureeditor.cpp`
- `gameadventuregen.cpp`
- `idelibs/codehelpers/game/adventureruntime.rulec`
- `idelibs/codehelpers/game/adventureruntime.ruleh`
- `splashscreenwidget.cpp` (shows `Build: 5.114.251026`)

No changes to user-owned `main.c` or other existing game files. Keep a backup of your source tree before copying.

## Verification performed

Passed GCC `-std=c11 -Wall -Wextra -Werror` native runtime tests:

- Stage 5.114 (new): current/next timing, change highlighted answer, suppress repeated reply, message and sequence modes, inherited thought, empty speech and no speculative action execution.
- Stage 5.98 (existing): next thought and state reset.
- Stage 5.99 and 5.99.2: dialogue typography and legacy spoken replies.
- Stage 5.97 and 5.96: dialogue sequences and single-message flows.
- Stage 5.94: puzzle/inventory dialogue outcomes.
- Stage 5.113: cross-world NPC action and state regression.

Source integration markers verified for IDE editor, generator and template. Qt6 development files are not installed in this packaging environment, so native IDE GUI compilation and actual SIDBOX hardware verification still require Fedora and device testing.
