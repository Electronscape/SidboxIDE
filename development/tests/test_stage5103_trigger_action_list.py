#!/usr/bin/env python3
"""Stage 5.103 action-list integration and native SIDBOX rule semantics.

Qt is not installed in this test container. The tests inspect the codegen
pipeline and compile the unchanged action template as actual C statements.
"""
from pathlib import Path
import tempfile, subprocess, re
base=Path(__file__).resolve().parents[2]
read=lambda p:(base/p).read_text()
source=read('gamedesigner_export.cpp')
designer=read('gamedesigner.cpp')
project=read('gamedesigner_project.cpp')
flow=read('gamefloweditor.cpp')
header=read('gamedesigner.h')
assert 'QVector<LinkedAction> triggerExtraActions' in header
for token in ('addLinkedAction','removeLinkedAction','upLinkedAction','downLinkedAction','currentLinks()','reloadLinks()'):
    assert token in designer,token
assert 'if (newType==QStringLiteral("trigger")) {' in designer
assert 'r.triggerExtraActions.clear();' in designer
assert 'triggerExtraActions' in flow
assert 'triggerExtraActions' in project and 'links.append(QJsonObject' in project
assert 'link.objectId = importById(link.objectId)' in designer
assert 'checkId(link.objectId)' in designer
assert 'if (!targetAction(target, &action)) return false;' in source
assert 'if (link.objectId == r->id || !objectSlot.contains(link.objectId)' in source
# The generator must execute the primary action then each additional one.
section=source[source.index('if (nt) for (int i = 0; i < nw; ++i)'):]
assert section.index('if (!targetAction(r, &action))') < section.index('for (const Resource::LinkedAction &link : r.triggerExtraActions)')
assert section.index('for (const Resource::LinkedAction &link : r.triggerExtraActions)') < section.index('const bool stop =')
# Ensure the old key/enemy handling is not rerouted through trigger lists.
assert 'auto targetAction = [&](const Resource &r, QString *out)' in source
assert 'oldStyleLinks = isKey || behaviour == QStringLiteral("enemy")' in designer
# UI caps the frame-per-step setting, and old settings are clamped on load.
assert 'spin(1, 32656, old.objectFadeDelay)' in designer
assert 'a.value(QStringLiteral("objectFadeDelay")).toInt(2), 32656' in project
assert 'qBound(1, r.objectFadeDelay, 32656)' in source
assert 'Build: 5.104.251026' in read('splashscreenwidget.cpp')
# Extract the exact firmware-rule statements, preserving source formatting.
template=read('idelibs/codehelpers/game/gameworlditems.rulec')
match=re.search(r'@IDE_SECTION\{TARGET_ACTION\}(.*?)@IDE_SECTION_END',template,re.S)
assert match
rule=match.group(1)
def render(target,action):
    # Conditional subblocks exactly correspond to three target actions.
    s=re.sub(r'@IDE_IF\{(TARGET_ENABLE|TARGET_DISABLE|TARGET_TOGGLE)\}(.*?)@IDE_END',
        lambda m:m.group(2) if m.group(1)=='TARGET_'+action.upper() else '',rule, flags=re.S)
    return s.replace('@IDE{TARGET_EXPRESSION}',target)
# Action order matters: turning on, toggling back off, then on again.
actions=[('objects[0]','disable'),('objects[1]','enable'),('objects[1]','toggle'),('objects[2]','enable')]
body=''.join(render(*a) for a in actions)
assert body.count('.active =')==4
program='''#include <stdint.h>
typedef struct { uint8_t active; } object_t;
static object_t objects[3]={{1},{0},{0}};
static void trigger(void) { if (1) {\n'''+body+'''\n} }
int main(void) { trigger();
 if (objects[0].active != 0 || objects[1].active != 0 || objects[2].active != 1) return 1;
 trigger();
 if (objects[0].active != 0 || objects[1].active != 0 || objects[2].active != 1) return 2;
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage5103_') as dir:
    c=Path(dir)/'linked_actions.c';exe=Path(dir)/'linked_actions';c.write_text(program)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.103: Trigger action list pipeline + native C order PASS')
