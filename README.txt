SIDBOX IDE - CoderGirl Gadget Palette (Qt6)
=========================================

BASELINE
  sidbox-virtual-timer.zip / guidesigner.cpp (the last Timer release)

UPDATED FILE
  guidesigner.cpp     - Full drop-in replacement

NO OTHER PROJECT FILES NEED CHANGING UNTIL YOU ADD YOUR OWN ICON PNGS.

WHAT CHANGED
  * Gadget toolbox is now a compact graphical palette: two or more columns
    depending on available width, with 64 x 24 pixel tiles.
  * Alphabetical sorting retained.
  * Click a tile to select it, double-click to add, or drag onto the canvas.
    "Add Selected Gadget" button is retained.
  * Hover tooltips show gadget names and descriptions.
  * All gadget type names are carried in QListWidgetItem::UserRole; drag/drop
    and add commands no longer rely on visible text labels.
  * The Timer remains a designer-only gadget (never rendered on SIDBOX).
  * If a PNG isn't in the executable's Qt resources yet, a dark placeholder
    with a small symbol and shortened name is drawn automatically.
  * This does not touch .sbui, code generation, Undo, timers or firmware.

YOUR ARTWORK - 64x24 pixels each, preferably PNG with transparency:

  icons/gadget_bitmapview.png
  icons/gadget_button.png
  icons/gadget_canvas.png
  icons/gadget_checkbox.png
  icons/gadget_gridselect.png
  icons/gadget_label.png
  icons/gadget_listbox.png
  icons/gadget_progressbar.png
  icons/gadget_radio.png
  icons/gadget_scrollbar.png
  icons/gadget_slider.png
  icons/gadget_tabgroup.png
  icons/gadget_textarea.png
  icons/gadget_textbox.png
  icons/gadget_timer.png

HOW TO INSTALL YOUR ARTWORK
  1. Save each 64x24 PNG in the IDE project's icons/ folder, using the
     exact filenames above. They need no text label; the IDE provides tooltip.
  2. Add these file paths under FILES in the existing qt_add_resources(...)
     list in the project's CMakeLists.txt (same list as icons/icon_save.png):

        icons/gadget_bitmapview.png
        icons/gadget_button.png
        icons/gadget_canvas.png
        icons/gadget_checkbox.png
        icons/gadget_gridselect.png
        icons/gadget_label.png
        icons/gadget_listbox.png
        icons/gadget_progressbar.png
        icons/gadget_radio.png
        icons/gadget_scrollbar.png
        icons/gadget_slider.png
        icons/gadget_tabgroup.png
        icons/gadget_textarea.png
        icons/gadget_textbox.png
        icons/gadget_timer.png

  3. Rebuild the IDE. This creates Qt resource URLs such as
     :/icons/gadget_button.png, which the palette automatically discovers.

  NOTE: This project CMakeLists.txt uses qt_add_resources for the application
  icons. Editing only res.qrc will not add them to that CMake resources list.
  Do NOT add absent PNG names to CMakeLists yet; CMake would fail on missing files.

INSTALLATION
  Replace your project's guidesigner.cpp with the ZIP copy, or apply
  sidbox-gadget-palette.patch against the Timer version.

TEST
  1. Open GUI Designer. Palette should show 15 small graphic tiles.
  2. Hover one: tooltip names gadget and tells what it does.
  3. Single-click Timer, click Add Selected Gadget: Timer should appear.
  4. Double-click Button: Button should be added.
  5. Drag Label from palette onto the canvas: should add where dropped.
  6. Save/open .sbui; regenerate applet. No output changes expected.
  7. Add one PNG to Qt resources, rebuild: just that tile updates;
     all other entries continue to use placeholders.

LIMITATIONS
  No live preview of Qt6 UI in this environment; compile and on-screen
  interaction should still be checked in the actual IDE.

NO firmware, API, or mainwindow.cpp changes. Your 2048 KB limit is untouched.
