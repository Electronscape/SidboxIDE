#!/usr/bin/env python3
"""Stage 5.119: source contracts for Game Flow audit, coloured headers,
and GIVE guards; native Adventure runtime behaviour remains unchanged.
The Qt graphical scene needs an actual desktop Qt6 build for visual acceptance.
"""
from pathlib import Path
import hashlib
import re
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
graph=(root/'gamefloweditor.cpp').read_text()
adventure=(root/'gameadventureeditor.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.119.251026' in splash

# The header must fill the full rectangle, not merely the glyph background.
assert 'QRectF(7,0,card->rect().width()-7,60)' in graph
assert 'nodeColour(n.kind,n.problem,theme),0.055' in graph
assert 'cover->setBrush(mix(g.automatic?arrayBackground:groupBackground,' in graph
assert 'subCover->setBrush(mix(nestedBackground,theme.brightText,0.105))' in graph
assert 'QRectF(0,0,child->rect().width(),58)' in graph
assert 'QRectF(0,0,mini->rect().width(),58)' in graph
assert 'QRectF(0,0,width,47)' in graph  # focused Choice drilldown
assert graph.count('setAcceptedMouseButtons(Qt::NoButton);') > 16

# Saved-world reader must respect executable paths only, including legacy data.
for needle in ('completed dialogue node','Fire2 close: gives item (one-time)',
               'Fire2 close: NPC appearance ','closeGiveItem','npcAction%1SpriteId',
               'thoughtBubbleThis','inactive Missing-item branch',
               'has a NEXT thought but closes the conversation',
               'GIVE with no valid requested items','inactive repeated-wrong branches'):
    assert needle in graph,needle
assert graph.index('if (!hasSelectableAnswer)') < graph.index('const int closeGift=') if 'const int closeGift=' in graph else True
assert 'if (needed>=0 && needed<items.size())' in graph
assert 'if (!validRequest)' in graph and 'continue; // generator treats this exchange as inactive' in graph
assert 'for (const QJsonValue &answer:choices)' in graph
assert 'const int closeGift=dialogue.value' not in graph  # legacy-aware non-const fallback

# GIVE editor warns immediately, prevents duplicate requested items, and does
# not stop a disabled exchange being saved just because a stale option is set.
for needle in ('Check GIVE flow:', 'const bool ready=active && required>0;',
               'gate(event.number,ready && kind==QStringLiteral("custom")',
               'gate(repeatEventId,repeat && repeatKind==QStringLiteral("custom")',
               'if(enabled->isChecked() && repeatEnabled->isChecked())',
               'if (selectedCount!=chosen.size())', 'Duplicate GIVE Items',
               'exchangeWarning->setVisible(!issues.isEmpty());'):
    assert needle in adventure,needle

# No game binary C, generated ABI, or TFCard/world format changes.
prior=Path('/mnt/data/ide_251026_stage5118')
for fname in ('gameadventuregen.cpp','gameadventuregen.h',
              'gamefloweditor.h','gameadventureeditor.h'):
    assert hashlib.sha256((root/fname).read_bytes()).digest()==hashlib.sha256((prior/fname).read_bytes()).digest(),fname

with tempfile.TemporaryDirectory(prefix='stage5119-flow-') as temp:
    output=render_adventure_runtime(root,Path(temp))
    tests=root/'development/tests'
    for stem in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=output/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),
                        '-I',str(output),str(output/'adventureruntime.c'),
                        str(tests/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.119: flow audit, full-width headers, GIVE guards and both native thought-bubble tests PASS')
