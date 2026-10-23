# Stage 5.34.3: Dialogue Speaker Auto-fill

In Adventure Editor > Dialogue, `+ Dialogue Node` fills its new **Speaker** field from the name of the top-level folder under which it is created.

- For example, `Wizard` > `Greeting` > `Node` inherits `Wizard`.
- Works when selecting either a folder or an existing dialogue inside that folder.
- If adding a dialogue in `Unfiled dialogues`, or with no usable folder name, Speaker stays `NPC`.
- Existing dialogues are unchanged, and Speaker remains fully editable.
- Folder assignment and stable dialogue IDs are unaffected.

This is an IDE-only change. No need to regenerate the game or change `main.c`.

Splash build: `5.34.3.221026`.

Qt6 was not available in the test environment; please build on Fedora.
