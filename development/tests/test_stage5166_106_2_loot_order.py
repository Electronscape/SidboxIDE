"""Stage 5.166.106.2: source-contract checks for sorted stompable loot picker.

The Qt UI still requires a real Qt build and GUI check.
"""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
EDITOR = (ROOT / 'gamedesigner.cpp').read_text()
SPLASH = (ROOT / 'splashscreenwidget.cpp').read_text()

class LootPickerOrdering(unittest.TestCase):
    def test_eligible_first_then_case_insensitive_natural_name_order(self):
        ui = EDITOR[EDITOR.index('const auto refillEnemyLoot ='):EDITOR.index('refillEnemyLoot(old.enemyLootIds);')]
        self.assertIn('a.reason.isEmpty() != b.reason.isEmpty()', ui)
        self.assertIn('return a.reason.isEmpty();', ui)
        self.assertIn('byName.setCaseSensitivity(Qt::CaseInsensitive);', ui)
        self.assertIn('byName.setNumericMode(true);', ui)
        self.assertIn('std::stable_sort(entries.begin(), entries.end()', ui)
        self.assertIn('byName.compare(a.name, b.name) < 0', ui)
        self.assertLess(ui.index('std::stable_sort('), ui.index('new QListWidgetItem(candidate.name'))

    def test_warning_metadata_and_saved_selection_preserved(self):
        ui = EDITOR[EDITOR.index('const auto refillEnemyLoot ='):EDITOR.index('refillEnemyLoot(old.enemyLootIds);')]
        for marker in ('lootIneligibility(candidate)',
                       'if (found.contains(id)) continue;',
                       'tr("This collectable no longer exists.")',
                       'entry->setData(Qt::UserRole, candidate.id);',
                       'entry->setData(Qt::UserRole + 1, candidate.reason);',
                       '[unavailable]',
                       'entry->setIcon(dialog.style()->standardIcon(QStyle::SP_MessageBoxWarning));',
                       'entry->setToolTip(candidate.reason);',
                       'entry->setFlags(entry->flags() & ~Qt::ItemIsSelectable);',
                       'entry->setSelected(selected.contains(candidate.id));'):
            with self.subTest(marker=marker):
                self.assertIn(marker, ui)

    def test_new_build_version(self):
        self.assertIn('Build: 5.166.106.2.291026', SPLASH)

if __name__ == '__main__':
    unittest.main()
