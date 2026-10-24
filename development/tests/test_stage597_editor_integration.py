#!/usr/bin/env python3
"""Verify the IDE, save format, export, flow map and runtime share the same modes."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
files={k:(r/k).read_text() for k in (
 'gamedesigner.cpp','gamedesigner.h','gamedesigner_project.cpp',
 'gamedesigner_export.cpp','gamefloweditor.cpp',
 'idelibs/codehelpers/game/adventureruntime.rulec',
 'idelibs/codehelpers/game/adventureruntime.ruleh',
 'idelibs/codehelpers/game/gameworlditems.rulec','splashscreenwidget.cpp')}
checks={
 'new message-sequence mode in UI':'Message sequence (continue prompts, no actions)' in files['gamedesigner.cpp'],
 'wrong item uses tree':'auto *interactWrongDialogue = createGameDialogueTreeCombo' in files['gamedesigner.cpp'],
 'wrong item has independent mode':'interactWrongDialogueMode->setCurrentIndex' in files['gamedesigner.cpp'],
 'wrong selection saved':'r.interactWrongDialogueNode = interactWrongDialogue->currentData().toInt()' in files['gamedesigner.cpp'],
 'wrong mode saved':'r.interactWrongDialogueMode = interactWrongDialogueMode->currentData().toString()' in files['gamedesigner.cpp'],
 'legacy success defaults to full':'toString(QStringLiteral("conversation"))' in files['gamedesigner_project.cpp'],
 'missing wrong defaults off':'toInt(-1)' in files['gamedesigner_project.cpp'],
 'saved wrong node':'object.insert(QStringLiteral("interactWrongDialogueNode")' in files['gamedesigner_project.cpp'],
 'saved wrong mode':'object.insert(QStringLiteral("interactWrongDialogueMode")' in files['gamedesigner_project.cpp'],
 'validates wrong node':'wrong-item dialogue node no longer exists' in files['gamedesigner_export.cpp'],
 'success dispatch supports sequence':'r.interactDialogueMode==QStringLiteral("sequence")' in files['gamedesigner_export.cpp'],
 'wrong dispatch supports sequence':'r.interactWrongDialogueMode==QStringLiteral("sequence")' in files['gamedesigner_export.cpp'],
 'exports wrong dialogue actions':'INTERACT_WRONG_DIALOGUE_ACTIONS' in files['gamedesigner_export.cpp'],
 'world USE includes wrong hook':'@IDE{INTERACT_WRONG_DIALOGUE_ACTIONS}' in files['idelibs/codehelpers/game/gameworlditems.rulec'],
 'wrong sound still fires':'gameworlditems_interaction_sound(0u)' in files['idelibs/codehelpers/game/gameworlditems.rulec'],
 'no side effects in text navigation':'if (ga_trigger_message_mode==2u) {' in files['idelibs/codehelpers/game/adventureruntime.rulec'],
 'wrong dialogue survives callback':'else if (ga_state==1u)' in files['idelibs/codehelpers/game/adventureruntime.rulec'],
 'sequence runtime API':'uint8_t game_adventure_trigger_sequence(uint16_t node)' in files['idelibs/codehelpers/game/adventureruntime.ruleh'],
 'wrong graph connection':'Wrong item → ' in files['gamefloweditor.cpp'],
 'success graph connection':'Success → message sequence' in files['gamefloweditor.cpp'],
 'version':'Build: 5.97.241026' in files['splashscreenwidget.cpp']
}
for name,ok in checks.items():
 assert ok,name
print(f"Stage 5.97: {len(checks)} editor/export/graph checks PASS")
