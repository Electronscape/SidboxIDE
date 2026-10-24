#!/usr/bin/env python3
from pathlib import Path
r=Path(__file__).resolve().parents[2]
files={x:(r/x).read_text() for x in ('gamedesigner.cpp','gamedesigner.h',
 'gamedesigner_project.cpp','gamedesigner_export.cpp','gamefloweditor.cpp',
 'idelibs/codehelpers/game/adventureruntime.rulec',
 'idelibs/codehelpers/game/adventureruntime.ruleh','splashscreenwidget.cpp')}
checks={
 'editor has single/full picker':'Single message (one node' in files['gamedesigner.cpp'] and 'Full conversation (choices' in files['gamedesigner.cpp'],
 'dialogue choice warning':'Dialogue choices on a Trigger' in files['gamedesigner.cpp'],
 'door invisibility hint':'will HIDE it' in files['gamedesigner.cpp'],
 'mode read+write':'object.value(QStringLiteral("interactDialogueMode"))' in files['gamedesigner_project.cpp'] and 'object.insert(QStringLiteral("interactDialogueMode")' in files['gamedesigner_project.cpp'],
 'legacy full conversation':'toString(QStringLiteral("conversation"))' in files['gamedesigner_project.cpp'],
 'generator dispatch':'game_adventure_trigger_message' in files['gamedesigner_export.cpp'],
 'flow labels':'Success → single message' in files['gamefloweditor.cpp'],
 'runtime skip choices':'if (ga_trigger_message_mode==1u) return 0u;' in files['idelibs/codehelpers/game/adventureruntime.rulec'],
 'runtime skip dialogue side effects':'if (ga_trigger_message_mode) {' in files['idelibs/codehelpers/game/adventureruntime.rulec'],
 'build splash':'Build: 5.97.241026' in files['splashscreenwidget.cpp'],
}
for name,good in checks.items():
 assert good,name
print(f'Stage 5.96: {len(checks)} editor/export/runtime checks PASS')
