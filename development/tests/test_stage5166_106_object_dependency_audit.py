"""Stage 5.166.106 Game Object Properties audit source-contract tests.

These verify that UI and exporter restrictions remain aligned; they cannot
replace compiling the Qt IDE or running it against a real SIDBOX project.
"""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
EDITOR = (ROOT / "gamedesigner.cpp").read_text()
EXPORT = (ROOT / "gamedesigner_export.cpp").read_text()
SPLASH = (ROOT / "splashscreenwidget.cpp").read_text()


class DependencyAudit(unittest.TestCase):
    def test_audit_is_live_and_in_editor(self):
        for fragment in (
            'GGDependencyWarning', 'QStyle::SP_MessageBoxWarning',
            'gatherDependencyIssues', 'refreshDependencyAudit',
            'reviewDependencyIssue', 'QCheckBox::toggled',
            'QComboBox::currentIndexChanged', 'QListWidget::itemSelectionChanged',
            'auditLoading = true;', 'auditLoading = false;',
            'setProperty("auditConflict", true)',
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, EDITOR)

    def test_export_protections_not_relaxed(self):
        for fragment in (
            'breakRewardOwner.contains(id)',
            'enemy.enemyLootIds.size() > 8',
            'r.pickupPersistent || r.pickupKind == 3',
            'droppingPickups.contains(j)',
            'r.pickupAllowEnemyLoot',
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, EXPORT)

    def test_invalid_loot_is_visible_not_silently_dropped(self):
        for fragment in (
            'lootIneligibility', '[unavailable]', 'Missing collectable:',
            'Exclusive quest reward already owned',
            'Keys are unique quest items',
            'Other enemies need this loot template',
            'Ineligible random loot selected',
            'Quest reward already assigned',
            'Reward is already used as ordinary enemy loot',
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, EDITOR)

    def test_other_types_and_live_save_gate(self):
        for fragment in (
            'Music action has no tune',
            'Dropped item switch needs a required item',
            'Destination world no longer exists',
            'Movement spline is missing',
            'Trigger has missing linked targets',
            'Moving platform has no movement path',
            'Conveyor is stationary',
            'Hazard has no stat change',
            'Particle layer mix is overridden',
            'Sprite Stamp overrides animation frames',
            'Quest reward cannot follow a movement spline',
            'reviewDependencyIssue(true)',
            'if (!commitObject()) return;',
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, EDITOR)

    def test_build_incremented(self):
        self.assertIn('Build: 5.166.106.2.291026', SPLASH)


if __name__ == '__main__':
    unittest.main()
