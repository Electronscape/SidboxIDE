# CoderGirl Stage 5.97: Trigger Dialogue Sequences and Wrong-Item Dialogues

Build: `5.97.241026` (24 October 2026)

## Installation

Copy the drop-in ZIP's files into the **IDE source root**, preserving paths. Rebuild the Qt6 IDE. **No replacement `main.c` and no changes to user world files are included.** To use the new modes on SIDBOX, save the edited world, run **Update Game Project**, then rebuild the game, since the new dialogue event hooks are generated into the game.

## New Trigger settings

In **Game Object Properties > Trigger / Switch**, when **Interact with inventory item** is configured:

- **On success: dialogue** uses the existing searchable dialogue folder-tree selector.
- **Dialogue behaviour** now offers **Single message**, **Message sequence**, or **Full conversation**.
- **On wrong item: dialogue** uses a second independent copy of the same folder-tree selector (default **None**).
- **Wrong item: dialogue behaviour** offers exactly the same three modes (default **Single message**).

**Single message**: show only the selected dialogue node's speaker/text. FIRE2 closes it; no choices/actions.

**Message sequence**: show selected node's speaker/text and its *saved choice labels* as navigation prompts. Choosing one follows only that choice's **Next** dialogue node; `Next = None` closes. No item requirements, gifts, take, reply bubble, event actions, one-time choice completion, NPC appearance or quest outcomes execute. Multiple prompts may branch to other message nodes, but they remain navigation-only.

**Full conversation**: retains the existing Adventure conversation engine, including choice actions. The Trigger success or failure itself is committed **before** the dialogue. The editor warns if choice-driven actions may be surprising. In the wrong-item case, the Trigger itself never consumes the offered item or activates the object, but a *deliberately configured full dialogue-choice action* can still change inventory or other game state.

Wrong item still plays its configured wrong-item SFX. With **None**, its previous `That item does not work!` selector hint remains. With a selected wrong-item dialogue, the USE modal is closed and the dialogue opens instead, without losing or consuming the wrong inventory item. After closing it, FIRE2 by the Trigger can open the USE selector again.

## Steve the Doorman example

Create these **Adventure Editor > Dialogue** nodes:

1. `Box / Deposit`: Speaker **Narrator**, text `You place your knickers into the box.`; a choice labelled `Continue...`, **Next** points to node 2. No effects required.
2. `Box / Result`: Speaker **Narrator**, text `Steve lets you past without bothering you.`; a choice labelled `Thank god!`, **Next = None**. No effects required.
3. `Box / Incorrect`: Speaker **Steve**, text `No, that's not what I asked for!` (optional extra prompts/nodes).

In Steve's Trigger, set **On success: dialogue = Box / Deposit**, mode **Message sequence**. Set **On wrong item: dialogue = Box / Incorrect**, mode **Single message** (or **Message sequence** if it has a continuation). The existing required-item, linked-object action, state frames, success/wrong/cancel sounds and one-shot rules stay unchanged.

An existing Stage 5.96 project loads its saved **Full conversation** success mode unchanged. A wrong-item dialogue remains disabled until explicitly configured. The Logic Flow Debugger shows both labelled links.

## Changed source files

- `gamedesigner.cpp`
- `gamedesigner.h`
- `gamedesigner_project.cpp`
- `gamedesigner_export.cpp`
- `gamefloweditor.cpp`
- `idelibs/codehelpers/game/adventureruntime.rulec`
- `idelibs/codehelpers/game/adventureruntime.ruleh`
- `idelibs/codehelpers/game/gameworlditems.rulec`
- `splashscreenwidget.cpp`

## Verification

- Native GCC tests cover: single message, multi-node message navigation, final `Next = None`, no dialogue side effects, wrong-item modal hand-off, no wrong-item consumption or object activation, legacy full conversations, capacity and inactive-state artwork.
- Generated world interaction code path compiled and tested with both wrong and correct items.
- Source checks cover editor controls, saved project fields, export dispatch, world template, graph links and splash build.
- The container has no Qt6 headers/toolchain, so Qt6 compilation and physical STM32 hardware verification are **still required**.
