/* Real SDK EBI field names; safe, read-only hardware test. */
#include "apis.h"
int main(void)
{
    int buttons = API.hwl->getjoyport();
    int cycles = API.hwl->getTicks();
    return (buttons & 63) + ((cycles >> 16) & 1);
}
