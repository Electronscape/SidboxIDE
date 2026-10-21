#!/usr/bin/env python3
"""Stage 4.43 story-rule migration tests without Qt6 installed.

Exercises the actual rule C/H skeleton with project-record fixtures, compiles
rendered C under GCC, verifies strict marker requirements and installer wiring.
This is NOT a substitute for the Qt C++ generator or SIDBOX hardware test.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
from stage442_render_test_helpers import render_adventure_runtime
import json
import re
import subprocess

ROOT=Path(__file__).resolve().parents[2]
TEMPLATES=ROOT/'idelibs/codehelpers/game'
C=(TEMPLATES/'gameadventure.rulec').read_text()
H=(TEMPLATES/'gameadventure.ruleh').read_text()
GEN=(ROOT/'gameadventuregen.cpp').read_text()
DES=(ROOT/'gamedesigner.cpp').read_text()
UP=(ROOT/'gamedesigner_update.cpp').read_text()
RENDER=(ROOT/'gamehelpertemplates.h').read_text()

required_c={'ITEM_ROWS','NODE_ROWS','WORLD_OBJECT_INCLUDE','CHOICE_FLAGS','NPC_ROWS',
    'NPC_COMPLETED_NODES','NPC_FRAME_ROWS','NPC_ANIMATION_ROWS','SKIN_CELLS',
    'SKIN_FLIPS','LINKED_ACTION_CASES','SKIN_LOAD_STATEMENT'}
required_h={'ITEM_COUNT','NODE_COUNT','NPC_COUNT'}
assert set(re.findall(r'@IDE\{([^{}]+)\}',C))==required_c
assert set(re.findall(r'@IDE\{([^{}]+)\}',H))==required_h
assert 'gameadventure_setup(void)' in C and 'game_adventure_start(' in C
assert 'gameadventure_on_event' in C and 'game_adventure_story_flags' in C
assert 'void gameadventure_setup(void)' not in GEN
assert 'game_adventure_start(' not in GEN
assert 'game_adventure_on_event(' not in GEN
assert 'GameHelperTemplates::renderFields' in GEN
assert 'loadRule(rules,QStringLiteral(".rulec")' in GEN
assert 'loadRule(rules,QStringLiteral(".ruleh")' in GEN
assert 'source.contains(QStringLiteral("@IDE{%1}")' in GEN
assert 'inline bool renderFields' in RENDER
assert 'AnchoredMatchOption' in RENDER
assert 'base == QStringLiteral("gameadventure")' in UP
assert 'base == QStringLiteral("gameadventure")' in DES
assert 'QDir(helperTemplatesRoot()).filePath(QStringLiteral("game"))' in DES
assert 'gamehelpers/gameadventure.c' in UP and 'gamehelpers/gameadventure.h' in UP
assert UP.index('gamehelpers/gameadventure.c') < UP.index('const QString stamp')
assert 'Missing Adventure story rule' in UP


def render_rule(tmpl, values):
    # Same strict one-pass substitution contract as the Qt renderer.
    parts=[]
    cursor=0
    for match in re.finditer(r'@IDE\{([A-Z_][A-Z0-9_]*)\}',tmpl):
        name=match.group(1)
        if name not in values:
            raise ValueError(name)
        parts += [tmpl[cursor:match.start()],str(values[name])]
        cursor=match.end()
    parts.append(tmpl[cursor:])
    return ''.join(parts)


def fixture(project):
    adventure=project.get('adventure',{})
    items=adventure.get('items',[])
    nodes=adventure.get('nodes',[])
    npcs=adventure.get('npcs',[])
    sprites={r.get('id'):r for r in project.get('resources',[]) if r.get('kind')=='sprite'}
    world=[r for r in project.get('resources',[])
           if r.get('kind')=='sprite' and r.get('gameObject',{}).get('type',r.get('objectType','decoration')) not in ('decoration','collectable')]
    def q(s): return json.dumps(s,ensure_ascii=True)
    values={
        'ITEM_COUNT':len(items),'NODE_COUNT':len(nodes),'NPC_COUNT':len(npcs),
        'WORLD_OBJECT_INCLUDE':'#include "gameworlditems.h"' if world else '',
        'ITEM_ROWS':'\n'.join(f'    {{{q(x.get("name", ""))},{x.get("pickupKind",0)}u,{x.get("icon",65535)}u,{x.get("capacity",1)}u,{x.get("initial",0)}u}},' for x in items) if items else '    {0,0,0,0,0},',
        'NODE_ROWS':'','CHOICE_FLAGS':'','NPC_ROWS':'','NPC_COMPLETED_NODES':'',
        'NPC_FRAME_ROWS':'','NPC_ANIMATION_ROWS':'',
        'SKIN_CELLS':','.join(str(n) for n in (adventure.get('skinIndices') or list(range(9)))),
        'SKIN_FLIPS':','.join(str(n & 12) for n in (adventure.get('skinFlips') or [0]*9)),
        'LINKED_ACTION_CASES':'','SKIN_LOAD_STATEMENT':'',
    }
    flags=[]
    node_rows=[]
    for ni,n in enumerate(nodes):
        rows=[]
        for ci in range(3):
            ch=(n.get('choices') or [{}]*3)
            ch=ch[ci] if ci<len(ch) else {}
            target=ch.get('targetObjectId','')
            action=ch.get('action',-1)
            if target:
                target_index=next(i for i,r in enumerate(world) if r.get('id')==target)
                action=30000+ni*3+ci
                mode={'disable':0,'enable':1,'toggle':2}.get(ch.get('targetAction'),1)
                values['LINKED_ACTION_CASES']+=f'    case {action}: gameworlditems_set_active({target_index}u, {mode}u); break;\n'
            vals=[q(ch.get('text','')),q(ch.get('reply',''))]
            vals += [str(ch.get(k,-1)) for k in ('next','requires','give','take')]
            vals.append(str(action))
            rows.append('        {'+','.join(vals)+'},')
            flags.append(str(int(bool(ch.get('once')))+2*int(bool(ch.get('completeNpc')))))
        node_rows.append('    {'+q(n.get('speaker',''))+','+q(n.get('text',''))+', {\n'+'\n'.join(rows)+'\n    }},')
    values['NODE_ROWS']='\n'.join(node_rows) if nodes else '    {0,0,{{0,0,-1,-1,-1,-1,-1}}},'
    values['CHOICE_FLAGS']=','.join(flags) if flags else '0'
    npc_rows=[]; done=[]; animations=[]; frametables=[]
    for i,npc in enumerate(npcs):
        r=sprites[npc['spriteId']]
        npc_rows.append(f'    {{{r.get("x",0)},{r.get("y",0)},{r.get("cellWidth",64)}u,{r.get("cellHeight",64)}u,{npc.get("radius",48)}u,{npc.get("node",0)}u}},')
        done.append(f'{npc.get("doneNode",65535) if npc.get("doneNode",-1)>=0 else 65535}u')
        anim=npc.get('animation',{})
        first=[anim.get('idleFirst',0),anim.get('talkFirst',0)]
        count=[anim.get('idleCount',0),anim.get('talkCount',0)]
        ptr=['0','0']
        for state,name in enumerate(('idle','talk')):
            frames=anim.get(name+'Frames',[])
            if frames:
                count[state]=len(frames)
                ptr[state]=f'&npc_animation_frames[{len(frametables)}u]'
                frametables += [f'    {{{x["index"]}u,{x.get("delay",6)}u}},' for x in frames]
        # The fake sprite name is declared by the mock gameassets.h
        animations.append(f'    {{&test_sprite,{first[0]}u,{count[0]}u,{anim.get("idleSpeed",6)}u,{first[1]}u,{count[1]}u,{anim.get("talkSpeed",5)}u,{ptr[0]},{ptr[1]},{4 if r.get("objectFlipX") else 0}u}},')
    values['NPC_ROWS']='\n'.join(npc_rows) if npc_rows else '    {0,0,0,0,0,0},'
    values['NPC_COMPLETED_NODES']=','.join(done) if done else '65535u'
    values['NPC_FRAME_ROWS']='\n'.join(frametables)
    values['NPC_ANIMATION_ROWS']='\n'.join(animations) if animations else '    {0},'
    if adventure.get('skinAtlasId'):
        values['SKIN_LOAD_STATEMENT']='    skin = gameassets_find_ppb("graphics/tilemap.ppb", &width, &height);'
    return values


def check_source(project,folder):
    fields=fixture(project)
    folder.mkdir(parents=True,exist_ok=True)
    (folder/'gameadventure.c').write_text(render_rule(C,fields))
    (folder/'gameadventure.h').write_text(render_rule(H,fields))
    assert '@IDE{' not in (folder/'gameadventure.c').read_text()
    assert f'#define GAME_ADVENTURE_STORY_NODE_COUNT {fields["NODE_COUNT"]}u' in (folder/'gameadventure.h').read_text()
    api=folder/'gameassets'
    api.mkdir()
    (api/'gameassets.h').write_text('''#include <stdint.h>
#include "apis.h"
extern gfxbob_t test_sprite;
const uint8_t *gameassets_find_ppb(const char *, uint16_t *, uint16_t *);
''')
    (folder/'gamehelpers').mkdir()
    (folder/'gamehelpers'/'gameworlditems.h').write_text('''#include <stdint.h>
void gameworlditems_set_active(uint16_t, uint8_t);
''')
    # Mirror real project: gamehelpers/ is sibling to gameassets/
    helpers=folder/'gamehelpers'
    runtime=render_adventure_runtime(ROOT, folder/'runtime_tmp',items=len(project.get('adventure',{}).get('items',[])))
    for name in ('adventureruntime.h', 'adventureruntime.c'):
        (helpers/('game'+name)).write_bytes((runtime/name).read_bytes())
    for name in ('gameadventure.c','gameadventure.h'):
        (folder/name).rename(helpers/name)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-fsyntax-only',
                    '-I',str(ROOT/'development/tests/stage429_mock_api'),
                    '-I',str(helpers),'-I',str(api),
                    str(helpers/'gameadventure.c')], check=True)
    return (helpers/'gameadventure.c').read_text()

with TemporaryDirectory() as d:
    root=Path(d)
    code=check_source({},root/'empty')
    assert '{0,0,0,0,0},' in code and '{0,0,0,0,0,0},' in code
    project=json.loads(Path('/mnt/data/world1.sbgm').read_text()) if Path('/mnt/data/world1.sbgm').exists() else {
        'adventure':{'items':[{'name':'Flower','pickupKind':5}],
            'nodes':[{'speaker':'Future Kim','text':'Please bring a flower!',
                'choices':[{'text':'Here you go!','completeNpc':True,'once':True}]},
                     {'speaker':'Future Kim','text':'Thank you!'}],
            'npcs':[{'spriteId':'sprite0','node':0,'doneNode':1,'animation':{
                'idleFrames':[{'index':0,'delay':6}],
                'talkFrames':[{'index':1,'delay':6}]}}]},
        'resources':[{'id':'sprite0','kind':'sprite','name':'Future Kim',
            'objectType':'decoration','cellWidth':64,'cellHeight':64}]}
    if project:
        result=check_source(project,root/'guardian')
        assert 'Future Kim' in result and 'gameworlditems_set_active' in result
        assert '&npc_animation_frames[0u]' in result and 'npc_animation_frames' in result
        assert 'npc_completed_nodes' in result
    # Multi-NPC animation offsets must point to the correct parts of the
    # flattened frame table, even with different numbers of frames.
    multi={'adventure':{'nodes':[{'speaker':'Hi','text':'Hello'}],
        'npcs':[{'spriteId':'A','node':0,'animation':{'idleFrames':[{'index':0},{'index':1}],
            'talkFrames':[{'index':2}]}},
            {'spriteId':'B','node':0,'animation':{'idleFrames':[{'index':3}],
                'talkFrames':[{'index':4},{'index':5}]}}]},
        'resources':[{'id':'A','kind':'sprite','objectType':'decoration','cellWidth':16,'cellHeight':16},
                     {'id':'B','kind':'sprite','objectType':'decoration','cellWidth':16,'cellHeight':16}]}
    multi_code=check_source(multi,root/'multi-npc')
    for offset in range(6):
        assert f'&npc_animation_frames[{offset}u]' not in multi_code or offset in (0,2,3,4)
    for offset in (0,2,3,4): assert f'&npc_animation_frames[{offset}u]' in multi_code
    # Record limits: the template structure remains valid at maximum inventory,
    # dialogue and NPC counts (the Qt side validates these exact limits).
    capacity={'adventure':{
        'items':[{'name':f'Item {i}','pickupKind':i%256} for i in range(64)],
        'nodes':[{'speaker':'NPC','text':f'Node {i}','choices':[]} for i in range(256)],
        'npcs':[{'spriteId':'A','node':0,'doneNode':255} for _ in range(256)]},
        'resources':[{'id':'A','kind':'sprite','objectType':'decoration',
                      'cellWidth':16,'cellHeight':16}]}
    max_code=check_source(capacity,root/'limits')
    assert 'GAME_ADVENTURE_STORY_NPC_COUNT' in max_code
    # Token-like text within project data must remain a literal, not be expanded.
    ghost=fixture({'adventure':{'nodes':[{'speaker':'@IDE{BOGUS}','text':'Hello','choices':[]}]}})
    text=render_rule(C,ghost)
    assert '"@IDE{BOGUS}"' in text
    for broken in (C.replace('@IDE{ITEM_ROWS}', '@IDE{FAKE_VALUE}'),
                   C.replace('@IDE{ITEM_ROWS}', '@IDE{ITEM_ROWS'),
                   C.replace('@IDE{ITEM_ROWS}', '')):
        if broken==C: raise AssertionError
        try:
            if 'ITEM_ROWS' not in re.findall(r'@IDE\{([^{}]+)\}',broken):
                raise ValueError('Missing required ITEM_ROWS')
            if '@IDE{ITEM_ROWS' in broken and '@IDE{ITEM_ROWS}' not in broken:
                raise ValueError('Malformed marker')
            render_rule(broken,fixture({}))
        except ValueError: pass
        else: raise AssertionError('bad rule accepted')
print('Stage4.43 story rule static paths, Guardian + empty GCC and safety checks PASS')
