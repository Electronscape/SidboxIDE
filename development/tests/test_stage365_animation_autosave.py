"""Static integration checks for the Stage 3.65 editor save workflow.
Qt6 must still be compiled and tested interactively on the target machine.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
editor = (root / 'gameanimationeditor.cpp').read_text()
designer = (root / 'gamedesigner.cpp').read_text() + (root / 'gamedesigner_export.cpp').read_text()
header = (root / 'gameanimationeditor.h').read_text()

assert 'm_defaultHeaderFile(defaultHeaderFile)' in editor
assert 'if (writeDocument() && offerHeaderUpdate()) accept();' in editor
assert 'QMessageBox::Yes | QMessageBox::No' in editor
assert 'if (!saveHeader(m_defaultHeaderFile)) return false;' in editor
assert 'QSaveFile out(path)' in editor
assert 'm_defaultHeaderFile.isEmpty()' in editor
assert 'const QString &defaultHeaderFile' in header
assert 'gameanimations/player_anim.h' in designer
assert 'resource.name.trimmed().compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0' in designer
assert 'resource.id' in designer
assert 'Save Animations, then YES' in designer
print('Stage 3.65 animation save/opt-in generated header source wiring: PASS')
