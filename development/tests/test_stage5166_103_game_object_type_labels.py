"""Stage 5.166.103: Game Object sidebar must use stable type IDs.

Run: python3 -m unittest discover -s development/tests -p 'test_stage5166_103_*.py'
Source-level coverage; Qt desktop behaviour is checked on the user's machine.
"""
from pathlib import Path
import re
import unittest

SOURCE = (Path(__file__).resolve().parents[2] / "gamedesigner.cpp").read_text()


def object_type_records():
    begin = SOURCE.index('auto *type = new GameComboBox(&dialog);')
    end = SOURCE.index('type->setCurrentIndex', begin)
    return re.findall(r'type->addItem\(tr\("([^\"]+)"\),\s*QStringLiteral\("([^\"]+)"\)\)', SOURCE[begin:end])


def presentation_records():
    begin = SOURCE.index('const QHash<QString, QPair<QString, QString>> typePresentation')
    end = SOURCE.index('typeList->setCurrentRow', begin)
    return re.findall(r'\{QStringLiteral\("([^\"]+)"\),\s*\{QStringLiteral\("([^\"]+)"\),\s*tr\("([^\"]+)"\)\}\}', SOURCE[begin:end])


class GameObjectSidebarMappingTests(unittest.TestCase):
    def test_all_canonical_types_have_one_presentation(self):
        canonical = [obj_id for _label, obj_id in object_type_records()]
        presented = [obj_id for obj_id, _symbol, _label in presentation_records()]
        self.assertEqual(len(canonical), 15)
        self.assertEqual(len(canonical), len(set(canonical)))
        self.assertEqual(len(presented), len(set(presented)))
        self.assertEqual(set(canonical), set(presented))

    def test_important_mismatched_types_are_now_distinct(self):
        names = {obj_id: caption for obj_id, _symbol, caption in presentation_records()}
        self.assertIn('Switchable Decoration', names['decoration_object'])
        self.assertIn('Stompable enemy', names['enemy'])
        self.assertIn('Goto World', names['goto_world'])
        self.assertIn('Save Game Checkpoint', names['save_checkpoint'])
        self.assertIn('Particle Spawner', names['particle_emitter'])
        self.assertNotEqual(names['enemy'], names['goto_world'])

    def test_rows_bind_stable_type_id_not_indexed_label_arrays(self):
        self.assertIn('const QString objectTypeId = type->itemData(n).toString();', SOURCE)
        self.assertIn('typePresentation.constFind(objectTypeId)', SOURCE)
        self.assertIn('item->setData(Qt::UserRole, objectTypeId);', SOURCE)
        self.assertNotIn('const QStringList titles = {tr("Decoration")', SOURCE)
        self.assertIn('Q_ASSERT(typePresentation.size() == type->count());', SOURCE)
        self.assertIn('type->setCurrentIndex(row);', SOURCE)

    def test_underlying_behaviour_is_not_selected_by_display_text(self):
        self.assertIn('const QString behaviour = type->currentData().toString();', SOURCE)
        self.assertIn('enemyCard.panel->setVisible(isEnemy);', SOURCE)
        self.assertIn('gotoCard.panel->setVisible(isGoto);', SOURCE)


if __name__ == '__main__':
    unittest.main()
