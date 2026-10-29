#!/usr/bin/env python3
"""Stage 5.166.77 destination labels: UI/source contracts, no Qt runtime available."""
from pathlib import Path

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version
start=s.index('void makeConversationCard(')
end=s.index('void rebuildConversationFlow()',start)
card=s[start:end]
assert 'destination.value(QStringLiteral("speaker")).toString().simplified()' in card
assert 'destination.value(QStringLiteral("text")).toString().simplified()' in card
assert 'tr("#%1 | %2: %3")' in card
assert 'next->addItem(label,target)' in card  # stored integer destination unchanged
assert 'next->addItem(tr("Close conversation"),-1)' in card
assert 'next->setItemData(next->count()-1,' in card
assert 'Qt::ToolTipRole' in card
assert 'next->chooseDestination=' in card
assert 'browseConversationDestination(current,chosen)' in card
assert 'class ConversationTreeCombo final : public QComboBox' in s
assert 'browser.setWindowModality(Qt::ApplicationModal)' in s
assert 'next->setMaximumWidth(115)' not in card
assert 'next->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon)' in card
assert 'nextLine->addWidget(next,1)' in card
assert 'next->setCurrentIndex(qMax(0,next->findData(selected)))' in card
assert 'next->currentData().toInt()' in card
assert 'setConversationAnswer(index,option,QStringLiteral("next")' in card
assert 'if(selected>=m_dialogues.size())' in card
assert 'MISSING dialogue #%1' in card
assert 'if(neededHeight>card->rect().height())' in card
assert 'void openConversationInAdventure(' in s
# Both normal and alternate item-required preview paths follow existing IDs.
assert 'a=port->sceneBoundingRect().center();' in s  # exact first-open sockets
assert 'const int next=choice.value(QStringLiteral("next")).toInt(-1)' in s
assert 'const int missing=choice.value(QStringLiteral("missingNext")).toInt(-1)' in s
print('PASS destination labels, full-width dropdown, unmodified numeric IDs, flow preview')
