#!/usr/bin/env python3
"""Stage 5.166.5: prevent the palette control count from exceeding storage.

The 5.166.4 crash happened during JournalDesigner construction. Qt created
five palette buttons but indices[] was declared with only four entries.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / 'gamequestjournaleditor.cpp').read_text()


def assert_palette_bounds(text):
    def size(pattern):
        found = re.search(pattern, text)
        assert found is not None, pattern
        return int(found.group(1))

    indices = size(r'\bint\s+indices\[(\d+)\]')
    buttons = size(r'\bQPushButton\s*\*\s*buttons\[(\d+)\]')
    defaults = re.search(r'\bconst\s+int\s+defaults\[(\d+)\]\s*=\s*\{([^}]*)\}', text)
    assert defaults is not None
    default_count = int(defaults.group(1))
    assert len(defaults.group(2).split(',')) == default_count
    colour_labels = re.search(r'const\s+QStringList\s+labels\s*=\s*\{([^}]*)\}', text)
    assert colour_labels is not None
    labels = colour_labels.group(1).count('tr(')
    # All dynamic colour-control loops (create, load, redraw, signal binding)
    # must iterate over exactly the allocated number of swatches.
    loops = re.findall(r'for\s*\(int\s+i\s*=\s*0\s*;\s*i\s*<\s*(\d+)\s*;\s*\+\+i\)', text)
    assert labels == 5 and indices == buttons == default_count == labels
    assert len([n for n in loops if int(n) == 5]) >= 4
    assert max(int(n) for n in re.findall(r'\bindices\[(\d+)\]', re.sub(r'\bint\s+indices\[\d+\]\s*\{\}', '', text)) if n.isdigit()) < indices
    assert 'outlineColour=indices[4]' in text


# Confirm this test catches the specific regression, not just current values.
try:
    assert_palette_bounds(source.replace('int indices[5]{}', 'int indices[4]{}'))
except AssertionError:
    pass
else:
    raise AssertionError('Regression test failed to detect the 5.166.4 array overrun')

assert_palette_bounds(source)
assert 'Build: 5.166.5.271026' in (root / 'splashscreenwidget.cpp').read_text()
print('PASS Stage 5.166.5 JournalDesigner palette storage/control bounds')
