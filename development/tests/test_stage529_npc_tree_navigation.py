"""Source integration regressions for Stage 5.29.

This environment does not provide Qt6, so this is not a substitute for a GUI
compile or user interaction test. It checks that both editor integration paths
stay wired together when they are next refactored.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
designer = (root / 'gamedesigner.cpp').read_text()
designer_header = (root / 'gamedesigner.h').read_text()
adventure = (root / 'gameadventureeditor.cpp').read_text()
adventure_header = (root / 'gameadventureeditor.h').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()

checks = {
    'Sprite [NPC] tag comes from stored NPC sprite ID':
        'm_adventure.value(QStringLiteral("npcs")).toArray()' in designer
        and 'value(QStringLiteral("spriteId")).toString() == r.id' in designer
        and 'title += QStringLiteral("  [NPC]")' in designer,
    'Shift-double-click uses actual Game Objects alias':
        'QApplication::keyboardModifiers() & Qt::ShiftModifier' in designer
        and 'QStringLiteral("gameobject")' in designer
        and 'm_resourceTree->setCurrentItem(alias)' in designer
        and 'm_resourceTree->scrollToItem(alias)' in designer,
    'NPC double-click passes stable sprite ID to Adventure':
        'openAdventureEditor(sprite.id)' in designer
        and 'void SidboxGameDesigner::openAdventureEditor(const QString &focusNpcSpriteId)' in designer
        and 'const QString &focusNpcSpriteId = QString()' in designer_header,
    'NPC tab and row focused by stable ID':
        'if (!focusNpcSpriteId.isEmpty())' in adventure
        and 'sprite->data(Qt::UserRole).toString() != focusNpcSpriteId' in adventure
        and 'tabs->setCurrentWidget(npcPage)' in adventure
        and 'npcs->setCurrentCell(row, 0)' in adventure
        and 'const QString &focusNpcSpriteId = QString()' in adventure_header,
    'NPC tags refreshed when Adventure editor closes':
        'm_adventure = edited;\n    // Refresh tree labels' in designer
        and 'refreshResources();\n    setDirty(true);' in designer,
    'NPC tags preserved during property rename':
        'if (group == QStringLiteral("sprite") || group == QStringLiteral("gameobject"))' in designer
        and 'title += QStringLiteral("  [NPC]")' in designer,
    'Correct stage displayed': 'Build: 5.30.221026' in splash,
}
for label, passed in checks.items():
    print(('PASS' if passed else 'FAIL') + ': ' + label)
assert all(checks.values()), 'Stage 5.29 navigation integration regression'
