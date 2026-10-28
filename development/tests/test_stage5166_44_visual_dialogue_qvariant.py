#!/usr/bin/env python3
"""Catch QVariant/QJsonValue toInt API confusion in Visual Nodes (C++17 + source test)."""
from pathlib import Path
import re
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert '#include <QVariant>' in s
assert 'const QVariant selectedData=m_dialogueControls.value(id).picker->currentData();' in s
assert 'int choice=selectedData.isValid() ? selectedData.toInt() : -1;' in s
assert not re.search(r'(?:currentData\(\)|QVariant\s*\(.*?\))\.toInt\(\s*-?\d+\s*\)', s)
assert (lambda v: v and int(v.group(1)) >= 44)(re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text()))

# A minimal signature-faithful analogue of the Qt QVariant API.
# This compiles the *same* validity/conversion expression used by the UI
# and executes it for all three supported statuses. It is NOT a Qt GUI build.
cxx=r'''
struct QVariant {
    int value; bool valid;
    bool isValid() const { return valid; }
    int toInt(bool *ok = nullptr) const { if (ok) *ok=valid; return valid?value:0; }
};
int convert(const QVariant &selectedData) {
    int choice=selectedData.isValid() ? selectedData.toInt() : -1;
    return choice;
}
int main() {
    return (convert({-2,true})==-2 && convert({-1,true})==-1 &&
            convert({7,true})==7 && convert({0,false})==-1) ? 0 : 1;
}
'''
with tempfile.TemporaryDirectory() as td:
    src=Path(td)/'check.cpp';bin=Path(td)/'check'
    src.write_text(cxx)
    subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(src),'-o',str(bin)],check=True)
    subprocess.run([str(bin)],check=True)
print('Stage 5.166.44 QVariant dialogue conversion test PASS')
