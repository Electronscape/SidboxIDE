#include "shared.h"
int main(void)
{
    int local[8] = {0};
    int changed = update_buffer(local, 8);
    int *p = &local[2];
    int *q = step_pointer(local, 6);
    p++;
    int distance = q - p;
    int scalar = 10;
    int *scalar_ref = &scalar;
    *scalar_ref = *scalar_ref + 13;
    int *first = local;
    first = first + 1;
    int positive = *(1 + first);
    int equal = (first != 0);
    return changed + read_global() + distance + scalar + positive + equal + q[-1];
}
