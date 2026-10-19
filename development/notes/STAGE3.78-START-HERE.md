# Stage 3.78 — PNG Background Rendering Default and Replacement

**Purpose:** An ordinary PNG imported to `Backgrounds` must be generated as a **Direct — convert PPB** resource, not a legacy sprite. A PPB overwritten by the PNG importer must update its existing background record, not append a duplicate resource pointing to that PPB.

## Installing

Replace `gamedesigner.cpp` in the IDE source root and rebuild in Qt Creator. The complete IDE archive contains the same files, based on Stage 3.77a. No firmware, physics helpers, PNG palette conversion, CoderGirl UI, or syntax file-size setting changed.

## What changed

- A PNG imported into **Backgrounds** is automatically configured for `direct_convert`, at (0,0), scale 100%. That selects the runtime transpose needed to feed the SIDBOX's column-major direct display buffer.
- Reimporting to the exact same PPB path already used by a background updates the existing resource and retains its identifier.
- When importing to a *new* filename while exactly one background resource already exists, asks if you want to replace that resource. **Yes** updates the existing resource. **No** still adds a separate background, so check your design before exporting; the generator only supports one standalone direct background.
- Other asset imports are unchanged.

## Existing projects

This fix applies to **future imports**. It does not silently rewrite existing `.sbgm` files. If your image was already imported, select its resource in Game Resources → Backgrounds and choose `Direct — convert PPB`, then Save/Export game assets and rebuild. If both old and new backgrounds are present, keep the correct one and remove the duplicate only after backing up your project.

**Important:** The user also reported the IDE unexpectedly exits when closing world1.sbgm. This patch does **not** claim to fix that: its cause is not yet reproduced. Please obtain a Qt Creator debugger backtrace (or a terminal error) from an instance that exhibits the problem. No speculative changes to tab lifetime or unrelated Qt code have been made.

## Tests

The static regression test is `development/tests/test_stage378_png_background_default.py`. Qt6 was not installed in the package-generation environment; this is not a Qt build or SIDBOX hardware acceptance test.
