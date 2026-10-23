#!/usr/bin/env python3
"""Prevent the Stage 5.41.1 World Items @IDE_ELSE parser regression.

The production Qt rule renderer requires @IDE_IF / @IDE_ELSE / @IDE_END
on their *own* lines, and strips the repeatable @IDE_SECTION blocks first.
Check both the structural layout and representative render modes without
needing Qt headers installed on the test machine.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RULES = ROOT / 'idelibs' / 'codehelpers' / 'game'
SECTION = re.compile(r'(?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?')
OPEN = re.compile(r'^\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*$')
FIELD = re.compile(r'@IDE\{([A-Z_][A-Z0-9_]*)\}')


def check_rule(lines, flags, name):
    """Mirror the exact control-directive order in renderConditionals()."""
    stack = []
    output = []
    active = True
    for lineno, line in enumerate(lines.split('\n'), 1):
        match = OPEN.fullmatch(line)
        stripped = line.strip()
        if match:
            condition = flags[match.group(1)]
            stack.append([active, condition, False])
            active = active and condition
        elif stripped == '@IDE_ELSE':
            assert stack and not stack[-1][2], (name, lineno, 'unexpected ELSE')
            stack[-1][2] = True
            active = stack[-1][0] and not stack[-1][1]
        elif stripped == '@IDE_END':
            assert stack, (name, lineno, 'unexpected END')
            active = stack.pop()[0]
        else:
            assert not re.search(r'@IDE_(?:IF\{|ELSE\b|END\b)', line), (
                name, lineno, 'inline or malformed control directive', line)
            if active:
                output.append(line)
    assert not stack, (name, 'unclosed conditional', stack)
    return '\n'.join(output)


def check_file(filename):
    raw = (RULES / filename).read_text()
    sections = dict(SECTION.findall(raw))
    assert len(sections) == raw.count('@IDE_SECTION{'), (filename, 'section parsing')
    base = SECTION.sub('', raw)
    assert '@IDE_SECTION' not in base
    all_src = '\n'.join([base, *sections.values()])
    flags = {name: False for name in re.findall(r'@IDE_IF\{([A-Z_][A-Z0-9_]*)\}', all_src)}
    # Full World Items, empty world, and a pickup-only world.
    for has_items, has_pickups, has_worlds in ((False, False, False),
                                                (True, False, True),
                                                (True, True, False),
                                                (True, True, True)):
        selected = dict(flags)
        selected.update(HAS_ITEMS=has_items, HAS_PICKUPS=has_pickups,
                        HAS_WORLDS=has_worlds)
        rendered = check_rule(base, selected, filename)
        assert not re.search(r'@IDE_(?:IF\{|ELSE\b|END\b)', rendered)
        assert 'gameworlditems_init' in rendered
        if filename.endswith('.rulec'):
            assert ('cg_pickup_permanently_collected' in rendered) == (has_items and has_pickups)
        # Rendering one of the real generated placeholders must not swallow an IF.
        simulated = FIELD.sub(lambda m: {
            'INIT_BODY': '    /* generated object initialisers */\n'
        }.get(m.group(1), '1'), rendered)
        assert not re.search(r'@IDE_(?:IF\{|ELSE\b|END\b)', simulated)
        if has_items:
            if filename.endswith('.rulec'):
                assert '    /* generated object initialisers */\n' in simulated
            if filename.endswith('.rulec'):
                assert '    return 1;' in simulated
        else:
            if filename.endswith('.rulec'):
                assert 'No managed world objects' in simulated
        for label, part in sections.items():
            # Section conditions have their own fields, including IS_PICKUP.
            check_rule(part, dict.fromkeys(flags, True), f'{filename}/{label}')
            check_rule(part, dict.fromkeys(flags, False), f'{filename}/{label}')


if __name__ == '__main__':
    check_file('gameworlditems.rulec')
    check_file('gameworlditems.ruleh')
    print('Stage 5.41.2 world-object rule directives and branches: PASS')
