#!/usr/bin/env python3
"""Stage 5.138: Tilemap ESC/cancel/close cannot silently lose edits."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
cpp = (r / 'gametilemap.cpp').read_text()
hdr = (r / 'gametilemap.h').read_text()
assert 'Build: 5.138.251026' in (r/'splashscreenwidget.cpp').read_text()
assert 'void closeEvent(QCloseEvent *event) override;' in hdr
assert 'SidboxTilemap m_lastCommittedMap;' in hdr
assert 'bool saveCurrentMap();' in hdr
assert 'bool confirmClose(bool forcePrompt);' in hdr
assert 'm_lastCommittedMap = m_map;' in cpp
assert 'if (!forcePrompt && sameTilemap(m_map, m_lastCommittedMap)) return true;' in cpp
assert 'Do you want to save before closing?' in cpp
for button in ('Save', 'No', 'Cancel'):
    assert 'prompt.addButton(tr("%s")' % button in cpp
assert 'prompt.setDefaultButton(cancel);' in cpp
assert 'prompt.setEscapeButton(cancel);' in cpp
assert 'if (prompt.clickedButton() == no) return true;' in cpp
assert 'if (prompt.clickedButton() == save)' in cpp
assert 'if (!saveCurrentMap()) {' in cpp
assert 'The editor will stay open' in cpp
assert 'm_lastCommittedMap = m_map;' in cpp
assert 'm_saveCallback(m_map)' in cpp
assert 'if (!m_closeAlreadyApproved && !confirmClose(false))' in cpp
assert 'event->ignore();' in cpp
assert '!confirmClose(m_escapeCloseRequest)' in cpp
assert 'm_escapeCloseRequest = true;\n        reject();\n        m_escapeCloseRequest = false;' in cpp
p_tmp = cpp.index('if (event->key() == Qt::Key_Escape && m_canvas && m_canvas->temporaryActive)')
p_stamp = cpp.index('finishCollisionStampEdit(false);', p_tmp)
p_close = cpp.index('m_escapeCloseRequest = true;', p_tmp)
assert p_tmp < p_stamp < p_close, 'ESC must cancel pending edits before closing'
assert 'QDialog::closeEvent(event);' in cpp
assert 'connect(m_saveButton, &QPushButton::clicked, this, [this]() {\n        saveCurrentMap();' in cpp
assert 'connect(apply, &QPushButton::clicked, this, &QDialog::accept);' in cpp
assert 'connect(cancel, &QPushButton::clicked, this, &QDialog::reject);' in cpp
print('PASS Stage 5.138 tilemap editor ESC close/save/no/cancel guard')
