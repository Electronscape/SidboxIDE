#include "shared.h"
static int global_scores[8] = {0};

int update_buffer(int *buffer, int count)
{
    for (int i = 0; i < count; i++) {
        buffer[i] = i * 7 + 5;
    }
    int *pointer = buffer;
    pointer += 2;
    *pointer = *pointer + 50;
    pointer--;
    return pointer[1] + buffer[0];
}

int *step_pointer(int *buffer, int count)
{
    return buffer + count;
}

int read_global(void)
{
    for (int i = 0; i < 8; ++i)
        global_scores[i] = i * 9;
    int *p = global_scores;
    p++;
    int *q = &global_scores[5];
    return *(p + 2) + *q + (q - p);
}
