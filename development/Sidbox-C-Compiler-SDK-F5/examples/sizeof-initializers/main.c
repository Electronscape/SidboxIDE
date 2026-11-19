#include "types.h"

static int lookup[5] = {3, 5, 7, 11, 13};
static Entity boss = {{10, 20}, {1, 2}, {7}, 80, 1};
static Entity enemies[2] = {
    {{1, 2}, {3, 4}, {9}, 30, 1},
    {{5, 6}, {7, 8}, {13}, 40, 1}
};
static int entity_bytes = sizeof(Entity);

int main(void)
{
    int scores[5] = {4, 8, 12};
    Vector2 point = {9, 17};
    Entity local = {{10, 20}, {1, 2}, {5}, 40, 1};
    Entity party[2] = {
        {{1, 3}, {2, 4}, {6}, 30, 1},
        {{10, 12}, {1, 1}, {8}, 50, 1}
    };
    int *pointer = scores;
    Entity *boss_pointer = &boss;
    int index = 1;
    int total = lookup[2] + lookup[4] + scores[0] + scores[2];
    total += point.x + point.y + local.position.x + local.health;
    total += value_of(&boss) + value_of(&enemies[1]) + value_of(&party[0]);
    total += sizeof(Entity) + sizeof(boss) + sizeof(enemies);
    total += sizeof(enemies[0]) + sizeof(enemies[0].position);
    total += sizeof(scores) + sizeof(scores[2]) + sizeof(point.x);
    total += sizeof(int) + sizeof(Vector2) + sizeof(Metric);
    total += sizeof(int[3]) + sizeof(Vector2[2]) + sizeof(17);
    total += sizeof(*pointer) + sizeof(*boss_pointer) + sizeof(boss_pointer->position.y);
    total += sizeof(scores[index++]) + index * 2 + entity_bytes;
    return total;
}
