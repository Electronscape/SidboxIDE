#include "enemy.h"

int main(void)
{
    struct Enemy party[3] = {0};
    party[0].x = 4;
    party[0].health = 40;
    party[1].x = 7;
    party[1].health = 50;
    party[2].x = 9;
    party[2].health = 70;

    int score = touch_enemy(party, 3);
    score += touch_enemy(&party[1], 2);
    score += touch_enemy(&party[2], 4);
    score += party[0].health + party[1].x + party[2].y;
    return score + update_enemies();
}
