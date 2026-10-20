# GamerGirl Stage 4.20 — Source navigator 2px bottom breathing room

Based on Stage 4.19. Replace only `mainwindow.cpp` in the IDE source root.

- Code source object/event navigation strip 30px → 32px high.
- Layout margins: 6px left, 2px top, 6px right, **4px bottom**.
- Dropdown top position, widths, and behaviour unchanged.
- Editor viewport moves down 2px with the strip, preserving the blue border.
- No other runtime, firmware or project format changes.

Run the focused Python test:
`python3 development/tests/test_stage420_source_navigator_padding.py`

Visual Qt6 check on Fedora is still required.
