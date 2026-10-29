#!/usr/bin/env python3
"""Regression: QString::toInt accepts bool* not a default integer value.

Qt 6: QString::toInt(bool *ok = nullptr, int base = 10).
QJsonValue::toInt(int defaultValue = 0) is a *different* API.
"""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root/'splashscreenwidget.cpp').read_text()
# Each string-derived preview ID is parsed with the Qt API's bool* output.
assert len(re.findall(r'id\.mid\(QStringLiteral\("@conversation:"\)\.size\(\)\)\.toInt\(&indexOk\)',s))==4
assert not re.search(r'\.mid\(QStringLiteral\("@conversation:"\)\.size\(\)\)\.toInt\(-1\)',s)
# Value-to-int defaults (different overload) remain untouched.
assert 'choice.value(QStringLiteral("next")).toInt(-1)' in s
assert 'choice.value(QStringLiteral("missingNext")).toInt(-1)' in s
assert 'choice.value(QStringLiteral("requires")).toInt(-1)' in s
# No game-generation or gameplay code should be changed by this test.
print('PASS Stage 5.166.75.1 QString::toInt signature regression')
