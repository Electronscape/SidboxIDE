#include "apis.h"

int main(int argc, char **argv)
{
    int window = SBOS_CreateWindow(NULL, 24, 58, 360, 112,
                                    "Hello from Sidbox SDK", SBX_WIN_DEFAULT);
    return window == 0xff;
}
