# Stage 5.98 | Thought bubbles (24 October 2026)

New reusable Adventure dialogue feature: **Use as thought bubble** on each dialogue choice's **Player speech**.

## Designer

1. Open **Adventure Editor > Dialogues & Choices**, double-click a dialogue node, and enter Player speech on a choice/continuation prompt. Check **Use as thought bubble (show with next dialogue)**.
2. **Dialogue + Thought Atlas** now shows two independent nine-slice frame designs, side by side. Both are chosen from the currently selected dialogue PPB tile atlas. Each frame has independent cell indexes and flip-X/Y flags. Empty atlas selection gives a simple rectangle.
3. **Dialogue Position** has dialogue settings above thought placement settings at the left, with a 480x320 preview to the right. Drag either the yellow dialogue frame or purple thought frame, or edit its own X/Y/width/height fields.
4. Save the world, **Update Game Project**, then rebuild the game. No `main.c` changes.

## Behaviour

When a player selects a choice whose Player speech is marked as a thought, the next dialogue node begins immediately and the thought appears simultaneously in its separately styled frame. The thoughts clear when that next node advances, the conversation ends, or the world is reloaded. Text types simultaneously with dialogue. The existing **Message sequence** mode follows the same logic, while still preventing its dialogue choices from running puzzle/inventory/NPC effects. Existing unmarked replies retain their previous sequential speech behaviour. A marked choice with no Player speech displays no thought, rather than showing its Continue label as a thought.

Per-world thought position, atlas cells and flags are design data, not hardcoded to any specific game. Existing worlds default to no thought flags, with no change to gameplay.

## Example

- Node 1, dialogue: `You place your item into the box.`
- Node 1, answer: `Continue...`, Player speech: `What have I got myself into?`, **Use as thought bubble** on, Next: node 2.
- Node 2, dialogue: `Steve lets you through.`
- When Continue is selected, the thought and node 2 dialogue render together.

## Verification

- Native C regression: stage598 thought and state reset, stage597 trigger message sequences, stage594 interaction rewards. All passed with GCC -Wall -Wextra -Werror.
- Existing generated wrong-item trigger test passed.
- Source pipeline checks passed and ZIP archive verified.
- Qt6 SDK is not available in the packaging environment; rebuild and interactive preview/hardware testing are still needed on Fedora.

Changed source files: `gameadventureeditor.cpp`, `gameadventuregen.cpp`, `idelibs/codehelpers/game/gameadventure.rulec`, `idelibs/codehelpers/game/adventureruntime.rulec`, `idelibs/codehelpers/game/adventureruntime.ruleh`, `splashscreenwidget.cpp`. Added two regression tests. No runtime C ABI struct changes, no user-owned `main.c` modifications.
