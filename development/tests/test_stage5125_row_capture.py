#!/usr/bin/env python3
"""Stage 5.125: prevent copying a noncopyable QDialog in Trigger row callbacks."""
from pathlib import Path
import difflib
import subprocess
import tempfile

root = Path(__file__).resolve().parents[2]
current = (root / 'gamedesigner.cpp').read_text()
prior = (Path('/mnt/data/ide_251026_stage5124') / 'gamedesigner.cpp').read_text()
start = current.index('auto insertLink = [=](int row, const Resource::LinkedAction &link)')
end = current.index('auto reloadLinks = [=]()', start)
section = current[start:end]
assert '&dialog' not in section, 'insertLink must not capture stack QDialog by copy'
for signal in ('rowUp,&QToolButton::clicked', 'rowDown,&QToolButton::clicked', 'rowDelete,&QPushButton::clicked'):
    assert section.count(f'connect({signal},linkedActionRows,[=]()') == 1, signal
    assert f'connect({signal},&dialog,[=]()' not in section, signal
assert 'Build: 5.125.251026' in (root / 'splashscreenwidget.cpp').read_text()

# This corrective stage must change only the three callback contexts.
changed = list(difflib.unified_diff(prior.splitlines(), current.splitlines()))
removed = [s[1:] for s in changed if s.startswith('-') and not s.startswith('---')]
added = [s[1:] for s in changed if s.startswith('+') and not s.startswith('+++')]
assert len(removed) == len(added) == 3, (removed, added)
for a, b in zip(removed, added):
    assert a.replace('&dialog', 'linkedActionRows') == b, (a, b)

# A small standalone C++ compile check: nested click handlers using a
# noncopyable dialog remain copy-constructible when context is an existing
# pointer instead of referring to the dialog in the captured lambda.
code = r'''
#include <type_traits>
struct QDialog { QDialog() = default; QDialog(const QDialog &) = delete; };
struct Table {};
int main() {
    QDialog dialog;
    Table table;
    Table *linkedActionRows = &table;
    auto moveLink = [=](int, int) {};
    auto deleteLink = [=](int) {};
    auto insertLink = [=](int) {
        auto rowUp = [=]() { moveLink(0, -1); (void)linkedActionRows; };
        auto rowDown = [=]() { moveLink(0, 1); (void)linkedActionRows; };
        auto rowDelete = [=]() { deleteLink(0); (void)linkedActionRows; };
        (void)rowUp; (void)rowDown; (void)rowDelete;
    };
    static_assert(std::is_copy_constructible_v<decltype(insertLink)>);
    insertLink(0);
    (void)dialog;
}
'''
with tempfile.TemporaryDirectory(prefix='stage5125-') as temp:
    src = Path(temp) / 'capture.cpp'
    binary = Path(temp) / 'capture'
    src.write_text(code)
    subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Werror',
                    '-pedantic', str(src), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
print('Stage 5.125 Qt dialog capture regression: PASS')
