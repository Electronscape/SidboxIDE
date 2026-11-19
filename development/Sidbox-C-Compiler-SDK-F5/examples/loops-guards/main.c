#include "settings.h"
#include "extra.h"
#include "settings.h"

#define OLD_FLAG 1
#undef OLD_FLAG
#ifdef OLD_FLAG
#error This undefined flag must stay off
#endif

#if (0 && (1 / 0))
#error Short-circuited expression must stay off
#endif
#if (1 || (1 / 0))
#define SHORT_CIRCUIT_OK 1
#endif
#if 0
struct unsupported { double x; };
#error This disabled branch must never be evaluated
#endif

#ifndef DOES_NOT_EXIST
#define MAIN_EXTRA 4
#else
#define MAIN_EXTRA 0
#endif

#if (defined(MAIN_EXTRA) && MAIN_EXTRA == 4)
int main(void)
{
    int value = calculate();
    value += MAIN_EXTRA;
    value -= EXTRA_BONUS;
    return value;
}
#else
int main(void) { return 0; }
#endif
