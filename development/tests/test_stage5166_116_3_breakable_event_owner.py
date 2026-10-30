"""Regression for ON DESTROY event validation in world-object generation.

The event is not an independently persisted Game Object. It is named by the
real source object's UUID; the graph order check must recognise that object.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[2]
HEADER = (ROOT / "gamevisualgraphlogic.h").read_text()
EXPORT = (ROOT / "gamedesigner_export.cpp").read_text()
SPLASH = (ROOT / "splashscreenwidget.cpp").read_text()


def check_event_reference(event_key, object_ids, event_keys):
    """Python model of the lookup in SidboxVisualLogic::order."""
    return event_key in event_keys or event_key.split(":", 2)[2] in object_ids


class BreakableEventSourceValidation(unittest.TestCase):
    def test_fallback_to_real_source_uuid_exists_in_production(self):
        self.assertIn("const QString sourceId=input.id.section(QLatin1Char(':'),2);", HEADER)
        self.assertIn("!objects.contains(sourceId) && !objects.contains(input.id)", HEADER)
        self.assertNotIn('input.kind==QStringLiteral("event") && !objects.contains(input.id)', HEADER)

    def test_saved_two_input_and_accepts_existing_breakable(self):
        breakable_id = '11111111-2222-4333-8444-555555555555'
        spring_id = 'aaaaaaaa-bbbb-4ccc-8ddd-eeeeeeeeeeee'
        object_ids = {breakable_id, spring_id}
        key = '@event:destroy:' + breakable_id
        self.assertTrue(check_event_reference(key, object_ids, set()))
        self.assertIn(spring_id, object_ids)

    def test_absent_source_does_not_pass(self):
        self.assertFalse(check_event_reference('@event:destroy:missing-id', {'some-other-id'}, set()))

    def test_exporter_keeps_real_one_frame_pulse(self):
        self.assertIn('objectSlot.insert(QStringLiteral("@event:destroy:")+platforms.at(i)->id,', EXPORT)
        self.assertIn('QStringLiteral("(cg_named_event_sources[%1u] & 2u)").arg(i)', EXPORT)
        self.assertIn('SidboxVisualLogic::expression(node,objectSlot,expressionNames)', EXPORT)
        self.assertIn('input.id==QStringLiteral("@event:destroy:")+owner.id', EXPORT)

    def test_splash_version(self):
        self.assertIn('Build: 5.166.116.4.301026', SPLASH)


if __name__ == '__main__':
    unittest.main()
