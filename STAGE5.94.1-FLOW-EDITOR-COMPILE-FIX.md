# CoderGirl Stage 5.94.1 (24 Oct 2026)

## Build fix

`gamefloweditor.cpp` (flow graph construction, resource/game-object loop, around line 262):
Correct four uses of undeclared `obj` to `o`, the actual `QJsonObject` defined in the loop.
This fixes the C++ compile error `‘obj’ was not declared in this scope` introduced with the state-frame descriptions in Stage 5.94.

Splash version: `Build: 5.94.1.241026`.

## Files changed

- `gamefloweditor.cpp`
- `splashscreenwidget.cpp`

No changes to the runtime, game project, `main.c`, or generated world files.

## Testing

- Verified exact four references corrected in their intended scope.
- Verified other uses of `obj` remain in the later loop where that identifier *is* declared.
- Qt6 development headers are not installed in this environment; compilation must be confirmed on Fedora.
