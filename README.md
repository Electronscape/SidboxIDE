SIDBOX / CoderGirl IDE source — Stage 5.62.231026

HUD Designer uses the same native SIDBOX glyph preview as GUI Designer and
Title Screen Designer. Labels, numeric stats and collectable counters render
from the shared 256-character 8×16 firmware-style font, not the desktop Qt font.
See STAGE5.62-HUD-SIDBOX-FONT-PREVIEW.md.

The generated game HUD runtime and all saved project/PPB assets are unchanged.
Full Qt6 GUI compilation and visual confirmation still need Fedora testing.
