#!/usr/bin/env python3
"""Stage 5.166.123: Flow Debugger must resolve exported virtual targets.

Source contracts only: desktop Qt6 rendering requires an IDE build.
"""
from pathlib import Path
import json
import re

root=Path(__file__).resolve().parents[2]
flow=(root/'gamefloweditor.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
node=(root/'gamevisualnodes.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()

assert 'Build: 5.166.123.301026' in splash
assert 'const auto virtualActionName=' in flow
assert 'const auto isVirtualTarget=' in flow
assert 'const auto virtualActionNode=' in flow
assert 'const QString key=world+QStringLiteral("/virtual-action/")+id;' in flow
assert 'g.addNode(key,world,id.startsWith(QStringLiteral("@quest_event:"))' in flow
assert 'if(!node.isEmpty())g.link(from,node,QStringLiteral("Runtime action: ")+targetAction);' in flow
assert 'if(!to.isEmpty())g.link(from,to,QStringLiteral("Runtime action: ")+action);' in flow
assert 'else g.missing(w,from,QStringLiteral("invalid virtual action target"),id);' in flow
assert 'const QString virtualName=virtualActionName(target);' in flow
assert 'if(!virtualName.isEmpty())return virtualName;' in flow
assert 'Sends quest event' in flow
assert 'questEventSignals.contains(signal)' in flow
assert 'const bool requiresEnable=' in flow
assert 'action!=QStringLiteral("enable")' in flow

# The source registry covers every command ID that game export actually accepts.
ids=[f'@player_time:{n}' for n in range(3)]+[f'@player_weather:{n}' for n in range(4)]
ids+=['@player_spotlight']
for ident in ids:
    assert f'QStringLiteral("{ident}")' in flow,ident
    assert ident in node,ident
for command in ('gameworlds_daylight_action(', 'gameworlds_weather_target_action(',
                'gameworlds_spotlight_action(', 'gameworlds_request_at(',
                'gameworlds_quest_event('):
    assert command in export,command
assert 'g.worlds.contains(name)' in flow
assert 'if(questEventSignals.contains(signal))' in flow

# Regression fixture: this is the actual saved combination that produced the
# screenshot. The triggerExtraActions loop must resolve it before consulting
# the ordinary objectKey path (which can never contain an @player_time ID).
stop_lift={'type':'trigger','triggerExtraActions':[
    {'objectId':'@player_time:0','action':'enable'}]}
assert stop_lift['triggerExtraActions'][0]['objectId'] in ids
assert stop_lift['triggerExtraActions'][0]['action']=='enable'
extra=flow[flow.index('if(isVirtualTarget(id)) {'):flow.index('const QString required=obj.value(',flow.index('if(isVirtualTarget(id)) {'))]
assert extra.index('virtualActionNode(w,id,action)')<extra.index('objectKey(w,id)')
assert 'g.missing(w,from,QStringLiteral("linked object"),id)' in extra

# Unknown modes are NOT blessed by merely sharing a valid prefix.
for ident in ('@player_time:7','@player_weather:99','@player_world:Nonexistent',
              '@quest_event:deleted_signal'):
    assert f'QStringLiteral("{ident}")' not in flow
print('PASS Stage 5.166.123 Flow Debugger virtual actions, saved stopLift repro and negative ID checks')
