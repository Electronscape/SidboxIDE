"""Stage 5.166.104: compile the actual generator's patrol C and exercise ledges.

Run: python3 -m unittest discover -s development/tests -p 'test_stage5166_104_*.py'
"""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

SRC = Path(__file__).resolve().parents[2]
RULEC = SRC / 'idelibs/codehelpers/game/worldobjects.rulec'


class EnemyPatrolLedgeTests(unittest.TestCase):
    def test_original_wall_turn_is_retained(self):
        c = RULEC.read_text()
        self.assertIn('if (climb > step) { dir = -dir; break; }', c)
        self.assertIn('if (down > step) { dir = -dir; break; }', c)
        self.assertIn('blocked(nx, ny + down + 1, o->width, o->height, context)', c)

    def test_native_runtime_patrol_on_slopes_ledges_and_walls(self):
        compiler = shutil.which('cc')
        if compiler is None:
            self.skipTest('Host C compiler unavailable')
        src = RULEC.read_text()
        marker = '/* All positions are in WORLD coordinates.'
        start = src.index('void game_world_objects_roam(')
        stop = src.index(marker, start)
        patrol = src[start:stop]
        self.assertIn('const int32_t front_x', patrol)
        self.assertIn('front_x - dir', patrol)
        harness = r'''
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GAME_OBJECT_ENEMY 9u
#define BLIT_FLAG_FLIP_X 1u
typedef struct {
    int16_t drawx, drawy;
    uint16_t flags;
} gfxbob_t;
typedef struct {
    gfxbob_t *sprite;
    int32_t x,y;
    uint16_t width,height;
    uint8_t type,active,enemy_roam,enemy_roam_speed,enemy_step_height;
    int8_t enemy_roam_direction;
    uint8_t enemy_base_flip_x;
} game_world_object_t;
static int16_t clamp16(int64_t v) { return (int16_t)v; }
''' + patrol + r'''

typedef struct { int mode; int wall_x; } terrain_t;
/* y is down, with solid material at and below this surface. */
static int ground_y(int x, int mode) {
    if (mode == 0) return x >= 20 && x < 80 ? 100 : -1;
    if (mode == 1) return x >= 20 && x < 80 ? 100 : x >= 80 && x < 150 ? 125 : -1;
    if (mode == 2) return x >= 20 && x < 150 ? 100 + (x - 20) / 2 : -1;
    if (mode == 3) return x >= 20 && x < 150 ? 100 + (x - 20) : -1;
    if (mode == 4) return x >= 20 && x < 150 ? 100 : -1;
    if (mode == 5) return x >= 20 && x < 80 ? 100 : x >= 80 && x < 150 ? 97 : -1;
    if (mode == 6) return x >= 20 && x < 80 ? 100 : x >= 80 && x < 150 ? 104 : -1;
    return -1;
}
static uint8_t blocked(int32_t x,int32_t y,uint16_t w,uint16_t h,void *ctx) {
    terrain_t *t = (terrain_t *)ctx;
    if (t->wall_x && x + w > t->wall_x && x < t->wall_x + 4 && y + h > 50) return 1;
    for (int32_t sx = x; sx < x + w; ++sx) {
        int surface = ground_y((int)sx, t->mode);
        if (surface >= 0 && y + h > surface) return 1;
    }
    return 0;
}
static void fail(const char *which, const game_world_object_t *o) {
    fprintf(stderr,"%s: x=%ld y=%ld dir=%d\n",which,(long)o->x,(long)o->y,o->enemy_roam_direction);
    exit(1);
}
static game_world_object_t enemy(int x,int y,int w,int facing,int speed,int step,gfxbob_t *bob) {
    game_world_object_t o;
    memset(&o,0,sizeof(o));
    o.x=x; o.y=y; o.width=w; o.height=10; o.type=GAME_OBJECT_ENEMY;
    o.active=1; o.enemy_roam=1; o.enemy_roam_speed=speed;
    o.enemy_step_height=step; o.enemy_roam_direction=facing; o.sprite=bob;
    return o;
}
int main(void) {
    terrain_t t={0,0};
    gfxbob_t bob={0,0,0};
    game_world_object_t o = enemy(45,90,16,1,8,4,&bob);
    /* The front edge (x+15) must never leave [20,80). */
    int saw_right_turn=0, saw_left_turn=0;
    for (int i=0;i<200;i++) {
        int prior_dir=o.enemy_roam_direction;
        game_world_objects_roam(&o,1,1,blocked,&t);
        if (o.x < 20 || o.x+o.width > 80) fail("off flat ledge",&o);
        if (prior_dir==1 && o.enemy_roam_direction==-1) saw_right_turn=1;
        if (prior_dir==-1 && o.enemy_roam_direction==1) saw_left_turn=1;
        if (bob.drawx != o.x || bob.drawy != o.y) fail("sprite unsynced",&o);
        if ((int)!!(bob.flags & BLIT_FLAG_FLIP_X) != (o.enemy_roam_direction<0))
            fail("wrong facing",&o);
    }
    if (!saw_right_turn||!saw_left_turn) fail("no ledge reversal",&o);
    /* Abrupt deep step has lower ground, but still counts as a ledge. */
    t.mode=1; o=enemy(55,90,16,1,8,4,NULL);
    for (int i=0;i<15;i++) {
        game_world_objects_roam(&o,1,1,blocked,&t);
        if (o.x + o.width > 80) fail("went off deep drop",&o);
    }
    /* A gentle downhill ramp must remain traversable in both directions. */
    t.mode=2; o=enemy(25,92,16,1,1,4,NULL);
    for (int i=0;i<35;i++) game_world_objects_roam(&o,1,1,blocked,&t);
    if (o.x < 55 || o.enemy_roam_direction!=1) fail("gentle slope turned",&o);
    /* A 1px-per-x slope: forward foot can be far below the rear foot. */
    t.mode=3; o=enemy(20,90,32,1,1,4,NULL);
    for (int i=0;i<22;i++) game_world_objects_roam(&o,1,1,blocked,&t);
    if (o.x < 39 || o.enemy_roam_direction!=1) fail("steep slope turned",&o);
    /* Wall reversal remains independent of the new ledge guard. */
    t.mode=4; t.wall_x=75; o=enemy(45,90,16,1,4,4,NULL);
    for (int i=0;i<20;i++) game_world_objects_roam(&o,1,1,blocked,&t);
    if (o.x >= 60) fail("wall walk-through",&o);
    t.wall_x=0;
    /* Climb a 3px step up, and descend a 4px step. */
    t.mode=5; o=enemy(53,90,16,1,1,4,NULL);
    for (int i=0;i<25;i++) game_world_objects_roam(&o,1,1,blocked,&t);
    if (o.x <= 75 || o.enemy_roam_direction!=1) fail("upstep refused",&o);
    t.mode=6; o=enemy(53,90,16,1,1,4,NULL);
    for (int i=0;i<30;i++) game_world_objects_roam(&o,1,1,blocked,&t);
    if (o.x <= 75 || o.enemy_roam_direction!=1) fail("downstep refused",&o);
    puts("patrol C: ledges, deep drops, both directions, sprites, slopes, walls, small steps PASS");
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            p = Path(d)
            (p / 'patrol.c').write_text(harness)
            cmd = [compiler, '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror',
                   str(p / 'patrol.c'), '-o', str(p / 'patrol')]
            compile_result = subprocess.run(cmd, capture_output=True, text=True)
            self.assertEqual(compile_result.returncode, 0, compile_result.stderr)
            run_result = subprocess.run([str(p / 'patrol')], capture_output=True, text=True)
            self.assertEqual(run_result.returncode, 0, run_result.stdout + run_result.stderr)
            self.assertIn('PASS', run_result.stdout)


if __name__ == '__main__':
    unittest.main()
