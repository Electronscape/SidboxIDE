#include "extra.h"
#include "extra.h"

static int counter = 0;

int calculate(void)
{
    int sum = 0;
    int old = 0;
    for (int i = 0; i < 12; i++) {
        if (i == 5) continue;
        if (i == 10) break;
        sum += i;
    }
    for (int j = 10; j > 0; j -= STEP) {
        sum -= 1;
    }
    for (;;) {
        ++counter;
        if (counter == 3) break;
    }
    old = counter++;
    sum += old;
    sum += counter--;
    sum += --counter;
    sum += ++counter;
    sum += LOOP_BONUS;
    sum += EXTRA_BONUS;
    return sum;
}
