#ifndef SIDC_ENEMY_H
#define SIDC_ENEMY_H
struct Enemy {
    int x;
    int y;
    int health;
};
int touch_enemy(struct Enemy *e, int amount);
int update_enemies(void);
#endif
