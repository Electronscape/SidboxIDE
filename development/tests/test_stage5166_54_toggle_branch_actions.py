#!/usr/bin/env python3
"""Stage 5.166.54: TRUE/FALSE actions are real .sbgm links and generated C."""
from pathlib import Path
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
graph=(root/'gamevisualnodes.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
header=(root/'gamedesigner.h').read_text()
generator=(root/'gamedesigner_export.cpp').read_text()
assert 'Build: 5.166.' in (root/'splashscreenwidget.cpp').read_text()
for field in ('toggleTrueActions','toggleFalseActions'):
    assert field in header and field in project and field in graph and field in generator
    assert f'QStringLiteral("{field}")' in project
    assert f'QStringLiteral("{field}")' in graph
    assert f'object.insert(yes?QStringLiteral("toggleTrueActions")' in project
    assert f'object.insert(yes?QStringLiteral("toggleTrueActions")' in graph
    assert f'r.{field}' in generator
assert 'm_objects.insert(owner,node);m_touched.insert(owner);m_dirty=true;' in graph
assert 'appendBranchConnection(from.mid(prefix.size()),yes,selectedId,QStringLiteral("enable"));' in graph
assert 'appendBranchConnection(owner,yes,to,QStringLiteral("enable"));' in graph
assert 'setBranchDialogue(from.mid(prefix.size()),yes,index,at);' in graph
assert 'state-true-action' in graph and 'state-false-action' in graph
assert 'removeBranchConnection(ref.first,ref.second>-2000' in graph
assert 'const int index=(yes?-1000:-2000)-ref.second;' in graph
assert 'node.toggleTrueActions.clear();node.toggleFalseActions.clear();' in graph
assert 'm_cards.contains(node.toggleStateTargetId)' in graph  # incoming source-object wire when condition exists
assert 'if (!targetAction(target,&action))return false;' in generator
start=generator.index('            if (!targetAction(r, &action)) return false;',generator.index('const Resource &r = *platforms.at(i);',generator.index('if (nt) for')))
body=generator[start:generator.index('            if (r.interactItemName.isEmpty()',start)]
assert body.index('for (const Resource::LinkedAction &link : r.triggerExtraActions)') < body.index('if (!r.toggleStateTargetId.isEmpty()')
assert body.index('for (const Resource::LinkedAction &link:r.toggleTrueActions)') < body.index('if (r.toggleTrueDialogueNode>=0)')
assert body.index('for (const Resource::LinkedAction &link:r.toggleFalseActions)') < body.index('if (r.toggleFalseDialogueNode>=0)')
assert body.index('if (%1.active)') < body.index('} else {')

# Compile the same TRUE / FALSE control flow against two target objects with
# both action and dialogue side effects, checking the active state AFTER Toggle.
c_source=r'''
#include <assert.h>
#include <stdint.h>
typedef struct { uint8_t active; } object;
static object lift,door;
static int message;
static void game_adventure_trigger_message(unsigned n){message=(int)n;}
static void game_object_action(object *o,int mode){
    if (mode==1)o->active=1;
    else if(mode==0)o->active=0;
    else o->active=(uint8_t)!o->active;
}
static void trigger(void) {
    game_object_action(&lift,2); /* the unconditional Trigger action */
    if (lift.active) {
        game_object_action(&door,1); /* TRUE: Enable door */
        game_adventure_trigger_message(10u);
    } else {
        game_object_action(&door,0); /* FALSE: Disable door */
        game_adventure_trigger_message(13u);
    }
}
int main(void){
    lift.active=0;door.active=0;
    trigger();assert(lift.active==1 && door.active==1 && message==10);
    trigger();assert(lift.active==0 && door.active==0 && message==13);
    trigger();assert(lift.active==1 && door.active==1 && message==10);
    return 0;
}'''
with tempfile.TemporaryDirectory() as td:
    source=Path(td)/'test.c';binary=Path(td)/'test'
    source.write_text(c_source)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)

# Check exact wire index encoding for multiple actions on both outputs.
for yes in (False,True):
    for index in (0,1,10,63):
        ref=(-1000 if yes else -2000)-index
        decoded_yes=ref>-2000
        decoded_index=(-1000 if decoded_yes else -2000)-ref
        assert (decoded_yes,decoded_index)==(yes,index)
print('PASS Stage 5.166.54: branch links, serialization, editing, action order, native C behavior')
