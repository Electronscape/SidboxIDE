#!/usr/bin/env python3
"""Stage 5.163: nested world registry directives and invalid spline flow diagnostics.

Run from anywhere: python3 development/tests/test_stage5163_rules_flow_audit.py
Qt6 isn't required for this source/template regression; this reproduces the
strict stack semantics of GameHelperTemplates::renderConditionals().
"""
from itertools import product
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
manager = (root / 'gameworldsnapshot.h').read_text()
renderer = (root / 'gamehelpertemplates.h').read_text()
flow = (root / 'gamefloweditor.cpp').read_text()
assert '#include "gamehelpertemplates.h"' in manager
assert 'GameHelperTemplates::renderConditionals(generated, conditionFlags' in manager
assert 'GameHelperTemplates::renderConditionals(header.readAll(), conditionFlags' in manager
assert 'const QList<QByteArray> bytes = {renderedHeader, renderedSource};' in manager
assert 'content->indexOf(flagEnd' not in manager
assert 'QVector<Frame> stack;' in renderer, 'expected stack-based production renderer'


def render(src: str, flags: dict[str, bool]) -> str:
    """Equivalent control flow to the production renderer, preserving nested IF/ELSE/END."""
    stack = []
    active = True
    output = []
    for index, line in enumerate(src.split('\n'), 1):
        match = re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*', line)
        if match:
            name = match.group(1)
            assert name in flags, f'unknown {name} at line {index}'
            stack.append([active, flags[name], False])
            active = active and flags[name]
        elif line.strip() == '@IDE_ELSE':
            assert stack and not stack[-1][2], index
            stack[-1][2] = True
            active = stack[-1][0] and not stack[-1][1]
        elif line.strip() == '@IDE_END':
            assert stack, index
            active = stack.pop()[0]
        else:
            assert not line.strip().startswith(('@IDE_IF', '@IDE_ELSE', '@IDE_END')), index
            if active:
                output.append(line)
    assert not stack, 'unclosed condition'
    return '\n'.join(output)


def strip_c_comments_strings(src: str) -> str:
    # Retain braces in C only, not in comments, char or string literals.
    return re.sub(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  '', src)


folder = root / 'idelibs/codehelpers/game'
source = (folder / 'gameworlds.rulec').read_text()
header = (folder / 'gameworlds.ruleh').read_text()
assert source.count('@IDE_IF{HAS_PICKUPS}') >= 1
assert source.count('@IDE_IF{HAS_ADVENTURE_RUNTIME}') >= 4
assert source.count('@IDE_IF{HAS_SHARED_PLAYER}') >= 1
for adventure, pickups, shared, physics, title in product((False, True), repeat=5):
    flags = {
        'HAS_ADVENTURE_RUNTIME': adventure,
        'HAS_PICKUPS': pickups,
        'HAS_SHARED_PLAYER': shared,
        'HAS_WORLD_PHYSICS': physics,
        'HAS_PLAYER_VISIBILITY': adventure and shared,
        'HAS_TITLE': title,
        'HAS_MAP': False,
    }
    for label, template in (('source', source), ('header', header)):
        rendered = render(template, flags)
        rendered = rendered.replace('@IDE{WORLD_DECLARATIONS}', '').replace('@IDE{WORLD_RECORDS}', '').replace('@IDE{SAVE_KEY}', '123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}', '')
        assert '@IDE' not in rendered, (flags, label, 'unresolved rule directive')
        body = strip_c_comments_strings(rendered)
        assert body.count('{') == body.count('}'), (flags, label, 'unbalanced braces')
        if label == 'source':
            assert ('#include "gametitle.h"' in rendered) == title, flags
            assert ('uint16_t gameworlds_check(' in rendered) == pickups, flags
            assert ('void gameworlds_before(' in rendered) == physics, flags
            assert ('static uint8_t gameworlds_hud_inventory_kinds[256];' in rendered) == (pickups and adventure), flags
            assert ('else if (item->stat_target == 4u && item->stat_name)' in rendered) == (pickups and shared), flags
        else:
            assert ('uint16_t gameworlds_check(' in rendered) == pickups, flags
            assert ('void gameworlds_before(' in rendered) == physics, flags
            assert ('uint8_t gameworlds_bind_player_physics(' in rendered) == shared, flags

assert 'const bool invalid = pointCount < 2;' in flow
assert 'description,3,invalid);' in flow
assert 'else if (g.nodes.at(g.byId.value(to)).problem)' in flow
assert 'g.missing(w,from,QStringLiteral("valid spline (needs 2+ points)"),spline);' in flow
assert 'g.link(to,from,QStringLiteral("Moves along path"));' in flow
assert 'Build: 5.166.111.1.291026' in (root / 'splashscreenwidget.cpp').read_text()
print('PASS Stage 5.163: 32 world flag configurations x C/H, balanced directives/braces, invalid spline diagnostics')
