#!/usr/bin/env python3
"""Regression: do not use Qt's `slots` keyword macro as a C++ identifier."""
from pathlib import Path
import re
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
header=(root/'gameworldsnapshot.h').read_text()
assert 'const auto &resolvedSlots=npc?npcSlots:objectSlots;' in header
assert '!resolvedSlots.contains(id)' in header
assert '.arg(resolvedSlots.value(id))' in header
# Qt's signals/slots macros are enabled by default; no local `slots` variable.
block=header[header.index('auto compileTimeActions='):header.index('if(!compileTimeActions(')]
assert not re.search(r'(?m)^\s*(?:const\s+)?(?:auto|int|bool|QString)\b[^;]*\bslots\b',block), 'Qt macro collides with local name'
# Compiler regression with same Qt macro spelling enabled and the three
# real expressions drawn verbatim from the header.
with tempfile.TemporaryDirectory() as td:
    path=Path(td)/'qt_macro.cpp'
    path.write_text(r'''
#include <string>
#include <unordered_map>
#define slots /* Qt Q_SLOTS keyword */
int main() {
    std::unordered_map<std::string,int> npcSlots{{"actor",3}};
    std::unordered_map<std::string,int> objectSlots{{"gate",7}};
    bool npc=true;
    std::string id="actor";
'''+ '\n'.join('    '+line.strip().replace('QStringLiteral("object:")','"object:"').replace('target.startsWith("object:")','true').replace('const auto &resolvedSlots=npc?npcSlots:objectSlots;','const auto &resolvedSlots=npc?npcSlots:objectSlots;') for line in [
            'const auto &resolvedSlots=npc?npcSlots:objectSlots;',
       ]) + r'''
    if (!resolvedSlots.contains(id)) return 1;
    if (resolvedSlots.at(id)!=3) return 2;
    return 0;
}
''')
    exe=Path(td)/'macro_test'
    subprocess.run(['g++','-std=c++20','-Werror','-Wall','-Wextra',str(path),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.19.1 Qt slots macro regression')
