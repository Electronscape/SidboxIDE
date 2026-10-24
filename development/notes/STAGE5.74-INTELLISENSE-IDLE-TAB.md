# CoderGirl IDE Stage 5.74.241026: IntelliSense idle time and Tab safety

Changes in `codeeditor.cpp`:

- The automatic completion popup is scheduled after **100 ms without another text edit** (previously 120 ms).
- Every new text edit restarts the single-shot timer; the popup is not summoned by ordinary caret navigation.
- **Tab/Shift+Tab now always indent/unindent** the editor, even when an IntelliSense suggestion list happens to be visible. Tab no longer accepts or inserts a suggestion.
- If the popup has Qt keyboard focus, Tab/Shift+Tab are forwarded to the source editor for normal indentation.
- Indenting/unindenting cancels pending completion and dismisses any visible popup; textChanged signals from indentation cannot reopen it.
- **Enter/Return** accepts a visible completion; Escape closes it. Ctrl+Tab still switches source tabs.
- The bracket matcher, source formatter, 2048 KB syntax limit, game generators and user-owned game `main.c` are unchanged.

Modified source files: `codeeditor.cpp`, `splashscreenwidget.cpp`.
Splash label: `Build: 5.74.241026`.

## Fedora testing

1. Build IDE using the normal Qt6 setup.
2. In a source file, type a name with completion candidates. Pause 100 ms: popup should appear.
3. Press Tab while popup is visible: it should insert a literal tab, **not** replace the function name.
4. Shift+Tab unindents normally with popup visible or hidden.
5. Enter on a visible completion intentionally inserts the suggestion; Esc dismisses it.
6. Rapidly type/paste and indent: no unexpected completion insertion.
7. Rebuild and check compiler Issues panel is clean of new warnings.

**Build status:** Source inspection and test assertions performed. This container lacks Qt6 dev headers, so actual compilation/hardware UI testing is pending on Fedora.
