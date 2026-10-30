"""Stage 5.166.107: real Stompable ON DEFEAT sockets and multi-action runtime.

These tests validate source contracts and correct data flow at build time; actual
Qt GUI drag, C++ compilation and SIDBOX hardware still require manual acceptance.
Run: python3 -m unittest discover -s development/tests -p 'test_stage5166_107_*.py' -v
"""
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[2]
NODE=(ROOT/'gamevisualnodes.cpp').read_text()
DESIGNER=(ROOT/'gamedesigner.cpp').read_text()
PROJECT=(ROOT/'gamedesigner_project.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
HEADER=(ROOT/'gamedesigner.h').read_text()
FLOW=(ROOT/'gamefloweditor.cpp').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
SPLASH=(ROOT/'splashscreenwidget.cpp').read_text()

class EnemyDefeatNodeTests(unittest.TestCase):
    def test_version(self):
        self.assertIn('Build: 5.166.111.1.291026', SPLASH)

    def test_distinct_action_and_state_sockets(self):
        card=NODE[NODE.index('void makeObjectCard('):NODE.index('void setConversationField(', NODE.index('void makeObjectCard('))]
        self.assertIn('setData(0,QStringLiteral("enemy-action-output"))', card)
        self.assertIn('tr("ON DEFEAT")',card)
        self.assertIn('tr("STATE OUTPUT:',card)
        self.assertIn('port->setData(0,QStringLiteral("output"))',card)
        self.assertIn('rect().width()',NODE[NODE.index('class NodeCard final'):NODE.index('class NodeCanvas final')])
        self.assertIn('QStringLiteral("enemy-action-output")',NODE[NODE.index('void updateSocketStates()'):NODE.index('void makeObjectCard(')] if False else NODE)

    def test_drag_to_existing_or_empty_canvas(self):
        self.assertIn('? QStringLiteral("@enemydefeat:")+item->data(1).toString()', NODE)
        self.assertIn('if (isEnemyDefeatOutput(from)) {', NODE)
        self.assertIn('appendConnection(owner,to,defaultPlayerAction(to,QStringLiteral("enable")));',NODE)
        self.assertIn('isEnemyDefeatOutput(from) ||', NODE)
        self.assertIn('enemyOutput?enemyDefeatOwner(from):from,',NODE)
        self.assertIn('objectSource?tr("Read Game Object State..."):',NODE)
        self.assertIn('enemyOutput?tr("Connect Enemy ON DEFEAT to...")',NODE)
        self.assertIn('if ((enemyOutput || eventOutputPort) && object.type==QStringLiteral("npc"))continue;',NODE)

    def test_wires_anchor_to_defeat_port(self):
        render=NODE[NODE.index('void redrawLinks() {'):NODE.index('void showDetails(',NODE.index('void redrawLinks() {'))]
        self.assertIn('node.type==QStringLiteral("enemy")?90:58',render)
        self.assertIn('QColor(108,211,159)',render)
        self.assertIn('node.links.size()',render)
        self.assertIn('isActionSource(node)',render)
        card=NODE[NODE.index('class NodeCard final'):NODE.index('class NodeCanvas final')]
        self.assertGreaterEqual(card.count('QStringLiteral("enemy-action-output")'),4)

    def test_sbgm_roundtrip_and_original_link(self):
        for data in [NODE,PROJECT,EXPORT,DESIGNER]:
            self.assertIn('enemyDefeatExtraActions',data)
        self.assertIn('QVector<LinkedAction> enemyDefeatExtraActions;',HEADER)
        self.assertIn('object.value(QStringLiteral("enemyDefeatExtraActions")).toArray()',PROJECT)
        self.assertIn('object.insert(QStringLiteral("enemyDefeatExtraActions"),links)',PROJECT)
        self.assertIn('data.value(QStringLiteral("enemyDefeatExtraActions")).toArray()',NODE)
        self.assertIn('object.insert(QStringLiteral("enemyDefeatExtraActions"),extras)',NODE)
        self.assertIn('QStringLiteral("targetObjectId"),node.links.isEmpty()',NODE)
        self.assertIn('QStringLiteral("targetAction"),node.links.isEmpty()',NODE)
        self.assertNotIn('enemyDefeatExtraActions',NODE[NODE.index('QJsonObject graphJson() const'):NODE.index('bool saveLayout()')])

    def test_game_object_properties_preserves_multiple_actions(self):
        self.assertIn('const bool multiLinks = isTrigger || behaviour == QStringLiteral("enemy")',DESIGNER)
        self.assertIn('old.enemyDefeatExtraActions:old.triggerExtraActions',DESIGNER)
        self.assertIn('newType==QStringLiteral("trigger") || newType==QStringLiteral("enemy")',DESIGNER)
        self.assertIn('?r.enemyDefeatExtraActions:r.triggerExtraActions;',DESIGNER)
        self.assertIn('currentLinks()',DESIGNER)
        self.assertIn('linkedActionRows->setVisible(multiLinks)',DESIGNER)
        self.assertIn('label->setVisible(multiLinks)',DESIGNER)

    def test_export_dispatch_and_validation(self):
        self.assertIn('for (const Resource::LinkedAction &link : r.enemyDefeatExtraActions)',EXPORT)
        self.assertIn('if (!targetAction(target,&action)) return false;',EXPORT)
        self.assertIn('if (!renderWorldSection(QStringLiteral("ENEMY_DEFEAT_ACTION"), f, &eventActions))',EXPORT)
        self.assertIn('if (r->enemyDefeatExtraActions.size()>(hasPrimary?63:64))',EXPORT)
        self.assertIn('!actionTargetExists(link.objectId)',EXPORT)
        self.assertIn('@IDE_SECTION{ENEMY_DEFEAT_ACTION}',RULE)
        self.assertIn('if (cg_gwi_platforms[@IDE{INDEX}].break_triggered)',RULE)

    def test_decorations_copy_and_flow_debugger(self):
        self.assertIn('!isActionSource(owner) && eventKinds(owner.type).isEmpty()',NODE)
        self.assertIn('object.insert(QStringLiteral("type"),QStringLiteral("decoration_object"))',NODE)
        self.assertIn('r.enemyDefeatExtraActions',DESIGNER)
        self.assertIn('QStringLiteral("enemyDefeatExtraActions")',FLOW)

if __name__=='__main__':unittest.main()
