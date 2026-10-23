#!/usr/bin/env python3
"""Stage 5.34.3 static contract for new dialogue Speaker inheritance.

Qt6 UI is unavailable in this runner. This guards the live + Dialogue Node
handler and its top-level-folder logic, not the Qt click behaviour itself.
"""
from pathlib import Path
import re

root=Path(__file__).resolve().parents[2]
src=(root/'gameadventureeditor.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()

handler=re.search(r'QObject::connect\(nodeAdd,&QPushButton::clicked,&dialog,\[&\] \{(.*?)\n    \}\);',src,re.S)
assert handler, 'new dialogue button handler missing'
body=handler.group(1)
assert 'const QString folder=selectedFolder();' in body
assert 'QString speaker=QStringLiteral("NPC");' in body, 'Unfiled fallback altered'
assert 'nodeTree->currentItem()' in body
assert 'QStringLiteral("node")' in body and 'root=root->parent();' in body
assert re.search(r'while\(root && root->parent\(\).*?QStringLiteral\("folder"\).*?root=root->parent\(\);',body,re.S), 'Top-level root traversal missing'
assert 'const QString name=root->text(0).trimmed();' in body
assert 'speaker=name.left(36)' in body
assert 'node.insert("speaker",speaker)' in body
assert 'if(!folder.isEmpty())node.insert("folderId",folder);' in body
assert 'nodes.append(node);' in body
assert 'redrawNodes(nodes.size()-1);refreshNpcNodes();' in body
assert 'Build: 5.34.3.221026' in splash

# Cross-check that editing old nodes remains distinct from adding new ones.
assert 'node.insert("speaker",speaker->text().left(36))' in src
assert src.count('node.insert("speaker",speaker)') == 1
print('PASS Stage 5.34.3: NPC-root speaker inheritance and Unfiled fallback source contract')
