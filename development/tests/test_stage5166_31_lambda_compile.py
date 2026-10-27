#!/usr/bin/env python3
"""Guard against deducing a pointer from lambda closure syntax in IDE C++ files."""
from pathlib import Path
import subprocess
import tempfile
import re

root=Path(__file__).resolve().parents[2]
ui=(root/'gamerpguieditors.h').read_text()
assert 'auto selectMode=[&](bool flags){' in ui
assert 'auto *selectMode=[&]' not in ui
assert 'selectMode(false);' in ui
assert 'selectMode(true);' in ui

# Unlike a Qt-only smoke check, this check runs on every build host.
# It catches the exact Stage 5.166.30 error and same-line variations.
pattern=re.compile(r'\bauto\s*\*\s*\w+\s*=\s*\[',re.M)
files=[p for ext in ('*.cpp','*.h','*.hpp','*.cc') for p in root.rglob(ext)
       if 'build' not in p.relative_to(root).parts and '.git' not in p.relative_to(root).parts]
for filename in files:
    match=pattern.search(filename.read_text(errors='replace'))
    assert not match, f'{filename.name}: lambda closure wrongly assigned to auto* at {match.start()}'

sample=r'''#include <cassert>
int main() {
    bool paint=true,flag=false;
    auto selectMode=[&](bool flags){paint=!flags;flag=flags;};
    selectMode(true);
    assert(!paint && flag);
    selectMode(false);
    assert(paint && !flag);
}
'''
with tempfile.TemporaryDirectory(prefix='cg516631_lambda_') as folder:
    cpp=Path(folder)/'check.cpp'
    exe=Path(folder)/'check'
    cpp.write_text(sample)
    subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',
                    '-pedantic-errors',str(cpp),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.31 C++ lambda compile and source audit')
