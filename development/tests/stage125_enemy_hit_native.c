#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "gameworldobjects.c"
void run_spline(game_spline_t *p, uint16_t frames){ (void)p; (void)frames; }
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y){ (void)p; (void)x; (void)y; }
void run_animation(game_animation_t *p, uint16_t frames){ (void)p; (void)frames; }
void test_bob(gfxbob_t *s){ (void)s; }
int main(void) {
  game_world_object_t e;
  gfxbob_t sprite, visible;
  memset(&e,0,sizeof e); memset(&sprite,0,sizeof sprite);
  sprite.index=7; sprite.flags=BLIT_FLAG_FLIP_X;
  assert(game_world_object_start(&e,GAME_OBJECT_ENEMY,&sprite,10,20,16,16));
  e.break_hits_required=4;
  e.enemy_hit_flash=1;
  e.enemy_hit_flash_colour=45;
  e.enemy_hit_flash_count=2;
  e.enemy_hit_flash_frames=2;
  e.enemy_hit_frame=10;
  e.enemy_hit_count=3;
  e.enemy_hit_delay=2;
  /* Empty config stays inert. */
  visible=sprite; game_world_enemy_hit_visual(&e,&visible);
  assert(visible.index==7 && visible.flags==sprite.flags);
  assert(game_world_objects_attack(&e,1,10,20,16,16,1)==1);
  assert(e.active && e.enemy_hit_ticks_remaining==8 && e.enemy_hit_elapsed==0);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(visible.index==10 && (visible.flags & BLIT_FLAG_SOLIDCOLOUR));
  assert(visible.flagval[BLIT_FLAG_TYPE_TINT_VALUE]==45);
  assert(sprite.index==7 && !(sprite.flags & BLIT_FLAG_SOLIDCOLOUR));
  game_world_objects_update(&e,1,2);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(visible.index==11 && !(visible.flags & BLIT_FLAG_SOLIDCOLOUR));
  game_world_objects_update(&e,1,2);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(visible.index==12 && (visible.flags & BLIT_FLAG_SOLIDCOLOUR));
  game_world_objects_update(&e,1,4);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(!e.enemy_hit_ticks_remaining && visible.index==7 && visible.flags==sprite.flags);
  /* Repeat swings restart feedback; lethal swing stops it and starts death. */
  assert(game_world_objects_attack(&e,1,10,20,16,16,2)==1);
  assert(e.active && e.break_hits_done==3 && e.enemy_hit_elapsed==0);
  e.enemy_defeat_frame=99; e.enemy_defeat_frames=3;
  assert(game_world_objects_attack(&e,1,10,20,16,16,1)==1);
  assert(!e.active && e.break_triggered && e.enemy_dying==3 && !e.enemy_hit_ticks_remaining);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(!(visible.flags & BLIT_FLAG_SOLIDCOLOUR));
  assert(game_world_objects_attack(&e,1,10,20,16,16,1)==0);
  /* Reaction can be pure flash without an animation or vice versa. */
  memset(&e,0,sizeof e);game_world_object_start(&e,GAME_OBJECT_ENEMY,&sprite,10,20,16,16);
  e.break_hits_required=5;e.enemy_hit_flash=1;e.enemy_hit_flash_colour=33;
  e.enemy_hit_flash_count=2;e.enemy_hit_flash_frames=1;
  assert(game_world_objects_attack(&e,1,10,20,16,16,1)==1);
  visible=sprite;game_world_enemy_hit_visual(&e,&visible);
  assert(visible.index==sprite.index && (visible.flags & BLIT_FLAG_SOLIDCOLOUR));
  puts("Stage125 hit effects native runtime PASS");return 0;
}
