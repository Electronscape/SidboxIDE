SIDBOX IDE Stage 5.166.106.1.291026 (29 Oct 2026)

Qt build hotfix for the Stage 5.166.106 Game Object Dependency Audit.

FILE: gamedesigner.cpp
FUNCTION: GameDesigner::editGameObject()

Corrected the linked Trigger target audit's warning message to use escaped
C++ newlines in both the translated string and QStringLiteral join separator.
This fixes the user's compiler diagnostics at lines 11052-11056.

No game runtime, project format, or audit behavior changes.
Splash Build: 5.166.106.1.291026.

VALIDATION: Audit source tests and C++ literal lexical scan passed.
The full Qt6 IDE build is unavailable in this environment. Please rebuild on
Fedora before treating the fix as compiled/GUI-tested.
