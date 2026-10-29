"""Stage 5.166.84.1: compile-safe subclass search in GIVE alignment."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
s=(r / "gamevisualnodes.cpp").read_text()
code=s[s.index("void redrawLinks() {"):s.index("for (QGraphicsPathItem *item:m_lines)",s.index("void redrawLinks() {"))]
assert "findChildren<QComboBox*>()" in code
assert "findChildren<ConversationTreeCombo*>()" not in code
assert "for(QComboBox *combo:panel->findChildren<QComboBox*>())" in code
assert 'combo->property("giveRouteBranch").isValid()' in code
assert "proxy->subWidgetRect(combo)" in code
assert "Build: 5.166.99.291026" in (r / "splashscreenwidget.cpp").read_text()
print("PASS Stage 5.166.84.1 Qt-safe GIVE combo discovery")
