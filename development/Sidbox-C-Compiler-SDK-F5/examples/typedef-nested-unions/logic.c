#include "types.h"
static Entity enemies[4];
void bump_vector(Vector2 *v, int amount)
{
    v->x += amount;
}
void move_entity(Entity *entity, int dx, int dy)
{
    bump_vector(&entity->position, dx);
    entity->position.y += dy;
    entity->velocity.x = dx;
    entity->velocity.y = dy;
    entity->metric.points += dx;
    entity->health -= dy;
}
int evaluate_entities(void)
{
    for (int i = 0; i < 4; i++) {
        enemies[i].position.x = i * 10;
        enemies[i].position.y = i * 20;
        enemies[i].metric.raw = i + 3;
        enemies[i].health = 100;
        move_entity(&enemies[i], 2, 4);
        bump_vector(&enemies[i].velocity, 0);
    }
    return enemies[3].position.x + enemies[2].position.y +
           enemies[0].metric.raw + enemies[3].health;
}
