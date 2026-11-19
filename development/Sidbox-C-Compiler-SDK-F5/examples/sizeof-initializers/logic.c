#include "types.h"

int value_of(Entity *entity)
{
    return entity->position.x + entity->position.y +
           entity->velocity.x + entity->velocity.y +
           entity->metric.raw + entity->health + entity->active;
}
