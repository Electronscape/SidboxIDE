/* CGARM CLI Stage 3 smoke test (actual SIDBOX applet, NOT a Linux host test). */
#include <stdio.h>

int main(void)
{
    printf("Hello from cgarm-build!\n");
    printf("Static libcgarm.a is linked.\n");
    return 0;
}
