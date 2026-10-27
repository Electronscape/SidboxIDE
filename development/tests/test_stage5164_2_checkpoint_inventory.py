#!/usr/bin/env python3
"""Stage 5.164.2: checkpoints genuinely share inventory USE and flow links.

Source-contract checks for the Qt exporter/UI; run native Stage 5.94 +
Stage 5.164 C tests for the two underlying runtime paths separately.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gamedesigner.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
flow=(root/'gamefloweditor.cpp').read_text()
items=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'interactItem->setEnabled(isTrigger || behaviour == QStringLiteral("save_checkpoint"));' in ui
assert 'const bool soundsForInteraction = (isTrigger || behaviour == QStringLiteral("save_checkpoint"))' in ui
assert 'interactionType == QStringLiteral("save_checkpoint")' in ui
assert 'triggerPress->setEnabled(isTrigger && !requiresItem);' in ui
assert 'triggerOneShot->setVisible(isTrigger);' in ui
assert 'checkpointHelp->setVisible(behaviour == QStringLiteral("save_checkpoint"));' in ui
assert 'boolValue("INTERACT_ENABLED", (type == QStringLiteral("trigger") ||' in export
assert 'type == QStringLiteral("save_checkpoint")) && !r.interactItemName.isEmpty());' in export
assert export.count('r->objectType != QStringLiteral("save_checkpoint")')>=1
assert export.count('r->objectType!=QStringLiteral("save_checkpoint")')>=1
assert export.count('r.objectType!=QStringLiteral("save_checkpoint")')>=1
assert 'obj->objectType == QStringLiteral("save_checkpoint")) && !obj->interactItemName.isEmpty()' in export
assert 'gameworlds_checkpoint_request(%1u)' in export
assert 'cg_complete_item_interaction(cg_interaction_target,0u)' in items
assert 'cg_run_trigger_actions();' in items
assert 'if (o->type != GAME_OBJECT_TRIGGER || o->trigger_requires_item) continue;' in (root/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
assert 'save_checkpoint_status=gameworlds_save_slot(slot)' in world
assert 'QStringLiteral("Inventory USE → Save Game")' in flow
assert 'if (type==QStringLiteral("trigger") || type==QStringLiteral("save_checkpoint"))' in flow
assert 'Build: 5.166.12.271026' in (root/'splashscreenwidget.cpp').read_text()
print('PASS Stage 5.164.2: checkpoint inventory USE, callbacks, flow, slot-save handoff')
