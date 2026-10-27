#!/usr/bin/env python3
"""Regression: Qt QJsonArray has at(), not value()."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
s = (root / "gameadventureeditor.cpp").read_text()
assert "QJsonArray choices = node.value(\"choices\").toArray();" in s
assert "while (choices.size() < 3) choices.append(defaultChoices().at(choices.size()));" in s
assert 'QString choiceId=choices.at(i).toObject().value("questChoiceId").toString();' in s
assert not re.search(r"\bchoices\.value\s*\(", s)
assert 'if (!choiceId.isEmpty())c.insert("questChoiceId",choiceId);' in s
assert 'Build: 5.166.12.271026' in (root / "splashscreenwidget.cpp").read_text()
print("PASS Stage 5.165.4: QJsonArray indexed access + stable dialogue ID preservation")
