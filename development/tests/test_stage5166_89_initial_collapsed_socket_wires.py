"""Stage 5.166.89: first-open collapsed dialogue/GIVE output routing.

Regression: before a card was expanded once, its output-port rect Ys were
provisional (often all zero). A nearest-Y lookup therefore sent multiple
wires to one output even though collapsed sockets were visibly separate.
Qt GUI/hardware visual validation is still required.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
s = (root / 'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root / 'splashscreenwidget.cpp').read_text()

redraw = s[s.index('void redrawLinks() {'):s.index('void showDetails(', s.index('void redrawLinks() {'))]
# Each graph route must match the appropriate port by its authoring identity,
# then take the scene centre of THAT item. No nearest-Y fallback is allowed.
for role in ('conversation-output', 'conversation-missing-output',
             'give-anchor', 'exchange-output'):
    start = redraw.index('child->data(0).toString()==QStringLiteral("' + role + '")')
    route = redraw[start:redraw.index('break;', start)]
    assert 'child->data(2).toInt()==' in route, role
    assert 'sceneBoundingRect().center()' in route, role
    assert '->wirePoint(' not in route, role
assert redraw.count('a=port->sceneBoundingRect().center();') == 2
assert 'from=circle->sceneBoundingRect().center()' in redraw
assert 'a=circle->sceneBoundingRect().center()' in redraw

# The compact geometry gives every physical socket its own Y offset even if
# its *expanded* rect() is not available at first load.
card = s[s.index('class NodeCard final'):s.index('class NodeCanvas final')]
assert '14.0+17.0*slot-original.center().y()' in card
assert 'compactOutputs.indexOf(port)' in card

# Live movement (Stage 5.166.88), popup labels and selection must remain.
assert 'void updateLiveWires(' in s
assert 'm_liveWiresByCard[from].append(wire)' in redraw
assert 'applyWireFocus();' in redraw
print('PASS Stage 5.166.89: each first-open collapsed branch routes to its own visible socket')
