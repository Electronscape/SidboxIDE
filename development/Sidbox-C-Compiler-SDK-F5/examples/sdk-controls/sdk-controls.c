#include "apis.h"

int main(int argc, char **argv)
{
    int window = SBOS_CreateWindow(NULL, 24, 30, 416, 220,
                                    "SDK controls", SBX_WIN_DEFAULT);
    if (window == 0xff)
        return 1;

    CGGadget status = SBOS_CreateLabel(window, 12, 12, 360, 16,
                                       "Setting up controls", GAD_TOOL_DEFAULT);
    CGGadget input = SBOS_CreateTextBox(window, 12, 40, 360, 24,
                                        "", 0, GAD_TOOL_DEFAULT);
    CGGadget checkbox = SBOS_CreateCheckbox(window, 12, 78, 168, 24,
                                             "Enabled", 0, GAD_TOOL_DEFAULT);
    CGGadget button = SBOS_CreateButton(window, 202, 78, 170, 24,
                                        "Button", GAD_TOOL_DEFAULT);
    CGGadget progress = SBOS_CreateProgBar(window, 12, 122, 360, 20,
                                           GAD_TOOL_DEFAULT);
    if (status == 0 || input == 0 || checkbox == 0 || button == 0 || progress == 0)
        return 1;

    SBOS_TextBoxSetText(input, "Type here");
    SBOS_CheckboxSetState(checkbox, 1);
    SBOS_ProgressbarSetMinMax(progress, 0, 100);
    SBOS_ProgressbarSetValue(progress, 65);
    SBOS_GadgetSetFocus(input);

    if (SBOS_CheckboxGetState(checkbox) != 1)
        return 2;
    return SBOS_LabelSetText(status, "Controls ready") != 0;
}
