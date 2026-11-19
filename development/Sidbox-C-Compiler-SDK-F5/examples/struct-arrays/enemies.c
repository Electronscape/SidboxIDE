#include "enemy.h"
static struct Enemy enemies[6];

int touch_enemy(struct Enemy *e, int amount)
{
    e->x += amount;
    e->y += 2;
    e->health -= amount;
    return e->x + e->y + e->health;
}

int update_enemies(void)
{
    int score = 0;
    for (int i = 0; i < 6; ++i) {
        enemies[i].x = i * 10;
        enemies[i].y = 3;
        enemies[i].health = 100;
        touch_enemy(&enemies[i], i + 1);
        score += enemies[i].x + enemies[i].health + enemies[i].y;
    }
    return score;
}
