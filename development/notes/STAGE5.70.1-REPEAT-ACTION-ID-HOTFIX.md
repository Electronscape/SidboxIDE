# Stage 5.70.1.241026 — Third wrong-item offer Game Object action hotfix

## Hardware report

Stage 5.69 repeated wrong-item dialogues reached First, Second, Third, and Fourth+ as intended, but selecting **Action on third offer (once) → Game Object** did not activate/deactivate/toggle the object.

## Confirmed source bug

`gameadventuregen.cpp` assigns automatic linked Game Object event IDs `33000 + nodeIndex * 3 + choice` (range 33000..33767). The generated array uses `game_adventure_wrong_repeat_t.reveal_action`, which was declared `int16_t` in `adventureruntime.ruleh`. All generated IDs therefore exceeded `INT16_MAX` (32767), became negative on the target, and were rejected by `if (repeat->reveal_action >= 0)` in `adventureruntime.rulec`. This does **not** affect dialogue rendering or the count, explaining the exact hardware symptoms.

## Fix

- `adventureruntime.ruleh`: change only `reveal_action` to `uint16_t`; the `-1` no-action initializer is represented as `UINT16_MAX` (65535). The struct still occupies the same number of bytes.
- `adventureruntime.rulec`: trigger the callback on the third wrong-item offer when `reveal_action != UINT16_MAX`. Pass the full unsigned event ID without truncation/sign conversion.
- `gameadventureeditor.cpp`: display a practical note in the repeated WRONG item section: **Deactivate** removes a solid door/barrier, whereas **Activate** makes it visible/solid. Solid tiles in the tilemap are independent and will continue blocking a doorway.
- `gameadventuregen.cpp`: document the reserved 33000+ linked ID range; the generated values remain unchanged. No project schema migration.
- Splash label updated to `Build: 5.70.1.241026`.

## Installation

1. Apply Stage 5.70.1 drop-in **over Stage 5.70**, then rebuild CoderGirl.
2. Open the project, **Update Game Project**. This regenerates the Adventure runtime and story with the corrected public header. Rebuild the game before testing hardware; the new IDE alone does not repair an already-built `.app`.
3. In Future Kim's repeated-item action, ensure the Game Object is selected and choose **Deactivate** if the goal is to remove/open a currently closed solid door. If the door is made of solid tilemap cells rather than a Game Object, removing a Game Object will not remove those tile collisions.
4. Test First → Second → Third and observe the door; Fourth+ should not retrigger the action. Game Object action and custom event ID both remain supported. No change to handwritten `main.c`.

## Verification

- `development/tests/test_stage5701_reveal_event.py`: host-compiled real Adventure runtime with linked event IDs **33000** and **33767**. Both tests cover First, Second, Third (once-only event), Fourth+, cross-world counter save/restore, the original wrong-item fallback, and no inventory consumption. PASS.
- `test_stage569_repeated_wrong_item.py`: original 61-event runtime regression. PASS.
- `test_stage569_generator_wiring.py`: editor/generator/quest-state linkage. PASS.
- `test_stage570_dialogue_tree.py`: folder-tree chooser regression. PASS.

The Qt6 IDE itself cannot be compiled in this environment (Qt6 development packages unavailable). The patch needs a real SIDBOX hardware acceptance run to verify Game Object status on the actual world.
