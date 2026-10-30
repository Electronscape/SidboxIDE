"""Compile the real Stage118 activation-event block without Qt headers.

The prior release placed an `else if` after a `for` statement, producing
`else without a previous if` in gamedesigner_export.cpp.
"""
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SRC = (ROOT / 'gamedesigner_export.cpp').read_text()


class TestExporterControlFlow(unittest.TestCase):
    def test_activation_block_compiles_and_checks_watched_trigger(self):
        before = SRC.index('        if(owner.objectType==QStringLiteral("trigger"))\n', SRC.index('QStringList activationEvents;'))
        after = SRC.index('        // Any real named event can own its gate:', before)
        actual_block = SRC[before:after]
        code = r'''
#include <cassert>
#include <string>
#include <vector>
struct QString {
    std::string value;
    QString(const char *s):value(s){}
    QString(std::string s):value(std::move(s)){}
    bool operator==(const QString &other)const{return value==other.value;}
    bool startsWith(const QString &prefix)const{return value.rfind(prefix.value,0)==0;}
    QString mid(size_t pos)const{return QString(value.substr(pos));}
    size_t size()const{return value.size();}
    QString arg(int)const{return *this;}
};
#define QStringLiteral(s) QString(s)
struct Resource {QString objectType;QString id;};
struct EventList {
    std::vector<QString> values;
    void append(const QString &s){values.push_back(s);}
};
int main(){
    Resource trigger{QStringLiteral("trigger"),QStringLiteral("id1")};
    Resource enemy{QStringLiteral("enemy"),QStringLiteral("id2")};
    Resource decoration{QStringLiteral("decoration"),QStringLiteral("id3")};
    std::vector<Resource*> platforms{&trigger,&enemy};
    int nw=2, ownerIndex=1;
    std::vector<QString> graphInputIds{QStringLiteral("@triggerstate:id1")};
    auto evaluate=[&](const Resource &owner){
        EventList activationEvents;
''' + actual_block + r'''
        return activationEvents.values.size();
    };
    assert(evaluate(enemy)==2);        // enemy defeat plus watched Trigger
    assert(evaluate(decoration)==1);   // watched Trigger only
    assert(evaluate(trigger)==2);      // own Trigger plus watched Trigger
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            src = Path(tmp) / 'check.cpp'
            exe = Path(tmp) / 'check'
            src.write_text(code)
            subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
            subprocess.run([str(exe)],check=True)

if __name__ == '__main__': unittest.main()
