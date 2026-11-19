#include "shared.h"
int helper(void)
{
    return 42;
}
int score(void)
{
    return 1000 + helper();
}
