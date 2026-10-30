"""Stage 5.166.105: repeatable enemy loot must not weaken exclusive quest drops.

Run: python3 -m unittest discover -s development/tests -p 'test_stage5166_105_*.py'
"""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

SRC = Path(__file__).resolve().parents[2]
RULE = SRC / 'idelibs/codehelpers/game/gameworlditems.rulec'

class RepeatableEnemyLootTests(unittest.TestCase):
    def test_independent_quest_reward_validation(self):
        s = (SRC/'gamedesigner_export.cpp').read_text()
        self.assertIn('QHash<QString, int> breakRewardOwner',s)
        self.assertIn('if (breakRewardOwner.contains(id))',s)
        self.assertIn('droppingPickups.contains(j)',s)
        self.assertIn('r.pickupPersistent || r.pickupKind == 3',s)
        self.assertIn('r.pickupAllowEnemyLoot',s)
        self.assertIn('enemy.enemyLootMax > 8',s)
        self.assertIn('const int lootSlotCount = qMin(64, lootRuleCount * 8);',s)

    def test_project_roundtrip_and_copying(self):
        project=(SRC/'gamedesigner_project.cpp').read_text()
        for key in ('enemyLootIds','enemyLootMin','enemyLootMax','pickupAllowEnemyLoot'):
            self.assertIn('object.value(QStringLiteral("'+key+'"))',project)
            self.assertIn('object.insert(QStringLiteral("'+key+'")',project)
        ui=(SRC/'gamedesigner.cpp').read_text()
        self.assertIn('QAbstractItemView::MultiSelection',ui)
        self.assertIn('r.enemyLootIds.clear()',ui)
        self.assertIn('refillEnemyLoot(old.enemyLootIds)',ui)
        self.assertEqual(ui.count('for (QString &lootId : r.enemyLootIds) lootId = importById(lootId);'),2)

    def test_snapshot_draw_pickup_hooks(self):
        s=RULE.read_text()
        for part in ('CG_SAVE_BYTES(cg_loot_saved);','CG_LOAD_BYTES(cg_loot_saved);',
                     'memcpy(cg_loot_saved,cg_loot_slots',
                     'memcpy(cg_loot_slots,cg_loot_saved',
                     'cg_loot_update(frames);','cg_loot_spawn();',
                     'game_collectables_check(cg_loot_pickups,CG_LOOT_CAPACITY',
                     'game_collectables_draw_layer(cg_loot_pickups',
                     '&cg_pickup_stamps[cg_loot_slots[i].template_index]'):
            self.assertIn(part,s)
        self.assertIn('item->persistent = 0;',s)
        self.assertIn('cg_loot_bobs[slot] = *source->sprite;',s)
        self.assertIn('item->can_collect = state->can_collect;',s)

    def test_native_c_spawn_and_gravity(self):
        compiler=shutil.which('clang') or shutil.which('cc')
        if not compiler: self.skipTest('No C compiler')
        s=RULE.read_text()
        a=s.index('/* Stage 5.166.105: repeatable enemy loot.')
        z=s.index('@IDE_END',a)
        c=s[a:z].replace('@IDE{LOOT_SLOT_COUNT}','16').replace('@IDE{PICKUP_COUNT}','3')
        c=c.replace('@IDE{LOOT_RULE_COUNT}','2').replace('@IDE{WORLD_SYMBOL}','world_tilemap')
        c=c.replace('@IDE{LOOT_RULE_ROWS}',
            '    {0u,8u,8u,1u,{0u}},\n    {1u,1u,1u,2u,{0u,1u}},\n')
        headers=r'''
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct {int16_t drawx,drawy;uint16_t width,height;const void *imgdat;} gfxbob_t;
typedef struct {gfxbob_t *sprite; int32_t x,y; uint16_t width,height,kind,value;
  uint8_t active,can_collect,persistent,tracking_configured,show_in_inventory,show_in_hud,stat_target,draw_behind_tiles;
  const char *stat_name; uint16_t respawn_frames,respawn_left,spline_start_delay;void *animation,*spline;} game_collectable_t;
typedef struct {int32_t x,y;int32_t width,height;uint8_t break_triggered;} game_world_object_t;
static game_collectable_t cg_gwi_pickups[3];
static game_world_object_t cg_gwi_platforms[2];
static gfxbob_t original_bobs[3];
static int world_tilemap;
static uint8_t game_tilemap_actor_blocked(const void *m,int32_t x,int32_t y,uint16_t w,uint16_t h)
{ (void)m;(void)x;(void)w;return y+h>64; }
'''
        main=r'''
int main(void) {
 (void)cg_loot_saved; (void)cg_loot_saved_rng;
 for(int i=0;i<3;i++){original_bobs[i]=(gfxbob_t){0,0,8,8,(void*)1};
  cg_gwi_pickups[i].sprite=&original_bobs[i];cg_gwi_pickups[i].kind=i+1;
  cg_gwi_pickups[i].value=1;cg_gwi_pickups[i].width=8;cg_gwi_pickups[i].height=8;cg_gwi_pickups[i].active=1;}
 cg_gwi_platforms[0]=(game_world_object_t){16,16,16,16,1};
 cg_gwi_platforms[1]=(game_world_object_t){48,16,16,16,0};
 cg_loot_spawn();
 int count=0;
 for(int i=0;i<16;i++)if(cg_loot_slots[i].active){count++;
   assert(cg_loot_slots[i].template_index==0);
   assert(cg_loot_pickups[i].sprite!=cg_gwi_pickups[0].sprite);}
 assert(count==8);assert(cg_gwi_pickups[0].active==1);assert(original_bobs[0].drawx==0);
 cg_gwi_platforms[0].break_triggered=0;cg_gwi_platforms[1].break_triggered=1;
 cg_loot_spawn();
 count=0;for(int i=0;i<16;i++)if(cg_loot_slots[i].active)count++;assert(count==9);
 for(int step=0;step<90;step++)cg_loot_update(1);
 int landed=0;for(int i=0;i<16;i++)if(cg_loot_slots[i].active && cg_loot_pickups[i].can_collect)landed++;
 assert(landed==9);
 cg_loot_pickups[0].active=0;cg_loot_slots[0].active=0;
 cg_gwi_platforms[0].break_triggered=1;cg_gwi_platforms[1].break_triggered=0;
 cg_loot_spawn();
 count=0;for(int i=0;i<16;i++)if(cg_loot_slots[i].active)count++;assert(count==16);
 assert(original_bobs[0].drawx==0);assert(cg_gwi_pickups[0].x==0);
 /* Save/load reconstitutes the clone from a source sprite, not a stale pointer. */
 memcpy(cg_loot_saved,cg_loot_slots,sizeof(cg_loot_slots));
 memset(cg_loot_pickups,0,sizeof(cg_loot_pickups));
 memcpy(cg_loot_slots,cg_loot_saved,sizeof(cg_loot_slots));
 for(int i=0;i<16;i++)cg_loot_rebuild(i);
 for(int i=0;i<16;i++)if(cg_loot_slots[i].active)assert(cg_loot_pickups[i].sprite==&cg_loot_bobs[i]);
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            source=Path(d)/'loot.c'; binary=Path(d)/'loot'
            source.write_text(headers+c+main)
            compiled=subprocess.run([compiler,'-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],
                                    capture_output=True,text=True)
            self.assertEqual(compiled.returncode,0,compiled.stderr)
            executed=subprocess.run([str(binary)],capture_output=True,text=True)
            self.assertEqual(executed.returncode,0,executed.stderr)

if __name__=='__main__': unittest.main()
