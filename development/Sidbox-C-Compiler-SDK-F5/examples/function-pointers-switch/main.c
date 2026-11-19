#include "shared.h"

int dispatch(int selector)
{
    int (*operation)(int, int) = add;
    int result = operation(10, 20); /* 30 */
    operation = multiply;
    result += (*operation)(3, 4);     /* 42 */

    switch (selector) {
        case 1:
            result += 3;
            break;
        case 2:
            result += 4; /* fall through */
        case 3:
            result += 5;
            break;
        default:
            result = -1;
    }
    return result;
}

int main(void)
{
    int total = dispatch(1);      /* 45 */
    total += dispatch(2);         /* 51 -> 96 */
    total += dispatch(9);         /* -1 -> 95 */
    int loops = 0;
    for (int i=0; i<5; i++) {
        switch (i) {
            case 0: continue;    /* continues for loop */
            case 1: loops += 10; break;
            case 2: loops += 20; break;
            default: loops++; break;
        }
        loops++;
    }
    return total + loops;         /* loops=36, expected 131 */
}
