#!/usr/bin/env python3
"""Regression: Defeat PPB selection must never copy a QDialog (Qt6 issue)."""
from pathlib import Path
import subprocess
import tempfile
ROOT=Path(__file__).resolve().parents[2]
ui=(ROOT/'gamerpguieditors.h').read_text()
assert 'Build: 5.166.21.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
# Dialog-bound callbacks must capture the dialog only via reference, not via
# a [=] lambda that accesses it (the original 5.166.20 Qt6 build failure).
assert 'QObject::connect(chooseAtlas' not in ui
assert 'const int chosen=cgRpgChooseCell(&dialog,image,tile,cells[i]->value())' in ui
assert 'QMessageBox::information(&dialog' in ui
assert 'QObject::connect(pickCells[i],&QPushButton::clicked,&dialog,[&,i]()' in ui
assert 'frame=frame.flipped(orientation)' in ui
assert '.mirrored(flags&1,flags&2)' not in ui
# Compilation model verifies the new [&,i] callback does not attempt to copy
# a deliberately noncopyable QWidget/QDialog.
code='''#include <functional>
struct Dialog { Dialog()=default; Dialog(const Dialog&)=delete; Dialog& operator=(const Dialog&)=delete; };
int main(){Dialog dialog;int i=2;std::function<void()> cb=[&,i](){Dialog* p=&dialog;(void)p;(void)i;};cb();}
'''
with tempfile.TemporaryDirectory() as d:
    src=Path(d)/'test.cpp';exe=Path(d)/'test';src.write_text(code)
    subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS 5.166.21: noncopyable Qt dialog callback and Qt6 frame mirroring')
