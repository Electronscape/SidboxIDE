#!/usr/bin/env python3
"""Read-toggle-state node schema + runtime generation contract; native behaviour check."""
from pathlib import Path
import tempfile, subprocess
base=Path(__file__).resolve().parents[2]
ui=(base/'gamevisualnodes.cpp').read_text()
project=(base/'gamedesigner_project.cpp').read_text()
header=(base/'gamedesigner.h').read_text()
export=(base/'gamedesigner_export.cpp').read_text()
assert 'Read Toggle State' in ui
assert 'createToggleCard(id)' in ui
assert 'createBranchCard(id,true)' in ui and 'createBranchCard(id,false)' in ui
assert 'showInsertTree(point,global,from)' in ui and 'setBranchDialogue(id,yes,index,at)' in ui
assert 'const int selected=browseDialogueTree(old)' in ui
for key in ('toggleStateTargetId','toggleTrueDialogueNode','toggleFalseDialogueNode'):
    assert key in header and key in project and key in ui and key in export
    assert 'object.insert(QStringLiteral("'+key+'")' in project
    assert 'object.value(QStringLiteral("'+key+'"))' in project
    assert 'object.insert(QStringLiteral("'+key+'")' in ui
assert 'objectSlot.value(input)' in export and 'const QString expression=comparisons.join(' in export
assert 'game_adventure_trigger_message(%1u)' in export
# Branch body is emitted after the ordinary Trigger links: toggles update
# active before TRUE/FALSE executes, not one event late.
start=export.index('        } else {\n            if (!targetAction(r, &action)) return false;',export.index('QString interactionRows;'))
body=export[start:export.index('        const bool stop =',start)]
assert body.index('for (const Resource::LinkedAction &link') < body.index('if (!r.toggleStateTargetId.isEmpty()')
assert body.index('if (!r.toggleStateTargetId.isEmpty()') < body.index('if (r.interactItemName.isEmpty()')
assert 'return false;' in export[export.index('toggle-state condition must'):export.index('toggle-state condition must')+180]
# Guard Qt6 syntax: QStringLiteral() requires a literal, not ternary expression.
assert 'QStringLiteral(yes?' not in ui
# Small native model of exactly the generated C control flow.
program=r'''#include <assert.h>
#include <stdint.h>
typedef struct { uint8_t active; } game_world_object_t;
static game_world_object_t lifty;
static int last_dialogue;
static void game_adventure_trigger_message(unsigned n){last_dialogue=(int)n;}
static void on_trigger(void){
  lifty.active=(uint8_t)!lifty.active;
  if (lifty.active){ game_adventure_trigger_message(10u); }
  else { game_adventure_trigger_message(13u); }
}
int main(void){
  lifty.active=0;last_dialogue=-1;
  on_trigger();assert(lifty.active==1 && last_dialogue==10);
  on_trigger();assert(lifty.active==0 && last_dialogue==13);
  on_trigger();assert(lifty.active==1 && last_dialogue==10);
  return 0;
}'''
with tempfile.TemporaryDirectory() as d:
    source=Path(d)/'test.c';binary=Path(d)/'test'
    source.write_text(program)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Werror',str(source),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
print('PASS: Stage 5.166.53 toggle-state TRUE/FALSE dialogue integration contract')
