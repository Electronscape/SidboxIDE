#!/usr/bin/env python3
"""Stage 4.17: popup-list theming is central, theme-aware and covers future dialogs."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
theme = (r/'ideglobaltheme.h').read_text()
main = (r/'mainwindow.cpp').read_text()
assert 'combobox-popup:0;' in theme
assert 'class IDEComboPopupThemeFilter final : public QObject' in theme
assert 'QAbstractItemView *view = combo->view();' in theme
assert 'view->setPalette(palette);' in theme
assert 'view->setStyleSheet(combined);' in theme
assert 'view->viewport()->setPalette(palette);' in theme
assert 'QListView::item:selected, QTreeView::item:selected' in theme
assert 'C(m_theme.menuBackground)' in theme
assert 'C(m_theme.text)' in theme
assert 'C(m_theme.alternateBackground)' in theme
assert 'popupWindow->setStyleSheet(frameStyle);' in theme
assert 'event->type() == QEvent::Show' in theme
assert 'qApp->installEventFilter(filter);' in theme
assert 'for (QWidget *widget : QApplication::allWidgets())' in theme
assert 'ideApplyComboPopupTheme(m_theme);' in main
assert 'theme.windowBackground' not in theme[theme.index('inline void ideApplyComboPopupTheme'):]
print('PASS Stage 4.17: central Qt combo popup colour and dynamic-dialog coverage')
