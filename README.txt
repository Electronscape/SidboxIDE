SIDBOX IDE 5.136.3.011126 - Workflow Notes: explicit line breaks

Apply over 5.136.2.011126 by replacing these two files at their existing source locations:
  notefloweditor.cpp
  splashscreenwidget.cpp

Notes and decision descriptions now honour manually inserted line breaks and blank
lines, while continuing to word-wrap and grow the card to fit the full text.
Uses QTextDocument's plain-text layout instead of QStaticText.

Everything else in Workflow Notes, including saved pan/zoom, snapping, checklist
status, branch collapsing, files and wiring, is unchanged.

Qt6 compilation cannot be verified in this environment (Qt6 SDK unavailable).
