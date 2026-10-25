# Stage 5.96 — Trigger dialogue modes and authoring guards (24 October 2026)

## Why
The saved World1 archive contains `stevesKey`, a Trigger requiring `Dildo`, linked via `Disable target` to `doormanSteve`, and set to start BigSteve dialogue node 10. This is not an NPC transaction: the Trigger's linked action commits immediately after successful item USE. The selected node is the beginning of a branching conversation, so players see the conversation *after* the door has already disappeared. `doormanSteve` also has no INACTIVE state frame (`-1`), hence disabling it hides its image.

## Authoring changes
* `Game Object Properties -> Trigger / Switch -> Dialogue behaviour` offers **Single message (no choices or dialogue actions)** and **Full conversation (choices and dialogue actions)**.
* Single message reuses the selected Adventure node's **speaker and text only**, with normal dialogue visuals. It never follows its choices, executes any node closing gifts, NPC appearance actions or other dialogue effects. All Trigger success actions still execute normally.
* Full conversation preserves previous gameplay. Existing `.sbgm` worlds without the new property load as **Full conversation**, so nothing is silently changed on reopening.
* A description warns when a selected node has player choices; saving a newly selected full conversation prompts for confirmation. Explicitly note that Trigger success actions take place **before** dialogue choices.
* `Linked action: Disable target` explains whether the target has an INACTIVE frame. Selecting an unconfigured target now warns on save that the target will disappear.
* Logic Flow labels distinguish single-message and full-conversation links.

## To get a short message after the player gives the item
1. In Adventure Editor create an independent, *terminal* dialogue node: speaker e.g. `BigSteve`, text `Thanks! You can pass now.`, **no choices**.
2. On `stevesKey` (Trigger) set `On success: dialogue` to that new node.
3. Set `Dialogue behaviour` to **Single message**. Keep linked action `Disable target` if Steve is supposed to stop blocking the way.
4. For Steve to **remain visible** with a different expression, his sprite atlas needs a distinct frame. Edit **doormanSteve**, not the Trigger: set ACTIVE/INACTIVE state frames to valid atlas indices. An INACTIVE frame >= 0 draws without collision. If -1, disabling Steve still hides him, intentionally.
5. Save the world, Update Game Project, rebuild the game. You do **not** need to replace `main.c`.

## NPC alternative
If the player must choose between Yes/No **before** Steve moves, set up an Adventure NPC with dialogue-choice actions instead. A Trigger's USE check succeeds before its dialogue begins, so its later dialogue choices cannot decide whether the item is accepted or the linked object disables.

## Modified files
- `gamedesigner.cpp`, `gamedesigner.h`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`, `gamefloweditor.cpp`
- `idelibs/codehelpers/game/adventureruntime.rulec`, `idelibs/codehelpers/game/adventureruntime.ruleh`
- `splashscreenwidget.cpp` (Build: 5.96.241026)
- Two new native/static regression tests under `development/tests`

## Verification
- Native GCC: Stage 5.94 Trigger reward/dialogue PASS.
- Native GCC: Stage 5.94 generated interaction USE PASS.
- Native GCC: Stage 5.96 single-message vs full conversation PASS.
- Stage 5.96 source/editor/export checks: 10/10 PASS.
- Qt6 toolchain unavailable in this container; **not Qt-compiled or SIDBOX-hardware verified**.
- User's `.sbgm`, `main.c` and project files not modified.
