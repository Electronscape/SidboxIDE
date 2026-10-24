# Stage 5.60.1.231026 — Title Screen Designer crash hotfix

## Reported failure

While clicking artwork in the Stage 5.60 Title Screen Designer, the IDE terminated abnormally. Fedora 44's GDB stack stopped in `QGraphicsItem::setSelected()` called from `QGraphicsItem::mousePressEvent()`, inside `editGameTitleScreen()`.

## Root cause

`gametitlescreeneditor.cpp` connected the graphics scene's `selectionChanged` signal to the selected-element dropdown. That dropdown's `currentIndexChanged` handler unconditionally invoked `render()`. `render()` called `scene->clear()`, immediately destroying every graphics item, including the item Qt was still clicking. This was a use-after-free during synchronous mouse-event handling.

## Fix

- The preview `selectionChanged` callback changes only the selected element and its properties; it does not rebuild or reselect graphics items while Qt processes the mouse click.
- Changing the selected element from the dropdown/table highlights the existing graphics items under a `QSignalBlocker`, without destroying them.
- Artwork/text/background changes still regenerate the preview normally.
- Stored `.sidbox-title-screen.json`, the PPBs, world files, TFCard and game runtime are not modified.

## Changed files

- `gametitlescreeneditor.cpp`
- `splashscreenwidget.cpp` (`Build: 5.60.1.231026`)
- `development/tests/test_stage5601_title_preview_crash.py`
- `development/tests/test_stage560_title_screen_styling.py` (updated splash assertion only)
- `development/tests/test_stage559_title_designer.py` (updated splash assertion only)

## Verification

PASS: Stage 5.60.1 source-level regression test for preview selection lifetime; PASS: prior Stage 5.60 title styling and Stage 5.59 title data tests.

Full Qt6 build and GUI crash reproduction **not** verified in this environment (Qt6 development files unavailable). Rebuild on Fedora, click and drag several menu/title previews, switch selection by dropdown and table, and confirm no crash. Prior QDBus/file-model notifications are not evidence of corrupt project data.

Apply the drop-in over Stage 5.60. No game project regeneration required.
