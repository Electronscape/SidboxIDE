"""Regression coverage: Stompable STATE as an autonomous independent DAG input.

Static integration/source checks plus a native C event/active-state truth table.
Full Qt compilation and SIDBOX hardware remain manual checks.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[2]
NODE=(ROOT/'gamevisualnodes.cpp').read_text()
WORLD=(ROOT/'gamedesigner_project.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
DESIGNER=(ROOT/'gamedesigner.cpp').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
SPLASH=(ROOT/'splashscreenwidget.cpp').read_text()
class EnemyStateLogic(unittest.TestCase):
    def test_version(self):
        self.assertIn('Build: 5.166.113.291026',SPLASH)

    def test_own_enemy_graph_no_trigger(self):
        self.assertIn('if (m_objects.value(source).type==QStringLiteral("enemy"))return source;',NODE)
        self.assertIn('m_objects.value(who).type!=QStringLiteral("enemy")',NODE)
        self.assertIn('createGraphLogic(from,at,selectedId.mid',NODE)
        self.assertIn('if(to.startsWith(QStringLiteral("@graph:"))) {addGraphInput(from,to);return;}',NODE)
        self.assertIn('if(node.type!=QStringLiteral("trigger") && node.type!=QStringLiteral("enemy") &&',NODE)
        self.assertIn('if(trigger.type!=QStringLiteral("trigger") && trigger.type!=QStringLiteral("enemy") &&',NODE)

    def test_save_and_reload_enemy_graphs_all_paths(self):
        self.assertIn('if (type==QStringLiteral("enemy") || type==QStringLiteral("lift"))\n                node.logicNodes=data.value',NODE)
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes)',NODE)
        self.assertIn('r.objectType==QStringLiteral("lift"))\n                object.insert(QStringLiteral("logicNodes"), r.logicNodes)',WORLD)
        self.assertIn('candidate.objectType!=QStringLiteral("enemy")',DESIGNER)
        self.assertIn('hasIncomingGraph |= !ownTrigger;',DESIGNER)
        self.assertIn('owner.logicNodes.replace(index,node);',DESIGNER)

    def test_validator_and_exporter(self):
        self.assertIn('r->objectType==QStringLiteral("enemy") || r->objectType==QStringLiteral("lift")',EXPORT)
        self.assertIn('owner.objectType!=QStringLiteral("enemy") &&',EXPORT)
        self.assertIn('for (int ownerIndex=0; ownerIndex<nw; ++ownerIndex)',EXPORT)
        self.assertIn('SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)',EXPORT)
        self.assertIn('GRAPH_INITIAL_SYNC', EXPORT)
        self.assertIn('HAS_ENEMY_STATE_LOGIC',EXPORT)
        self.assertLess(EXPORT.index('QStringList graphInputIds=graphInputs.values();'),EXPORT.index('for (const QString &enemyId:graphInputIds)'))

    def test_enemy_event_executes_graph_post_actions_once(self):
        self.assertLess(RULE.index('@IDE{WORLD_EVENT_ACTIONS}'),RULE.index('if(cg_defeat_logic_event) {'))
        self.assertIn('if(cg_defeat_logic_event) {\n        cg_run_trigger_actions();',RULE)
        self.assertIn('cg_enemy_logic_event_handled=1u;',RULE)
        self.assertIn('cg_enemy_logic_event_handled=0u;',RULE)
        self.assertIn('!cg_enemy_logic_event_handled',EXPORT)
        self.assertIn('cg_gwi_platforms[%1].break_triggered',EXPORT)
        self.assertIn('for(const Resource::LinkedAction &action:enemy.enemyDefeatExtraActions)',EXPORT)
        self.assertIn('if(graphInputs.contains(action.objectId))modifiesInput=true;',EXPORT)
        self.assertIn('if(modifiesInput)defeatWatchIndexes.insert(enemyIndex);',EXPORT)

    def test_native_two_enemy_and_not(self):
        program=r'''
#include <assert.h>
#include <stdint.h>
static uint8_t run_logic(uint8_t alive_a, uint8_t alive_b, uint8_t defeat_a, uint8_t defeat_b) {
    const uint8_t run = !!(defeat_a || defeat_b);
    if(!run)return 255u;
    const uint8_t any_alive = !!(alive_a || alive_b); // OR node
    return !any_alive; // NOT node: both are defeated
}
int main(void) {
    assert(run_logic(1,1,0,0)==255u); /* no event */
    assert(run_logic(0,1,1,0)==0u);   /* one defeated */
    assert(run_logic(0,0,0,1)==1u);   /* both defeated */
    assert(run_logic(0,0,0,0)==255u); /* don't re-trigger every frame */
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            source=Path(tmp)/'enemy_logic.c';source.write_text(program)
            out=Path(tmp)/'enemy_logic'
            subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(out)],check=True)
            subprocess.run([str(out)],check=True)
if __name__=='__main__':unittest.main()
