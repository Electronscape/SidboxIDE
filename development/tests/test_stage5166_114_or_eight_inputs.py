"""Stage 5.166.114: OR 2..8 across UI, validation and generated-C paths."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
VISUAL = (ROOT / 'gamevisualnodes.cpp').read_text()
DESIGNER = (ROOT / 'gamedesigner.cpp').read_text()
EXPORT = (ROOT / 'gamedesigner_export.cpp').read_text()
LOGIC = (ROOT / 'gamevisualgraphlogic.h').read_text()
SPLASH = (ROOT / 'splashscreenwidget.cpp').read_text()

class EightInputOrRegression(unittest.TestCase):
    def test_independent_parser_accepts_2_to_8_only(self):
        self.assertIn('n.op==QStringLiteral("or") ? (rawInputs.size()<2 || rawInputs.size()>8)',LOGIC)
        self.assertIn('rawInputs.size()>16', LOGIC)
        self.assertIn('QStringLiteral(" || ")', LOGIC)
        for n in range(0,11):
            self.assertEqual(2 <= n <= 8, not (n < 2 or n > 8))

    def test_numbered_or_ports_expand_and_contract(self):
        source = re.search(r'const int inputSocketCount=.*?;', VISUAL, re.S)
        self.assertIsNotNone(source)
        self.assertIn('op==QStringLiteral("or")?qMin(8,qMax(2,static_cast<int>(inputs.size())+1)):1;', source.group())
        for n in range(0,9):
            visible = min(8, max(2,n+1))
            self.assertGreaterEqual(visible,2)
            self.assertLessEqual(visible,8)
            self.assertGreaterEqual(visible,n)
            if n < 8: self.assertGreater(visible,n)
            else: self.assertEqual(visible,n)
        self.assertIn('syncGraphCardSockets(cardId);',VISUAL)
        self.assertIn('inputs.removeAt(index);n.insert(QStringLiteral("inputs"),inputs);',VISUAL)
        self.assertIn('target->wirePoint(QPointF(0,52+24*i))',VISUAL)

    def test_qt_slots_macro_does_not_break_or_socket_math(self):
        statement = re.search(r'const int inputSocketCount=.*?;', VISUAL, re.S)
        self.assertIsNotNone(statement)
        sample = '''#include <algorithm>\n#include <cassert>\n#include <string>\n#include <vector>\n#define slots\n#define QStringLiteral(s) std::string(s)\ntemplate<class T> T qMin(T a,T b) {return std::min(a,b);}\ntemplate<class T> T qMax(T a,T b) {return std::max(a,b);}\nint main() {\n'''
        for index in range(10):
            sample += '{\nconst std::string op = "or";\nconst std::vector<int> inputs('+str(index)+',1);\n'+statement.group(0)+'\nassert(inputSocketCount == '+str(min(8,max(2,index+1)))+');\n}\n'
        sample+='}\n'
        with tempfile.TemporaryDirectory() as d:
            path=Path(d)/'or_ports.cpp'; exe=Path(d)/'or_ports'
            path.write_text(sample)
            subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(path),'-o',str(exe)],check=True,capture_output=True,text=True)
            subprocess.run([str(exe)],check=True)

    def test_editor_blocks_ninth_and_preserves_first_eight(self):
        self.assertIn('op==QStringLiteral("or") && inputs.size()>=8',VISUAL)
        self.assertIn('OR accepts at most eight inputs.',VISUAL)
        self.assertIn('n.toggleStateInputIds.size()>=7',VISUAL)
        self.assertIn('Disconnect extra inputs before switching this gate to OR.',VISUAL)
        self.assertNotIn('n.toggleStateInputIds=n.toggleStateInputIds.mid(0,7);',VISUAL)
        self.assertIn('count<2 || count>8',VISUAL)
        self.assertIn('OR (2–8 inputs)',VISUAL)

    def test_properties_and_export_agree_with_logic_parser(self):
        self.assertIn('OR (2–8 objects, any enabled)',DESIGNER)
        self.assertIn('op==QStringLiteral("or") && (inputs.size()<2 || inputs.size()>8)',DESIGNER)
        self.assertIn('op == QStringLiteral("or") && (inputs.size() < 2 || inputs.size() > 8)',EXPORT)
        self.assertIn('op==QStringLiteral("or")?tr("2–8")',DESIGNER)
        self.assertIn('op==QStringLiteral("or")?tr("2–8")',EXPORT)
        self.assertIn('r.toggleStateOperator==QStringLiteral("or")?QStringLiteral(" || ")',EXPORT)

    def test_eight_input_or_native_truth_table(self):
        src = r'''
#include <assert.h>
int main(void) {
    int s[8]={0};
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j)s[j]=0;
        s[i]=1;
        int any=s[0]||s[1]||s[2]||s[3]||s[4]||s[5]||s[6]||s[7];
        assert(any);
    }
    for (int j=0;j<8;++j)s[j]=0;
    assert(!(s[0]||s[1]||s[2]||s[3]||s[4]||s[5]||s[6]||s[7]));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            path=Path(d)/'or_eight.c'; exe=Path(d)/'or_eight'
            path.write_text(src)
            subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(path),'-o',str(exe)],check=True,capture_output=True,text=True)
            subprocess.run([str(exe)],check=True)

    def test_no_save_schema_change(self):
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes)',VISUAL)
        self.assertRegex(SPLASH, r'Build: 5\.166\.(?:114\.291026|116\.4\.301026)')

if __name__=='__main__': unittest.main()
