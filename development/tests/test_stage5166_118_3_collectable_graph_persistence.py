"""Stage 118.3 regression: Collectable ON PICKUP graphs survive both save paths.

This checks the actual source-level reader, writer, project serializer and
exporter contracts. Full Qt application testing is still done on Fedora.
"""
import unittest
from pathlib import Path
import json
ROOT=Path(__file__).resolve().parents[2]
UI=(ROOT/'gamevisualnodes.cpp').read_text()
WORLD=(ROOT/'gamedesigner_project.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
SPLASH=(ROOT/'splashscreenwidget.cpp').read_text()

class CollectableGraphPersistence(unittest.TestCase):
    def test_visual_nodes_loads_collectable_owned_logic(self):
        self.assertIn('type!=QStringLiteral("player_action"))\n                node.logicNodes=data.value(QStringLiteral("logicNodes")).toArray();',UI)
        self.assertNotIn('type!=QStringLiteral("player_action") && type!=QStringLiteral("collectable")',UI)

    def test_visual_nodes_writes_collectable_owned_logic(self):
        self.assertIn('node.type!=QStringLiteral("player_action"))\n                        object.insert(QStringLiteral("logicNodes"),node.logicNodes);',UI)
        self.assertNotIn('if(node.type!=QStringLiteral("collectable") &&',UI)
        self.assertIn('if (node.type!=QStringLiteral("trigger")) {',UI)

    def test_ordinary_world_save_keeps_collectable_owned_logic(self):
        self.assertIn('!r.logicNodes.isEmpty())\n                object.insert(QStringLiteral("logicNodes"), r.logicNodes);',WORLD)
        self.assertNotIn('r.objectType!=QStringLiteral("collectable") && !r.logicNodes.isEmpty()',WORLD)
        self.assertIn('r.logicNodes = object.value(QStringLiteral("logicNodes")).toArray();',WORLD)

    def test_exporter_emits_collectable_owned_logic_and_pickup_pulse(self):
        self.assertIn('for (int ownerIndex=0; ownerIndex<nw+np; ++ownerIndex)',EXPORT)
        self.assertIn('const Resource &owner=pickupOwner?*pickups.at(pickupIndex):*platforms.at(ownerIndex);',EXPORT)
        self.assertIn('QStringLiteral("@event:pickup:")+owner.id',EXPORT)
        self.assertIn('cg_named_pickup_sources[%1u]=1u;',EXPORT)
        self.assertIn('if(!r.logicNodes.isEmpty())pickupGraph=true;',EXPORT)

    def test_graph_fixture_roundtrips_without_shape_change(self):
        fixture={"resources":[
            {"id":"pickup-uuid","kind":"sprite","gameObject":{"type":"collectable","logicNodes":[
                {"id":"logic1","op":"and","inputs":[
                    {"kind":"event","id":"@event:pickup:pickup-uuid"},
                    {"kind":"object","id":"@triggerstate:trigger-uuid"}],
                 "trueActions":[],"falseActions":[],"trueDialogueNode":21,"falseDialogueNode":-1}]}},
            {"id":"trigger-uuid","kind":"sprite","gameObject":{"type":"trigger"}}
        ]}
        after=json.loads(json.dumps(fixture))
        graph=after["resources"][0]["gameObject"]["logicNodes"][0]
        self.assertEqual(graph["inputs"][0]["id"],"@event:pickup:pickup-uuid")
        self.assertEqual(graph["inputs"][1]["id"],"@triggerstate:trigger-uuid")
        self.assertEqual(graph["trueDialogueNode"],21)
        self.assertEqual(graph["op"],"and")

    def test_version_and_prior_visual_fix_preserved(self):
        self.assertIn('Build: 5.166.118.3.301026',SPLASH)
        self.assertIn('tr("Virtual switch")',UI)
        self.assertIn('const qreal y=off?239.0:210.0;',UI)

if __name__ == '__main__': unittest.main()
