"""5.166.99 source contract: one IDE palette for every Visual Nodes control.

These tests are static checks, not a Qt rendering/build substitute.
"""
from pathlib import Path

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
sp=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.100.291026' in sp
assert '#include "idetheme.h"' in s
assert 'VisualNodesDialog(const QString &vsgmPath,const IDETheme &theme' in s
assert 'VisualNodesDialog dialog(vsgmPath,theme,parent)' in s
assert 'Q_UNUSED(theme)' not in s
assert 'm_theme(theme)' in s
assert s.count('panel->setStyleSheet(m_controlsStyle);')==7
assert 'operatorPanel->setStyleSheet(m_controlsStyle);' in s
assert 'opCombo->setStyleSheet(m_controlsStyle);' in s
for field in ('panelBackground','inputBackground','windowBackground','editorBackground',
              'accent','border','hover','text','mutedText','selectionBackground','selectionText'):
    assert 'm_theme.'+field in s,field
assert s.count('card->setBrush(m_theme.panelBackground);')==8
assert 'new FlowGroupBox(conversationFlowTitle(root),m_theme.alternateBackground)' in s
assert 'm_view->setBackgroundBrush(m_theme.editorBackground);' in s
assert 'QColor(97,65,129)' in s  # Purple header identity unchanged.
assert 'QColor(34,115,111)' in s # Teal GIVE header identity unchanged.
assert 'QColor(233,177,98)' in s # Amber socket identity unchanged.
for unwanted in ('#293441','#18202c','#523e6e','#664284','#26736e','#e4ccea'):
    assert unwanted not in s,unwanted
print('PASS Stage 5.166.99: all node control surfaces use IDE theme; frames/sockets preserved')
