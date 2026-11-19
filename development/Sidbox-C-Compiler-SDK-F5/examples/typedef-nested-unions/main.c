#include "types.h"
int main(void)
{
    Entity hero = {0};
    hero.position.x = 7;
    hero.position.y = 9;
    hero.metric.raw = 50;
    hero.health = 100;
    hero.active = 1;
    Vector2 *pos = &hero.position;
    bump_vector(pos, 0);
    move_entity(&hero, 4, 5);
    return hero.position.x + hero.position.y + hero.metric.points +
           hero.health + hero.active + hero.velocity.x +
           hero.velocity.y + evaluate_entities();
}
