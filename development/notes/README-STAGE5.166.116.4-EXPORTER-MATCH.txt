# Stage 5.166.116.4 (30 Oct 2026): Matched Breakable Event Exporter

Fixes the exact error message reported after a Breakable ON DESTROY event was connected to AND logic:

    Invalid ON ARRIVAL logic input on 'bonkCollect'.

This exact text occurs in the **old Stage 113/114 gamedesigner_export.cpp**, whose validator accepts only a lift's ON ARRIVAL event. Stage 115+ accepts Breakable ON HIT and ON DESTROY. If this message appears after installing Stage 116.3, the executable was built with **mixed source versions** or an older executable is being launched.

This release is based on the complete Stage 116.3 source and explicitly includes **gamedesigner_export.cpp**, **gamevisualgraphlogic.h** and **splashscreenwidget.cpp**. The exporter validation error now prints the offending node and event ID rather than incorrectly calling all inputs ON ARRIVAL. The runtime event logic and .sbgm/save data formats are unchanged.

## Recommended install

1. Extract `SIDBOX1164-Full.zip` to a **new/empty source directory**. Do NOT merge it into an old Stage 114 tree.
2. Configure and build in a separate, clean CMake build directory. On Fedora Qt6, make sure the IDE executable you run is from that new build.
3. Check the splash screen displays `Build: 5.166.116.4.301026`.
4. Open the existing world and choose Update World Objects. Do **not** delete or rewire the saved ON DESTROY -> AND gate.

`SIDBOX1164-Exporter-Fix.zip` contains the three above-listed files and should only be applied when the rest of the source is already Stage 116.3. If there is any doubt, use the complete source.

## Verification

Focused source tests cover validation of ON HIT/ON DESTROY, actual source UUIDs, pulse emission, and detection of the stale Stage 114 error string. Qt development libraries are unavailable here, so the full GUI compilation and SIDBOX hardware run must still be tested on Fedora.
