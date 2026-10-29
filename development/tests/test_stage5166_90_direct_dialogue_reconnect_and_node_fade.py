"""Stage 5.166.90: independent TRUE/FALSE dialogue reconnection and node focus.

This is a source-contract check. Qt mouse/paint integration still needs desktop testing.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
source = (root / 'gamevisualnodes.cpp').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in splash

connect = source[source.index('void addConnection('):source.index('int removeOrphanCard(', source.index('void addConnection('))]
graph = connect[connect.index('if(from.startsWith(QStringLiteral("@graphbranch:")))'):connect.index('if (from.startsWith(QStringLiteral("@stateout:")))')]
assert 'to.startsWith(QStringLiteral("@graph-dialogue:"))' in graph
assert 'selectedDialogueOnCard(to)' in graph
assert 'const QString own=graphDialogueKey(key,yes)' in graph
assert 'int selected=selectedDialogueOnCard(to);' in graph
assert 'selected=browseDialogueTree(-1)' in graph
assert 'if(selected==-1)return' in graph
assert 'setGraphDialogue(key,yes,selected,where)' in graph
assert 'if(m_objects.contains(to))addGraphAction' in graph
assert graph.index('to.startsWith(QStringLiteral("@graph-dialogue:"))') < graph.index('if(m_objects.contains(to))addGraphAction')
assert 'm_dialogueControls.value(to).picker->currentData()' in connect  # State branch too.
assert 'setBranchDialogue(owner,yes,selected,m_cards.value(to)->pos())' in connect
assert 'm_dialogueControls.value(from).picker->currentData()' in connect
assert 'connectExistingDialogue(from,m_cards.value(to)->pos(),selected)' in connect

focus = source[source.index('void applyWireFocus()'):source.index('void updateLiveWires(')]
assert 'QSet<QString> focusedCards=m_multiSelectedCards;' in focus
assert 'emphasisedCards.insert(wire->data(4).toString())' in focus
assert 'emphasisedCards.insert(wire->data(5).toString())' in focus
assert 'card->setOpacity(focused && !related ? 0.24 : 1.0)' in focus
assert 'card->setPen(pen)' in focus
assert 'wire->setOpacity(!focused || active?1.0:0.12)' in focus
assert 'wire->setZValue(active?0.8:0.0)' in focus
assert 'card->setEnabled(false)' not in focus
assert 'm_selectedWireKey.clear();\n        m_selectedCardId=id;' in source
assert 'cardSelected(parent->data(1).toString())' in source
assert 'if (cardSelected)cardSelected(m_from);' not in source
assert 'applyWireFocus();' in source[source.index('void redrawLinks()'):source.index('void showDetails(')]
print('PASS Stage 5.166.90: direct dialogue reattach, safe branch ownership, card opacity, focus and wire regression')
