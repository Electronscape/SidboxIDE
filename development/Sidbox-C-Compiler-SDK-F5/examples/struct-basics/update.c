#include "entity.h"

static struct Entity persistent;

int update_entity(void)
{
    struct Entity e = {0};
    e.x = 10;
    e.y = 20;
    e.health = 30;

    struct Entity *p = &e;
    p->x += 8;
    p->x -= 1;
    struct Entity *q = p;
    q->health += 5;
    q->health -= 2;

    int *hp = &e.health;
    *hp = *hp + 4;

    persistent.x = e.x + e.y;
    persistent.health = e.health;
    return persistent.x * 10 + persistent.health;
}
