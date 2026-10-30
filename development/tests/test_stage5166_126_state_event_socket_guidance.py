"""Stage 5.166.126: state/event port semantics displayed without changing runtime data."""
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[2]
NODES=(ROOT/'gamevisualnodes.cpp').read_text()
SPLASH=(ROOT/'splashscreenwidget.cpp').read_text()


def test_enemy_and_trigger_readable_socket_labels():
    assert 'tr("ENEMY STATE / EVENTS")' in NODES
    assert 'tr("STATE: ALIVE")' in NODES
    assert 'tr("STATE: ACTIVE")' in NODES
    assert 'tr("EVENT: ON DEFEAT")' in NODES
    assert 'tr("EVENT: %1").arg(eventLabel(key))' in NODES
    assert 'tr("EVENT: ON ACTIVATE")' in NODES
    assert 'tr("STATE: OFF"):tr("STATE: ON")' in NODES
    assert 'TEAL = STATE (held)' in NODES
    assert 'GOLD = EVENT (pulse)' in NODES
    assert 'ON HIT also pulses on the killing blow.' in NODES


def test_gate_input_classification_and_tooltips():
    assert 'tr("EVENT %1").arg(eventLabel(eventKey(id)))' in NODES
    assert 'tr("STATE %1").arg(m_objects.value(id).name)' in NODES
    assert 'tr("LOGIC %1").arg(id)' in NODES
    assert 'socketColour=kind==QStringLiteral("event")' in NODES
    assert 'label->setToolTip(connected?inputTip:' in NODES
    assert 'card->setToolTip(guidance);' in NODES
    assert 'card->setPen(QPen(guidance.startsWith(tr("CAUTION:"))?' in NODES
    assert 'syncGraphCardSockets(key);' in NODES


def test_guidance_non_blocking_and_inspector_visible():
    assert 'QString graphSocketGuidance(const QJsonObject &node) const {' in NODES
    assert 'if(op==QStringLiteral("not") && eventInput)' in NODES
    assert 'if(op==QStringLiteral("and") && eventInput && stateInput)' in NODES
    assert 'CAUTION: NOT(EVENT) is NOT the opposite of a persistent STATE.' in NODES
    assert 'EVENT + STATE: this AND gate is TRUE only when the event fires' in NODES
    assert 'm_inspectorType->setText(guidance.startsWith(tr("CAUTION:"))?' in NODES
    assert 'm_inspectorType->setToolTip(guidance);' in NODES
    assert 'row(tr("Input guidance"),guidance);' in NODES
    assert 'm_status->setText(guidance);' in NODES
    # Warnings must not turn into an error modal or disconnect valid user wires.
    guidance=NODES[NODES.index('QString graphSocketGuidance('):NODES.index('void syncGraphCardSockets(')]
    assert 'QMessageBox' not in guidance
    # Save IDs and wire routing remain exactly the existing .sbgm contracts.
    for contract in ('@triggerstate:on:', '@triggerstate:off:', '@enemydefeat:',
                     '@event:', 'graphUpdate(key,node);'):
        assert contract in NODES


def test_qt6_regression_source_patterns():
    assert re.search(r'Build: 5\.166\.\d+(?:\.\d+)?\.301026', SPLASH)
    for path in list(ROOT.glob('*.cpp')) + list(ROOT.glob('*.h')):
        assert not re.search(r'\bauto\s*\*\s*\w+\s*=\s*\[',path.read_text(errors='replace')),path
    # Verify new Qt UI calls use known Qt types/overloads: Qt graphics items,
    # QString formatting, labels and QColor/QPen.
    for call in ('new QGraphicsSimpleTextItem(', 'label->setToolTip(',
                 'socket->setPen(QPen(', 'm_inspectorType->setToolTip('):
        assert call in NODES
