# Stage 5.35: Reuse matching PNG colours

## Request

When converting a PNG to a SIDBOX PPB, provide an optional **Reuse matching colours (only add new unique colours)** checkbox. Existing matching colours must retain the same CLUT indices instead of consuming new output entries.

## Where

Game Designer → Import PNG → Palette mode **Generate colours in selected range** → check **Reuse matching colours**. It starts **unchecked**, so current imports behave as before. The option is disabled for **Start with a blank palette** and **Match existing palette colours (do not modify)**.

## Algorithm

* For each visible (non-transparent) source RGB, look for an exact, opaque matching CLUT entry in indices **1..255**, including indices *outside* the selected import range. Prefer an index outside the writable range if several indices have the same RGB.
* If an existing match is inside the selected range, reserve that index so the new colours cannot overwrite it.
* Add only as-yet-unmatched source RGBs to other available indices in the selected writable range. Exact protected colours use an existing entry if possible, instead of needing a duplicate protected entry.
* All transparent PNG pixels and the optional exact transparency key still map to **index 0**. Index 0 is never reused for visible pixels; palette entries with alpha below 128 are likewise excluded from visible matches.
* In the preview, exact reused colours keep their indices even if a dither setting is selected. If there are more new RGBs than available indices, only the new colours are reduced/nearest-matched; existing matches remain exact.
* The preview reports the number of existing RGBs reused and new palette entries generated. The same converter runs for actual saved PPB/CLUT data.

**Important:** The selected range is still a writable range. Existing palette entries *not referenced as reused colours in this PNG* within that range may be replaced by new colours. As with the previous importer, choose an appropriate free or sacrificial range to avoid changing colours in already authored resources. The IDE cannot infer whether arbitrary existing indices are referenced by external artwork. If no writable index remains, unmatched colours are approximated with available matched colours.

## Changed production files

* `pngpaletteimport.h`
* `pngpaletteimport.cpp`
* `splashscreenwidget.cpp` (`Build: 5.35.231026`)

No `.sbgm` formats, firmware, game rules or hand-authored `main.c` change. No game-code regeneration required.

## Tests

* Python source regressions, including earlier importer layout, protected-colour, picker and background-import checks (run here).
* `development/tests/test_stage535_png_reuse.cpp`: Qt6 executable regression for reused indices inside/outside selected range, protected matches, transparency, dithering, quantised fallback, legacy unchecked mode and UI checkbox (provided for Fedora). Run it from the IDE source root:

```bash
g++ -std=c++17 -fPIC -I. development/tests/test_stage535_png_reuse.cpp \
  pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/test_stage535_png_reuse
QT_QPA_PLATFORM=offscreen /tmp/test_stage535_png_reuse
```

Qt6 development headers are unavailable in the packaging environment, so the full Qt6 build and real Qt6 test are pending the Fedora build.
