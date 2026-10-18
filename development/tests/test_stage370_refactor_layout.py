"""Stage 3.70: Qt-free safety checks for the MainWindow modularisation.

Run from any working directory: python development/tests/test_stage370_refactor_layout.py
Qt Creator is still required for a full IDE compile/UI smoke test.
"""
from pathlib import Path
import hashlib
import json
import re

root = Path(__file__).resolve().parents[2]
manifest = json.loads((root / 'development/tests/stage370_refactor_manifest.json').read_text())
cmake = (root / 'CMakeLists.txt').read_text()
mainwindow = (root / 'mainwindow.cpp').read_text()
all_files = {p.name: p.read_text() for p in root.glob('mainwindow*.cpp')}
assert len(manifest) == 50, len(manifest)

for method, record in manifest.items():
    owner = record['file']
    assert owner in all_files, owner
    assert len(re.findall(r'^\s*' + re.escape(owner) + r'\s*$', cmake, re.M)) == 1, owner
    text = all_files[owner]
    if method == 'editorTabIconForFile':
        start = re.search(r'(?m)^QIcon editorTabIconForFile\(', text)
    else:
        start = re.search(r'(?m)^[^\n]*\bMainWindow::' + re.escape(method) + r'\s*\(', text)
    assert start, f'{method} definition missing from {owner}'
    brace = text.find('{', start.end())
    assert 0 <= brace - start.start() < 700, (method, 'body opening')
    close = re.search(r'(?m)^}[ \t]*$', text[brace:])
    assert close, (method, 'body closing')
    body = text[start.start():brace + close.end()]
    assert hashlib.sha256(body.encode()).hexdigest() == record['sha256'], method
    if method == 'editorTabIconForFile':
        assert not re.search(r'(?m)^QIcon editorTabIconForFile\(', mainwindow)
    else:
        assert not re.search(r'(?m)^[^\n]*\bMainWindow::' + re.escape(method) + r'\s*\(', mainwindow), method
        assert sum(len(re.findall(r'(?m)^[^\n]*\bMainWindow::' + re.escape(method) + r'\s*\(', content))
                   for content in all_files.values()) == 1, method

assert '    mainwindow_uiicons.h\n' in cmake
assert '#include "mainwindow_uiicons.h"' in mainwindow
assert 'const qint64 largeSourceThreshold = 2048LL * 1024LL;' in mainwindow
assert (root / 'gamedesigner_project.cpp').exists()
assert (root / 'gametilemapmodel.cpp').exists()
assert 'gamedesigner_project.cpp' in cmake
assert 'gametilemapmodel.cpp' in cmake
print('PASS: Stage 3.70 — 49 moved MainWindow methods + shared icon function, exact bodies, unique definitions and build registration.')
