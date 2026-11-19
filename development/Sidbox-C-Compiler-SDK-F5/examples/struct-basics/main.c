#include "entity.h"

int main(void)
{
    struct Entity local = {0};
    local.x = 4;
    struct Entity *p = &local;
    p->y = 5;
    return update_entity() + local.x * 10 + p->y;
}
