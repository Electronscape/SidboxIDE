"""Stage 5.166.113.1: guard against Qt 'slots' macro in graph code."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = (ROOT / 'gamevisualnodes.cpp').read_text()

class QtKeywordRegression(unittest.TestCase):
    def test_graph_function_does_not_use_qt_slots_as_identifier(self):
        fragment = SOURCE.split('void syncGraphCardSockets(const QString &key) {', 1)[1].split('void makeGraphCard(', 1)[0]
        self.assertNotRegex(fragment, r'\b(?:slots|signals|emit)\b')
        self.assertIn('const int inputSocketCount=', fragment)
        self.assertIn('i<inputSocketCount', fragment)

    def test_qt_macro_simulation_can_compile_math(self):
        # A lightweight compiler check intentionally defines Qt's `slots` macro.
        # Reproduces the reported error if someone reintroduces `int slots`.
        # Compile the *actual* initializer copied from the production source.
        statement = re.search(r'const int inputSocketCount=.*?;', SOURCE, re.S)
        self.assertIsNotNone(statement)
        sample = r'''
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#define slots
#define QStringLiteral(s) std::string(s)
template<class T> T qMin(T a, T b) { return std::min(a,b); }
template<class T> T qMax(T a, T b) { return std::max(a,b); }
int main() {
    const std::string op = "and";
    const std::vector<int> inputs = {1,2,3};
''' + statement.group(0) + r'''
    assert(inputSocketCount == 4);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            src = Path(d) / 'check.cpp'
            exe = Path(d) / 'check'
            src.write_text(sample)
            subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)], check=True, capture_output=True, text=True)
            subprocess.run([str(exe)], check=True)

if __name__ == '__main__': unittest.main()
