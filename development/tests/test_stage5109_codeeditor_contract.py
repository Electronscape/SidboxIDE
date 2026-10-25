#!/usr/bin/env python3
"""Stage 5.109 source checks for Enter, idle suggestions, folded hints.
Qt6 graphical compilation is required for full verification on Fedora.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
source = (root/'codeeditor.cpp').read_text()
header = (root/'codeeditor.h').read_text()
version = (root/'splashscreenwidget.cpp').read_text()
checks = {
    'caret-left indentation, not entire source line':
        'beforeCursor, leadingWhitespace(beforeCursor).size()' in source,
    'idle delay 600ms': 'm_completionDelayTimer->setInterval(600);' in source,
    'typing-only timer gate': 'if (m_completionTypingEdit && !m_resourceMode && hasFocus()' in source,
    'each key stops idle timer': 'm_completionDelayTimer->stop();\n    const QString keyText = event->text();' in source,
    'newlines do not automatically accept completions':
        'Plain Enter must create a line' in source,
    'popup Enter forwarded to editor':
        'QCoreApplication::sendEvent(this, &forwarded);' in source,
    'explicit Ctrl+Enter acceptance': 'if (key->modifiers() == Qt::ControlModifier) {' in source,
    'space/backspace/delete forwarded from popup':
        'key->key() == Qt::Key_Backspace' in source and 'key->key() == Qt::Key_Delete' in source,
    'fold hint drawn on viewport, not document':
        'QPainter painter(viewport());' in source and 'QStringLiteral("[...]")' in source,
    'fold overlay repainted after collapse/expand':
        'viewport()->update(); // Refresh [...] overlay' in source,
    'completion guard declared': 'bool m_completionTypingEdit = false;' in header,
    'splash version': 'Build: 5.109.251026' in version,
}
for name, good in checks.items():
    print(('PASS' if good else 'FAIL'), name)
assert all(checks.values()), 'Stage 5.109 contract failure'
print('PASS Stage 5.109 codeeditor contract')
