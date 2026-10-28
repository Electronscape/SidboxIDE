#!/usr/bin/env python3
"""Stage 5.166.46: UI and runtime source contract, no Qt GUI claim."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
source = (root / 'gamedesigner.cpp').read_text()
exporter = (root / 'gamedesigner_export.cpp').read_text()

# The two independent UI refresh routes must agree: an ordinary Trigger
# can show dialogue on touch or FIRE2 whether or not it requires an item.
hint = source[source.index('    const auto refreshDialogueHint = [=]() {'):source.index('    connect(interactDialogue,', source.index('    const auto refreshDialogueHint = [=]() {'))]
assert 'behaviour == QStringLiteral("trigger") ||' in hint
assert 'behaviour == QStringLiteral("save_checkpoint") &&' in hint
assert 'interactDialogueMode->setEnabled(canShowSuccessDialogue &&' in hint
fields = source[source.index('    auto enableFields = [=]() {'):source.index('    connect(interactReward,', source.index('    auto enableFields = [=]() {'))]
assert 'const bool canShowSuccessDialogue = isTrigger || soundsForInteraction;' in fields
assert 'interactDialogue->setEnabled(canShowSuccessDialogue);' in fields
assert 'interactDialogueMode->setEnabled(canShowSuccessDialogue &&' in fields
assert 'interactWrongDialogue->setEnabled(soundsForInteraction)' in fields
assert 'interactReward->setEnabled(soundsForInteraction)' in fields
assert 'sfxInteractSuccess->setEnabled(soundsForInteraction)' in fields
assert 'successful inventory USE' in source

# Runtime already supports ordinary trigger dialogue with no item; don't
# modify the runtime or accidentally make checkpoints launch this path.
assert 'if (r.interactItemName.isEmpty() && r.interactDialogueNode >= 0)' in exporter
assert 'game_adventure_trigger_message' in exporter
assert 'game_adventure_trigger_sequence' in exporter
assert 'game_adventure_trigger_dialogue' in exporter
# Logical truth table for the new UI permissions; checkpoint sans item is
# not supported by the existing generator, so remains disabled.
for behaviour,has_item,expect in [
    ('trigger',False,True),('trigger',True,True),
    ('save_checkpoint',False,False),('save_checkpoint',True,True),
    ('enemy',False,False),('enemy',True,False),
]:
    allowed = behaviour=='trigger' or (behaviour=='save_checkpoint' and has_item)
    assert allowed == expect, (behaviour,has_item)
build=re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text())
assert build and int(build.group(1))>=46
print('Stage 5.166.46 Trigger success-dialogue UI contract PASS')
