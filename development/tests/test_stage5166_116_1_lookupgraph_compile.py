"""Stage 116.1 regression: event-to-logic lookupGraph needs 3 arguments."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = (ROOT / 'gamevisualnodes.cpp').read_text()

class LookupGraphCompileHotfix(unittest.TestCase):
    def test_member_declaration_and_call_agree(self):
        self.assertIn(
            'bool lookupGraph(const QString &key,QString *owner,int *index,QJsonObject *found=nullptr) const',
            SOURCE)
        self.assertIn('if(lookupGraph(to,&graphOwner,nullptr) && graphOwner!=eventOwner(from))', SOURCE)
        self.assertNotIn('lookupGraph(to,&graphOwner)', SOURCE)

    def test_call_compiles_with_real_member_signature(self):
        call = 'lookupGraph(to,&graphOwner,nullptr)'
        self.assertIn(call, SOURCE)
        cpp = r'''
#include <string>
using QString=std::string;
struct QJsonObject {};
struct Example {
 bool lookupGraph(const QString &,QString *owner,int *,QJsonObject * = nullptr) const {
   *owner="other"; return true;
 }
 bool eventToGraph(const QString &to, const QString &eventOwnerName) const {
   QString graphOwner;
   if(LOOKUP_CALL && graphOwner!=eventOwnerName) return true;
   return false;
 }
};
int main(){Example e; return e.eventToGraph("object", "enemy") ? 0 : 1;}
'''.replace('LOOKUP_CALL', call)
        with tempfile.TemporaryDirectory() as tmp:
            src = Path(tmp) / 'check.cpp'
            exe = Path(tmp) / 'check'
            src.write_text(cpp)
            subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Werror',
                            str(src), '-o', str(exe)], check=True, capture_output=True)
            subprocess.run([str(exe)], check=True, capture_output=True)

if __name__ == '__main__':
    unittest.main()
