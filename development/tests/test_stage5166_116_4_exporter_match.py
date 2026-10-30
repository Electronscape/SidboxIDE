"""Ensure Breakable ON DESTROY logic is accepted by exporter, not a stale Stage 114 build."""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
EXPORT = (ROOT / 'gamedesigner_export.cpp').read_text()
GRAPH = (ROOT / 'gamevisualgraphlogic.h').read_text()
SPLASH = (ROOT / 'splashscreenwidget.cpp').read_text()

class MatchedBreakableExporter(unittest.TestCase):
    def test_old_arrival_only_error_removed(self):
        self.assertNotIn('Invalid ON ARRIVAL logic input', EXPORT)
        self.assertIn('input.id==QStringLiteral("@event:destroy:")+r->id', EXPORT)
        self.assertIn('input.id==QStringLiteral("@event:hit:")+r->id', EXPORT)
        self.assertIn('r->objectType==QStringLiteral("breakable")', EXPORT)

    def test_event_uuid_and_runtime_pulse(self):
        self.assertIn('objectSlot.insert(QStringLiteral("@event:destroy:")+platforms.at(i)->id', EXPORT)
        self.assertIn('QStringLiteral("(cg_named_event_sources[%1u] & 2u)").arg(i)', EXPORT)
        self.assertIn('input.id==QStringLiteral("@event:destroy:")+owner.id', EXPORT)
        self.assertIn('if(wantedEvents)', EXPORT)
        self.assertIn('!objects.contains(sourceId) && !objects.contains(input.id)', GRAPH)

    def test_new_diagnostics_reports_actual_event(self):
        self.assertIn("unsupported event input '%3'", EXPORT)
        self.assertIn('which does not belong to this %4', EXPORT)

    def test_splash(self):
        self.assertIn('Build: 5.166.116.4.301026', SPLASH)

if __name__ == '__main__':
    unittest.main()
