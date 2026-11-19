#include "apis.h"

int main(int argc, char **argv)
{
    int window = SBOS_CreateWindow(NULL, 24, 58, 360, 112,
                                    "Hello from Sidbox SDK", SBX_WIN_DEFAULT);
    if (window == 0xff)
        return 1;
    CGGadget label = SBOS_CreateLabel(window, 10, 12, 320, 20,
                                     "Hello from SBOS_CreateLabel()", GAD_TOOL_DEFAULT);
    return label == 0;
}
