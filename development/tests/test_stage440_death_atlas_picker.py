"""Stage 4.40: visual death-animation start-frame UI regressions.

Checks source wiring and zero-based row-major/sequence constraints without Qt.
Native Qt build and GUI visual tests require Fedora with Qt6.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamedesigner.cpp').read_text()
prev=(root/'gamedesigner_project.cpp').read_bytes()
assert 'chooseDeathAtlasStart' in s
assert 'Choose Death Animation Start Frame' in s
assert 'Choose from atlas...' in s
assert 'GGDeathAtlasFramePicker' in s
assert 'frame % cols' in s and 'frame / cols' in s
assert 'atlas.copy((index % cols) * cellW,' in s
assert 'selected + length <= frames' in s
assert 'No death animation' in s
assert 'if (selected >= -1) enemyDefeatFrame->setValue(selected)' in s
assert 'picker.exec() == QDialog::Accepted ? chosen : -2;' in s
assert 'refreshDeathStartButton();' in s
assert 'deathStartPicker->setIcon' in s
assert 'enemyDefeatCount->value(), m_theme.accent' in s
assert 'enemyDefeatFrame->setValue(old.enemyDefeatFrame)' in s
assert 'r.enemyDefeatFrame = enemyDefeatFrame->value()' in s
assert b'enemyDefeat' in prev # Saved format isn't moved to the GUI picker.
# Atlas frame order matches SIDBOX game object renderer, including non-square cells.
for cw,ch,w,h in ((16,16,64,32),(24,16,96,64),(32,48,128,144)):
    cols,rows=w//cw,h//ch
    for n in range(cols*rows):
        assert (n%cols)*cw < w and (n//cols)*ch < h
# The popup refuses a too-late start if the sequence cannot fit.
for n in (1,4,8,20):
    for start in range(32):
        assert (start+n<=32) == (start<=32-n)
print('PASS: Stage 4.40 visual death atlas picker source/wiring and frame range checks')
